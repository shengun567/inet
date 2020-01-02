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
#include "inet/protocol/Reordering.h"
#include "inet/protocol/SequenceNumberHeader_m.h"

namespace inet {

Define_Module(Reordering);

void Reordering::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        registerService(IProtocol::sequenceNumber, gate("in"), gate("in"));
        registerProtocol(IProtocol::sequenceNumber, gate("out"), gate("out"));
    }
}

void Reordering::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    auto header = packet->popAtFront<SequenceNumberHeader>();
    auto sequenceNumber = header->getSequenceNumber();
    packets[sequenceNumber] = packet;
    if (sequenceNumber == expectedSequenceNumber) {
        while (true) {
            auto it = packets.find(expectedSequenceNumber);
            if (it == packets.end())
                break;
            send(it->second, "out");
            packets.erase(it);
            expectedSequenceNumber++;
        }
    }
}

} // namespace inet

