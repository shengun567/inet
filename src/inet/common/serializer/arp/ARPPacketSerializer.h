//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __INET_ARPPACKETSERIALIZER_H
#define __INET_ARPPACKETSERIALIZER_H

#include "inet/common/packet/serializer/FieldsChunkSerializer.h"

namespace inet {

namespace serializer {

/**
 * Converts between ARPPacket and binary (network byte order)  ARP header.
 */
class INET_API ARPPacketSerializer : public FieldsChunkSerializer
{
  protected:
    MACAddress readMACAddress(MemoryInputStream& stream, unsigned int size) const;
    IPv4Address readIPv4Address(MemoryInputStream& stream, unsigned int size) const;

    virtual void serialize(MemoryOutputStream& stream, const Ptr<const Chunk>& chunk) const override;
    virtual Ptr<Chunk> deserialize(MemoryInputStream& stream) const override;

  public:
    ARPPacketSerializer() : FieldsChunkSerializer() {}
};

} // namespace serializer

} // namespace inet

#endif // ifndef __INET_ARPPACKETSERIALIZER_H