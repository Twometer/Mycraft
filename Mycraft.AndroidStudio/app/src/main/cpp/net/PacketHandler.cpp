//
// Created by twome on 21/06/2018.
//

#include "PacketHandler.h"
#include "PacketBuffer.h"
#include "../world/Chunk.h"
#include "../Renderer.h"
#include "../Logger.h"

int countSetBits(unsigned short bitmask) {
    unsigned int count = 0;
    while (bitmask) {
        count += bitmask & 1;
        bitmask >>= 1;
    }
    return count;
}

int calculateChunkBlobLength(int sections, bool skylight, bool continuous) {
    int var3 = sections * 2 * 16 * 16 * 16;
    int var4 = sections * 16 * 16 * 16 / 2;
    int var5 = skylight ? sections * 16 * 16 * 16 / 2 : 0;
    int var6 = continuous ? 256 : 0;
    return var3 + var4 + var5 + var6;
}

void PacketHandler::onPacket(int id, unsigned char *content, int contentLength) {

    PacketBuffer buffer = PacketBuffer(content, contentLength);

    //  LOGD("Received packet id %d with contentLength %d", id, contentLength);

    if (id == 0x08) {
        float x = static_cast<float>(buffer.readDouble());
        float y = static_cast<float>(buffer.readDouble());
        float z = static_cast<float>(buffer.readDouble());

        LOGD("Updated position: %f %f %f", x, y, z);

        Renderer::getPlayer()->setPosition(x, y, z);
    } else if (id == 0x26) {
        bool skylight = buffer.readBool();
        int columnCount = buffer.readVarInt();
        int *xCoords = new int[columnCount];
        int *zCoords = new int[columnCount];
        unsigned short *bitmasks = new unsigned short[columnCount];


        for (int i = 0; i < columnCount; i++) {
            xCoords[i] = buffer.readInt();
            zCoords[i] = buffer.readInt();
            bitmasks[i] = buffer.readUShort();
        }

        for (int i = 0; i < columnCount; i++) {
            unsigned short bitmask = bitmasks[i];
            Chunk *chunk = new Chunk(xCoords[i], zCoords[i]);
            chunk->loadFromPacket(buffer.getDataPointer(), bitmask);
            buffer.skip(calculateChunkBlobLength(countSetBits(bitmask), skylight, true));
            Renderer::getWorld()->addChunk(chunk);
        }

        delete[] xCoords;
        delete[] zCoords;
        delete[] bitmasks;
    }

}
