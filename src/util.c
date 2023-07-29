#include "util.h"
#include "graphics/Camera.h"
#include "graphics/Sprite.h"
#include "Chunk.h"
#include "Block.h"

// out: 12 floats
void CreateLine(float* out, vec3s start, vec3s end, vec3s color)
{
	float data[] = {
		start.x, start.y, start.z,	color.x, color.y, color.z,
		end.x, end.y, end.z,		color.x, color.y, color.z
	};

	memcpy(out, data, sizeof(data));
}

vec3s* GetChunkOffsets()
{
	vec3s* ret = malloc(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH * sizeof(vec3s));
	for (int y = 0; y < CHUNK_HEIGHT; ++y)
		for (int z = 0; z < CHUNK_DEPTH; ++z)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
			{
				ret[CHUNK_BLOCK_INDEXER(x,y,z)].x = (float)x;
				ret[CHUNK_BLOCK_INDEXER(x,y,z)].y = (float)y;
				ret[CHUNK_BLOCK_INDEXER(x,y,z)].z = (float)-z;
			}

	return ret;
}

float* GetSpriteXYFromSheet(u8 tileIndexX, u8 tileIndexY)
{
	float x = g_SPRITE_SHEET.tileWidth * (tileIndexX - 1);
	float y = g_SPRITE_SHEET.sheet.height - (g_SPRITE_SHEET.tileHeight * tileIndexY); // y is flipped
	float* ret = malloc(2 * sizeof(float));
	if (ret)
	{
		ret[0] = x;
		ret[1] = y;
		return ret;
	}
	else
	{
		ERR("Malloc failed at: %i", __LINE__);
		return NULL;
	}
}

enum BLOCK_TEX_NAMES MapBlocksToTextures(enum BLOCK_TYPE blockType)
{
	switch (blockType)
	{
		case BLOCK_AIR:
			return TEX_AIR;

		case BLOCK_STONE:
			return TEX_ROCK;

		case BLOCK_DIRT:
			return TEX_DIRT;

		default:
			return TEX_AIR;
	}
}

void CalculateUVsOfBlock(float* out, enum BLOCK_TEX_NAMES texName)
{
	float blockTextureUVs[6];
	GetBlockTexture(blockTextureUVs, texName);

	float ret[12];

	// topX0
	ret[0] = blockTextureUVs[0] / g_SPRITE_SHEET.sheet.width;
	// topX1
	ret[1] = (blockTextureUVs[0] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	// topY0
	ret[2] = blockTextureUVs[1] / g_SPRITE_SHEET.sheet.width;
	// topY1
	ret[3] = (blockTextureUVs[1] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;

	// aroundX0
	ret[4] = blockTextureUVs[2] / g_SPRITE_SHEET.sheet.height;
	// aroundX1
	ret[5] = (blockTextureUVs[2] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;
	// aroundY0
	ret[6] = blockTextureUVs[3] / g_SPRITE_SHEET.sheet.height;
	// aroundY1
	ret[7] = (blockTextureUVs[3] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	// bottomX0
	ret[8] = blockTextureUVs[4] / g_SPRITE_SHEET.sheet.width;
	// bottomX1
	ret[9] = (blockTextureUVs[4] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	// bottomY0
	ret[10] = blockTextureUVs[5] / g_SPRITE_SHEET.sheet.height;
	// bottomY1
	ret[11] = (blockTextureUVs[5] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	memcpy(out, ret, 12 * sizeof(float));
}

u8* ChunkFlattenIndex(u16 index)
{
	u8 z = index / (CHUNK_WIDTH * CHUNK_HEIGHT);
	index -= (z * CHUNK_WIDTH * CHUNK_HEIGHT);
	u8 y = index / CHUNK_WIDTH;
	u8 x = index % CHUNK_WIDTH;

	u8* ret = malloc(3 * sizeof(u8));
	ret[0] = x;
	ret[1] = y;
	ret[2] = z;

	return ret;
}

void SetNeighboringBlocks(struct Chunk* chunk, u8 x, u8 y, u8 z)
{
	struct Block* curBlock = &chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z)];

	curBlock->neighbors.left =   (x != 0) ? &chunk->blocks[CHUNK_BLOCK_INDEXER(x-1, y, z)] : NULL;
	curBlock->neighbors.right =  (x != CHUNK_WIDTH-1) ? &chunk->blocks[CHUNK_BLOCK_INDEXER(x+1, y, z)] : NULL;

	curBlock->neighbors.above =  (y != CHUNK_HEIGHT-1) ? &chunk->blocks[CHUNK_BLOCK_INDEXER(x, y+1, z)] : NULL;
	curBlock->neighbors.below =  (y != 0) ? &chunk->blocks[CHUNK_BLOCK_INDEXER(x, y-1, z)] : NULL;

	curBlock->neighbors.front =  (z != 0) ? &chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z-1)] : NULL;
	curBlock->neighbors.behind = (z != CHUNK_DEPTH-1) ? &chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z+1)] : NULL;
	
}

