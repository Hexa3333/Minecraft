#ifndef CHUNK_H
#define CHUNK_H

#include <cglm/struct.h>
#include "graphics/Block.h"

#define CHUNK_WIDTH 16
//#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 16

#define CHUNK_TOTAL_BLOCKS 16*16
#define CHUNK_INDEXER(x,z) z * CHUNK_WIDTH + x
//#define CHUNK_BLOCK_INDEXER(x,y,z) (z * CHUNK_WIDTH * CHUNK_HEIGHT) + (y * CHUNK_WIDTH) + x

#define RENDER_DISTANCE 4 * 4

struct Chunk
{
	vec3s position;
	struct Block blocks[CHUNK_WIDTH * CHUNK_DEPTH];
};
struct Chunk CreateChunk(u32 x, u32 z);
void DrawChunk(struct Chunk* chunk);

#endif // CHUNK_H
