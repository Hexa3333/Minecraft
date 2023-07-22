#ifndef CHUNK_H
#define CHUNK_H

#include <cglm/struct.h>
#include "graphics/Block.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 16

#define CHUNK_TOTAL_BLOCKS CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_DEPTH
#define CHUNK_INDEX(x,y,z) y][z][x

#define MAX_VISIBLE_CHUNKS_X 2
#define MAX_VISIBLE_CHUNKS_Z 2
#define MAX_VISIBLE_CHUNKS MAX_VISIBLE_CHUNKS_X * MAX_VISIBLE_CHUNKS_Z
#define CHUNK_MAP_INDEX(x,z) z*MAX_VISIBLE_CHUNKS_Z + x

struct Chunk
{
	vec3s position;
	struct Block blocks[CHUNK_HEIGHT][CHUNK_DEPTH][CHUNK_WIDTH];
};

struct Chunk* CreateChunk(u32 x, u32 z);
void DrawChunk(struct Chunk* chunk);

#endif // CHUNK_H
