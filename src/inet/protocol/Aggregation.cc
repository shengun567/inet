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
#include "inet/protocol/Aggregation.h"
#include "inet/protocol/SubpacketLengthHeader_m.h"

namespace inet {

Define_Module(Aggregation);

void Aggregation::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL)
        aggregatedLength = b(par("aggregatedLength"));
}

void Aggregation::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    if (aggregatedPacket == nullptr) {
        aggregatedPacket = new Packet("");
        aggregatedPacket->copyTags(*packet); // TODO: more complicated
    }
    auto subpacketHeader = makeShared<SubpacketLengthHeader>();
    subpacketHeader->setLengthField(packet->getDataLength());
    std::string aggregatedName = aggregatedPacket->getName();
    if (aggregatedName.length() != 0)
        aggregatedName += "+";
    aggregatedName += packet->getName();
    aggregatedPacket->setName(aggregatedName.c_str());
    aggregatedPacket->insertAtBack(subpacketHeader);
    aggregatedPacket->insertAtBack(packet->peekData());
    if (aggregatedPacket->getTotalLength() > aggregatedLength) {
        send(aggregatedPacket, "out");
        aggregatedPacket = nullptr;
    }
    delete packet;
}

void Aggregation::confirm(Packet *p, bool successful)
{
}

} // namespace inet

