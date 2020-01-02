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

#include "inet/common/checksum/TcpIpChecksum.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/protocol/CrcHeader_m.h"
#include "inet/protocol/CrcInsertion.h"

namespace inet {

Define_Module(CrcInsertion);

void CrcInsertion::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        registerService(IProtocol::crc, gate("in"), gate("in"));
        registerProtocol(IProtocol::crc, gate("out"), gate("out"));
    }
}

void CrcInsertion::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
//    auto data = packet->peekDataAsBytes();
//    auto crc = TcpIpChecksum::checksum(data->getBytes());
    auto crc = 0; // TODO:
    auto header = makeShared<CrcHeader>();
    header->setCrc(crc);
    packet->insertAtFront(header);
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&IProtocol::crc);
    send(packet, "out");
}

void CrcInsertion::confirm(Packet *p, bool successful)
{
}

} // namespace inet

