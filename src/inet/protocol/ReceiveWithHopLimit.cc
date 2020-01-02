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
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/protocol/HopLimitHeader_m.h"
#include "inet/protocol/ReceiveWithHopLimit.h"

namespace inet {

Define_Module(ReceiveWithHopLimit);

void ReceiveWithHopLimit::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        registerService(IProtocol::hopLimit, gate("in"), gate("in"));
        registerProtocol(IProtocol::hopLimit, gate("out"), gate("out"));
    }
}

void ReceiveWithHopLimit::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    auto header = packet->popAtFront<HopLimitHeader>();
    if (header->getHopLimit() > 0) {
        packet->addTag<HopLimitInd>()->setHopLimit(header->getHopLimit());
        packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&IProtocol::forwarding);
        send(packet, "out");
    }
    else
        delete packet;
}

} // namespace inet

