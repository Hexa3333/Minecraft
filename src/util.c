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
	u8 blockIndexX = blockIndex % CHUNK_WIDTH;
	u8 blockIndexZ = blockIndex / CHUNK_WIDTH;
	
	curBlock->neighbors.left = (blockIndex-1 % CHUNK_WIDTH == 0 || blockIndexX != 0) ? &chunk->blocks[blockIndex - 1] : NULL;
	curBlock->neighbors.right = (blockIndex+1 % CHUNK_WIDTH == 0 || blockIndexX != 0) ? &chunk->blocks[blockIndex + 1] : NULL;
	curBlock->neighbors.front = ((blockIndex-CHUNK_DEPTH) % CHUNK_WIDTH == 0 || blockIndexZ != 0) ? &chunk->blocks[blockIndex - CHUNK_WIDTH] : NULL;
	curBlock->neighbors.behind = ((blockIndex+CHUNK_DEPTH) % CHUNK_WIDTH == 0 || blockIndexZ != 0) ? &chunk->blocks[blockIndex + CHUNK_DEPTH] : NULL;
}
