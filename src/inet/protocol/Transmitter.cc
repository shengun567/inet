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
#include "inet/protocol/Transmitter.h"

namespace inet {

Define_Module(Transmitter);

void Transmitter::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        datarate = bps(par("datarate"));
        endTimer = new cMessage("endTimer");
    }
}

void Transmitter::handleMessage(cMessage *message)
{
    if (message == endTimer) {
        auto input = getConnectedModule<IProtocol>(gate("in"));
        input->confirm(packet, true);
    }
    else {
        auto packet = check_and_cast<Packet *>(message);
        auto duration = s(packet->getTotalLength() / datarate).get();
        packet->setDuration(duration);
        send(packet, "out");
        scheduleAt(simTime() + duration, endTimer);
    }
}

void Transmitter::confirm(Packet *p, bool successful)
{
}

} // namespace inet

