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

void SetNeighboringBlocks(struct Chunk* chunk, u8 blockIndexX, u8 blockIndexY, u8 blockIndexZ)
{
	struct Block* curBlock = &chunk->blocks[blockIndexY][blockIndexZ][blockIndexX];
	
	curBlock->neighbors.left =   (blockIndexX != 0) ? &chunk->blocks[blockIndexY][blockIndexZ][blockIndexX-1] : NULL;
	curBlock->neighbors.right =  (blockIndexX != CHUNK_WIDTH-1) ? &chunk->blocks[blockIndexY][blockIndexZ][blockIndexX+1] : NULL;
	curBlock->neighbors.above =  (blockIndexY != CHUNK_HEIGHT-1) ? &chunk->blocks[blockIndexY+1][blockIndexZ][blockIndexX] : NULL;
	curBlock->neighbors.below =  (blockIndexY != 0) ? &chunk->blocks[blockIndexY-1][blockIndexZ][blockIndexX] : NULL;
	curBlock->neighbors.front =  (blockIndexZ != 0) ? &chunk->blocks[blockIndexY][blockIndexZ-1][blockIndexX] : NULL;
	curBlock->neighbors.behind = (blockIndexZ != CHUNK_DEPTH-1) ? &chunk->blocks[blockIndexY][blockIndexZ+1][blockIndexX] : NULL;
}

void SetChunkInnerBlocksInvisible(struct Chunk* chunk)
{
	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int y = 0; y < CHUNK_HEIGHT; ++y)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
			{
				// If it has neighbors in all direction, then it is inside
				struct Block* cur = &chunk->blocks[CHUNK_INDEX(x,y,z)];
				if (
					cur->neighbors.above  &&
					cur->neighbors.below  &&
					cur->neighbors.left   &&
					cur->neighbors.right  &&
					cur->neighbors.front  &&
					cur->neighbors.behind 
				   )
					chunk->blocks[CHUNK_INDEX(x,y,z)].props.isVisible = false;
				else 
					chunk->blocks[CHUNK_INDEX(x,y,z)].props.isVisible = true;
			}
}
