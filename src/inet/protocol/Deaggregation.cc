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
#include "inet/protocol/Deaggregation.h"
#include "inet/protocol/SubpacketLengthHeader_m.h"

namespace inet {

Define_Module(Deaggregation);

void Deaggregation::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        registerService(IProtocol::aggregation, gate("in"), gate("in"));
        registerProtocol(IProtocol::aggregation, gate("out"), gate("out"));
    }
}

void Deaggregation::handleMessage(cMessage *message)
{
    auto aggregatedPacket = check_and_cast<Packet *>(message);
    cStringTokenizer tokenizer(aggregatedPacket->getName(), "+");
    while (aggregatedPacket->getDataLength() > b(0)) {
        auto subpacketHeader = aggregatedPacket->popAtFront<SubpacketLengthHeader>();
        auto subpacketData = aggregatedPacket->popAtFront(subpacketHeader->getLengthField());
        auto subpacket = new Packet(tokenizer.nextToken(), subpacketData);
        send(subpacket, "out");
    }
    delete aggregatedPacket;
}

} // namespace inet

