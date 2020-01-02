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
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/protocol/DestinationMacAddressHeader_m.h"
#include "inet/protocol/SendToMacAddress.h"

namespace inet {

Define_Module(SendToMacAddress);

void SendToMacAddress::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        const char *addressAsString = par("address");
        if (strlen(addressAsString) != 0)
            address = MacAddress(addressAsString);
        consumer = getConnectedModule<queueing::IPassivePacketSink>(gate("out"));
        registerService(IProtocol::destinationMacAddress, gate("in"), gate("in"));
        registerProtocol(IProtocol::destinationMacAddress, gate("out"), gate("out"));
    }
}

void SendToMacAddress::pushPacket(Packet *packet, cGate *inGate)
{
    Enter_Method_Silent();
    take(packet);
    handleMessage(packet);
}

void SendToMacAddress::handleCanPushPacket(cGate *outGate)
{
    auto inGate = gate("in");
    auto producer = findConnectedModule<queueing::IActivePacketSource>(inGate);
    if (producer != nullptr)
        producer->handleCanPushPacket(inGate->getPathStartGate());
}

void SendToMacAddress::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    auto macAddressReq = packet->findTag<MacAddressReq>();
    auto destinationAddress = macAddressReq != nullptr ? macAddressReq->getDestAddress() : address;
    auto header = makeShared<DestinationMacAddressHeader>();
    header->setDestinationAddress(destinationAddress);
    packet->insertAtFront(header);
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&IProtocol::destinationMacAddress);
    if (consumer != nullptr)
        consumer->pushPacket(packet, gate("out")->getPathEndGate());
    else
        send(packet, "out");
}

void SendToMacAddress::confirm(Packet *packet, bool successful)
{
    auto input = findConnectedModule<IProtocol>(gate("in"));
    if (input != nullptr)
        input->confirm(packet, successful);
}

} // namespace inet

