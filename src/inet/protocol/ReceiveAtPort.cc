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

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/protocol/DestinationPortHeader_m.h"
#include "inet/protocol/ReceiveAtPort.h"

namespace inet {

Define_Module(ReceiveAtPort);

void ReceiveAtPort::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        port = par("port");
        registerService(IProtocol::destinationPort, gate("in"), gate("in"));
        registerProtocol(IProtocol::destinationPort, gate("out"), gate("out"));
    }
}

void ReceiveAtPort::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    auto header = packet->popAtFront<DestinationPortHeader>();
    if (header->getDestinationPort() == port)
        send(packet, "out");
    else
        delete packet;
}

void ReceiveAtPort::confirm(Packet *packet, bool successful)
{
}

} // namespace inet