void SetNeighboringBlocksOfChunk(struct Chunk* chunk)
{
	for (int y = 0; y < CHUNK_HEIGHT; ++y)
		for (int z = 0; z < CHUNK_DEPTH; ++z)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
				SetNeighboringBlocks(chunk, x, y, z);
}

void SetChunkInnerBlocksInvisible(struct Chunk* chunk)
{
	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int y = 0; y < CHUNK_HEIGHT; ++y)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
			{
				// If it has neighbors in all direction, then it is inside
				struct Block* cur = &chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z)];
				if (
					cur->neighbors.above &&
					cur->neighbors.below &&
					cur->neighbors.left &&
					cur->neighbors.right &&
					cur->neighbors.front &&
					cur->neighbors.behind
					)
					cur->isVisible = false;
			}
}

void CullBackFaces(struct Chunk* chunk)
{
	vec3s cameraPos = g_MainCamera.position;
	
	for (int z = 0; z < CHUNK_DEPTH; z++)
		for (int y = 0; y < CHUNK_HEIGHT; y++)
			for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		if (x != 0 && y != 0 && z != 0 && x != CHUNK_WIDTH-1 && y != CHUNK_HEIGHT-1 && z != CHUNK_DEPTH-1)
		{
			// Left
			if (cameraPos.x > chunk->position.x + 0.5f)
				chunk->blocks[CHUNK_BLOCK_INDEXER(0,y,z)].isVisible = false;
			else
				chunk->blocks[CHUNK_BLOCK_INDEXER(0,y,z)].isVisible = true;

			// Right
			if (cameraPos.x < chunk->position.x + CHUNK_WIDTH - 0.5f)
				chunk->blocks[CHUNK_BLOCK_INDEXER(CHUNK_WIDTH-1,y,z)].isVisible = false;
			else
				chunk->blocks[CHUNK_BLOCK_INDEXER(CHUNK_WIDTH-1,y,z)].isVisible = true;

			// Top
			if (cameraPos.y < chunk->position.y + CHUNK_HEIGHT - 0.5f)
				chunk->blocks[CHUNK_BLOCK_INDEXER(x,CHUNK_HEIGHT-1,z)].isVisible = false;
			else
				chunk->blocks[CHUNK_BLOCK_INDEXER(x,CHUNK_HEIGHT-1,z)].isVisible = true;
						
			// Bottom
			if (cameraPos.y > chunk->position.y + 0.5f)
				chunk->blocks[CHUNK_BLOCK_INDEXER(x,0,z)].isVisible = false;
			else
				chunk->blocks[CHUNK_BLOCK_INDEXER(x,0,z)].isVisible = true;
			
			// Back
			if (cameraPos.z > chunk->position.z + 0.5f)
				chunk->blocks[CHUNK_BLOCK_INDEXER(x,y,0)].isVisible = false;
			else
				chunk->blocks[CHUNK_BLOCK_INDEXER(x,y,0)].isVisible = true;

			// Front
			if (cameraPos.z < chunk->position.z + CHUNK_DEPTH - 0.5f)
				chunk->blocks[CHUNK_BLOCK_INDEXER(x,y,CHUNK_DEPTH-1)].isVisible = false;
			else
				chunk->blocks[CHUNK_BLOCK_INDEXER(x,y,CHUNK_DEPTH-1)].isVisible = true;
		}
	}

}