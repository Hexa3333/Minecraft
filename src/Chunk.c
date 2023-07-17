#include "Chunk.h"
#include "util.h"
#include "graphics/Camera.h"

struct _ChunkMap g_ChunkMap;
static u64 chunkIdIndex = 0;

struct Chunk CreateChunk(u32 x, u32 z)
{
	struct Chunk ret;
	ret.position.x = x;
	ret.position.y = 0;
	ret.position.z = z;

	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int y = 0; y < CHUNK_HEIGHT; ++y)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		
		ret.blocks[CHUNK_INDEX(x,y,z)].position = (vec3s){ret.position.x + x, ret.position.y + y, ret.position.z + z};
		ret.blocks[CHUNK_INDEX(x,y,z)] = CreateBlock(&g_TerrainShader, DIRTWGRASS, ret.blocks[y][z][x].position);
		ret.blocks[CHUNK_INDEX(x,y,z)].model = glms_translate(GLMS_MAT4_IDENTITY, ret.blocks[y][z][x].position);
		
		SetNeighboringBlocks(&ret, x,y,z);
	}

	ret.id = chunkIdIndex;
	++chunkIdIndex;

	SetChunkInnerBlocksInvisible(&ret);
	return ret;
}

void DrawChunk(struct Chunk* chunk)
{
	CullBackFaces(chunk);
	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int y = 0; y < CHUNK_HEIGHT; ++y)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
				if (chunk->blocks[CHUNK_INDEX(x,y,z)].props.isVisible && !chunk->blocks[CHUNK_INDEX(x,y,z)].props.isTransparent)
					DrawGameObject(&chunk->blocks[CHUNK_INDEX(x,y,z)]);
}

void ChunkMapSetup()
{
	u8 chunkIdIndex = 0;

	for (int z = 0; z < MAX_VISIBLE_CHUNKS_Z; z++)
		for (int x = 0; x < MAX_VISIBLE_CHUNKS_X; x++)
	{
			g_ChunkMap.chunks[CHUNK_MAP_INDEX(x,z)] = CreateChunk(x*CHUNK_WIDTH, z*CHUNK_DEPTH);
	}

}
