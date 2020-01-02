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
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/protocol/DestinationL3AddressHeader_m.h"
#include "inet/protocol/SendToL3Address.h"

namespace inet {

Define_Module(SendToL3Address);

void SendToL3Address::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        address = Ipv4Address(par("address").stringValue());
        registerService(IProtocol::destinationL3Address, gate("in"), gate("in"));
        registerProtocol(IProtocol::destinationL3Address, gate("out"), gate("out"));
    }
}

void SendToL3Address::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    auto header = makeShared<DestinationL3AddressHeader>();
    header->setDestinationAddress(address);
    packet->insertAtFront(header);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&IProtocol::forwarding);
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&IProtocol::destinationL3Address);
    send(packet, "out");
}

void SendToL3Address::confirm(Packet *packet, bool successful)
{
}

} // namespace inet

