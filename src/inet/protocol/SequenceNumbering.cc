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

#include "inet/common/ProtocolTag_m.h"
#include "inet/protocol/SequenceNumberHeader_m.h"
#include "inet/protocol/SequenceNumbering.h"

namespace inet {

Define_Module(SequenceNumbering);

void SequenceNumbering::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    auto header = makeShared<SequenceNumberHeader>();
    header->setSequenceNumber(sequenceNumber++);
    packet->insertAtFront(header);
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&IProtocol::sequenceNumber);
    send(packet, "out");
}

void SequenceNumbering::confirm(Packet *p, bool successful)
{
}

} // namespace inet

