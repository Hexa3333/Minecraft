#ifndef CHUNK_H
#define CHUNK_H

#include "../common.h"
#include "Block.h"

#define CHUNK_WIDTH 10
#define CHUNK_DEPTH 10

struct Chunk
{
	double x, z; // middle
	struct Block* blocks;
};

struct Chunk CreateChunk(double x, double w);
void DrawChunk(struct Chunk* chunk);
void FreeChunk(struct Chunk* chunk);

#endif // CHUNK_H
