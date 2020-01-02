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
#include "inet/protocol/FragmentNumberHeader_m.h"
#include "inet/protocol/Defragmentation.h"

namespace inet {

Define_Module(Defragmentation);

void Defragmentation::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        registerService(IProtocol::fragmentation, gate("in"), gate("in"));
        registerProtocol(IProtocol::fragmentation, gate("out"), gate("out"));
    }
}

void Defragmentation::handleMessage(cMessage *message)
{
    auto fragmentPacket = check_and_cast<Packet *>(message);
    auto fragmentHeader = fragmentPacket->popAtFront<FragmentNumberHeader>();
    if (expectedFragmentNumber != fragmentHeader->getFragmentNumber())
        throw cRuntimeError("Unexpected fragment");
    else {
        if (expectedFragmentNumber == 0) {
            std::string name = fragmentPacket->getName();
            name = name.substr(0, name.rfind('-'));
            packet = new Packet(name.c_str());
        }
        expectedFragmentNumber++;
        packet->insertAtBack(fragmentPacket->peekData());
        if (fragmentHeader->getLastFragment()) {
            send(packet, "out");
            packet = nullptr;
            expectedFragmentNumber = 0;
        }
        delete fragmentPacket;
    }
}

} // namespace inet

