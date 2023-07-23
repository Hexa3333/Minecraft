#include "Chunk.h"
#include "util.h"
#include "graphics/Camera.h"

struct Chunk* CreateChunk(u32 x, u32 z)
{
	struct Chunk* ret = malloc(sizeof(struct Chunk));
	if (!ret) return NULL;
	ret->position.x = (float)x;
	ret->position.y = (float)0;
	ret->position.z = (float)z;

	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int y = 0; y < CHUNK_HEIGHT; ++y)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		struct Block* curBlock = &ret->blocks[CHUNK_INDEX(x, y, z)];
		curBlock->position = (vec3s){ret->position.x + x, ret->position.y + y, ret->position.z + z};
		*curBlock = CreateBlock(&g_TerrainShader, BLOCK_STONE, ret->blocks[y][z][x].position);
		curBlock->model = glms_translate(GLMS_MAT4_IDENTITY, ret->blocks[y][z][x].position);
		curBlock->props.isVisible = true;
	}
	
	ret->isRecentlyModified = false;
	SetNeighboringBlocksOfChunk(ret);
	SetChunkInnerBlocksInvisible(ret);
	return ret;
}

void ChunkRemoveBlockAt(struct Chunk* chunk, u8 x, u8 y, u8 z)
{
	chunk->blocks[CHUNK_INDEX(x,y,z)].props.isVisible = false;
	chunk->isRecentlyModified = true;
}

void DrawChunk(struct Chunk* chunk)
{
	if (chunk->isRecentlyModified)
	{
		SetNeighboringBlocksOfChunk(chunk);
		SetChunkInnerBlocksInvisible(chunk);
		chunk->isRecentlyModified = false;
	}

	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int y = 0; y < CHUNK_HEIGHT; ++y)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
			{
				if (chunk->blocks[CHUNK_INDEX(x,y,z)].props.isVisible)
					DrawGameObject(&chunk->blocks[CHUNK_INDEX(x,y,z)]);
			}
}
