#include "Chunk.h"
#include "util.h"

struct ChunkMap chunkMap;
struct Chunk CreateChunk(u32 x, u32 z)
{
	struct Chunk ret;
	ret.positionX = x;
	ret.positionZ = z;

	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		int indexer = CHUNK_INDEXER(x,z);
		ret.blocks[indexer].position = (vec3s){ret.positionX + x, 0, ret.positionZ + z};
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

void SetChunkMap()
{
	chunkMap.chunksInView = RENDER_DISTANCE;
	printf("Chunks in view: %u\n", chunkMap.chunksInView);
	for (int x = 0; x < 4; ++x)
		for (int z = 0; z < 4; ++z)
			chunkMap.chunks[CHUNK_INDEXER(x,z)] = CreateChunk(x*CHUNK_WIDTH, z*CHUNK_DEPTH);
}
void DrawChunkMap()
{
	for (int i = 0; i < chunkMap.chunksInView; ++i)
		DrawChunk(&chunkMap.chunks[i]);
}
