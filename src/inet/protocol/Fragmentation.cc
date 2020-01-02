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
#include "inet/protocol/FragmentNumberHeader_m.h"
#include "inet/protocol/Fragmentation.h"

namespace inet {

Define_Module(Fragmentation);

void Fragmentation::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL)
        fragmentLength = b(par("fragmentLength"));
}

void Fragmentation::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    b offset = b(0);
    int fragmentCount = std::ceil((double)packet->getTotalLength().get() / fragmentLength.get());
    for (int i = 0; i < fragmentCount; i++) {
        std::string name = std::string(packet->getName()) + "-frag" + std::to_string(i);
        auto length = std::min(fragmentLength, packet->getTotalLength() - offset);
        auto fragmentData = packet->peekDataAt(offset, length);
        offset += length;
        auto fragmentHeader = makeShared<FragmentNumberHeader>();
        fragmentHeader->setFragmentNumber(i);
        fragmentHeader->setLastFragment(i == fragmentCount - 1);
        auto fragmentPacket = new Packet(name.c_str());
        fragmentPacket->copyTags(*packet);
        fragmentPacket->insertAtBack(fragmentData);
        fragmentPacket->insertAtFront(fragmentHeader);
        fragmentPacket->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&IProtocol::fragmentation);
        send(fragmentPacket, "out");
    }
    delete packet;
}

void Fragmentation::confirm(Packet *p, bool successful)
{
}

} // namespace inet

