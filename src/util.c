#include "util.h"

// out: 12 floats
void CreateLine(float* out, vec3s start, vec3s end, vec3s color)
{
	float data[] = {
		start.x, start.y, start.z,	color.x, color.y, color.z,
		end.x, end.y, end.z,		color.x, color.y, color.z
	};

	memcpy(out, data, sizeof(data));
}

void GetNeighboringBlocks(struct Chunk* chunk, u16 blockIndex)
{
	struct Block* curBlock = &chunk->blocks[blockIndex];
	
	curBlock->neighbors.left = ((blockIndex-1) % CHUNK_DEPTH == 0) ? NULL : &chunk->blocks[blockIndex - 1];
	curBlock->neighbors.right = ((blockIndex+1) % CHUNK_DEPTH == 0) ? NULL : &chunk->blocks[blockIndex + 1];
}
