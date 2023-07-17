#ifndef CHUNK_H
#define CHUNK_H

#include <cglm/struct.h>
#include "graphics/Block.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 16

#define CHUNK_TOTAL_BLOCKS CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_DEPTH
#define CHUNK_INDEX(x,y,z) y][z][x

#define MAX_VISIBLE_CHUNKS 2 * 2

struct Chunk
{
	vec3s position;
	struct Block blocks[CHUNK_HEIGHT][CHUNK_DEPTH][CHUNK_WIDTH];
};

struct Chunk CreateChunk(u32 x, u32 z);
void DrawChunk(struct Chunk* chunk);

extern struct _ChunkMap
{
	struct Chunk chunks[MAX_VISIBLE_CHUNKS];
} g_ChunkMap;


#endif // CHUNK_H
