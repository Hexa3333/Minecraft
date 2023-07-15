#include "Chunk.h"
#include "util.h"

struct Chunk CreateChunk(u32 x, u32 z)
{
	struct Chunk ret;
	ret.position.x = x;
	ret.position.y = 0;
	ret.position.z = z;

	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		int indexer = CHUNK_INDEXER(x,z);
		ret.blocks[indexer].position = (vec3s){ret.position.x + x, ret.position.y + 0, ret.position.z + z};
		ret.blocks[indexer] = CreateBlock(&g_TerrainShader, DIRTWGRASS, ret.blocks[indexer].position);
		ret.blocks[indexer].model = glms_translate(GLMS_MAT4_IDENTITY, ret.blocks[indexer].position);

		GetNeighboringBlocks(&ret, CHUNK_INDEXER(x,z));
	}

	return ret;
}

void DrawChunk(struct Chunk* chunk)
{
	for (int i = 0; i <	CHUNK_TOTAL_BLOCKS; ++i)
		DrawGameObject(&chunk->blocks[i]);
}

