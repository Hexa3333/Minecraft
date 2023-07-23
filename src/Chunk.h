#ifndef CHUNK_H
#define CHUNK_H

#include <cglm/struct.h>
#include "graphics/Block.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 16

#define CHUNK_TOTAL_BLOCKS CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_DEPTH
#define CHUNK_INDEX(x,y,z) y][z][x

#define CHUNK_SET_EVERYTHING(_chunk, _property, _value) \
	for (int _y = 0; _y < CHUNK_HEIGHT; ++_y) \
		for (int _z = 0; _z < CHUNK_DEPTH; ++_z) \
			for (int _x = 0; _x < CHUNK_WIDTH; ++_x) \
				_chunk->blocks[CHUNK_INDEX(_x,_y,_z)].props._property = _value;

#define MAX_VISIBLE_CHUNKS_X 2
#define MAX_VISIBLE_CHUNKS_Z 2
#define MAX_VISIBLE_CHUNKS MAX_VISIBLE_CHUNKS_X * MAX_VISIBLE_CHUNKS_Z
#define CHUNK_MAP_INDEX(x,z) z*MAX_VISIBLE_CHUNKS_Z + x

struct Chunk
{
	vec3s position;
	struct Block blocks[CHUNK_HEIGHT][CHUNK_DEPTH][CHUNK_WIDTH];
	bool isRecentlyModified;
};

struct Chunk* CreateChunk(u32 x, u32 z);
void ChunkRemoveBlockAt(struct Chunk* chunk, u8 x, u8 y, u8 z);
void DrawChunk(struct Chunk* chunk);

#endif // CHUNK_H