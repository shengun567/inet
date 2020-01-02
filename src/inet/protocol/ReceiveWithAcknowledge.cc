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
#include "inet/common/packet/Packet.h"
#include "inet/protocol/AcknowledgeHeader_m.h"
#include "inet/protocol/ReceiveWithAcknowledge.h"
#include "inet/protocol/SequenceNumberHeader_m.h"

namespace inet {

Define_Module(ReceiveWithAcknowledge);

void ReceiveWithAcknowledge::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        registerService(IProtocol::withAcknowledge, gate("in"), gate("in"));
        registerProtocol(IProtocol::withAcknowledge, gate("out"), gate("out"));
    }
}

void ReceiveWithAcknowledge::handleMessage(cMessage *message)
{
    auto dataPacket = check_and_cast<Packet *>(message);
    auto dataHeader = dataPacket->popAtFront<SequenceNumberHeader>();
    send(dataPacket, "out");
    auto ackHeader = makeShared<AcknowledgeHeader>();
    ackHeader->setSequenceNumber(dataHeader->getSequenceNumber());
    auto ackPacket = new Packet("Ack", ackHeader);
    ackPacket->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&IProtocol::acknowledge);
    send(ackPacket, "ackOut");
}

} // namespace inet

