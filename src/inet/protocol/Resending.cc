//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/protocol/Resending.h"

namespace inet {

Define_Module(Resending);

void Resending::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        numRetries = par("numRetries");
        auto inGate = gate("in");
        producer = getConnectedModule<queueing::IActivePacketSource>(inGate);
        producer->handleCanPushPacket(inGate->getPathStartGate());
    }
}

void Resending::pushPacket(Packet *packet, cGate *gate)
{
    Enter_Method_Silent();
    take(packet);
    handleMessage(packet);
}

void Resending::handleMessage(cMessage *message)
{
    ASSERT(retry == 0);
    packet = check_and_cast<Packet *>(message);
    send(packet->dup(), "out");
    retry++;
}

void Resending::confirm(Packet *p, bool successful)
{
    if (successful || retry == numRetries) {
        auto input = getConnectedModule<IProtocol>(gate("in"));
        input->confirm(packet, successful);
        delete packet;
        packet = nullptr;
        retry = 0;
        auto inGate = gate("in");
        producer->handleCanPushPacket(inGate->getPathStartGate());
    }
    else {
        send(packet->dup(), "out");
        retry++;
    }
}

} // namespace inet

