#include "Chunk.h"
#include "Sprite.h"
#include "Shader.h"

struct Chunk CreateChunk(double x, double z)
{
	struct Chunk ret = { x, z };
	ret.blocks = malloc(CHUNK_WIDTH * CHUNK_DEPTH * sizeof(struct Block));

	for (int i = 0; i < CHUNK_WIDTH * CHUNK_DEPTH; ++i)
		ret.blocks[i] = CreateBlock(&g_TerrainShader, DIRTWGRASS);

	return ret;
};

void DrawChunk(struct Chunk* chunk)
{
	for (int w = 0; w < CHUNK_WIDTH; ++w)
		for (int d = 0; d < CHUNK_DEPTH; ++d)
		{
			struct Block* cur = &chunk->blocks[w*CHUNK_WIDTH + d];
			cur->model = glms_translate(GLMS_MAT4_IDENTITY, (vec3s) { chunk->x + w, 0, chunk->z + d });
			DrawGameObject(cur);
		}
}

void FreeChunk(struct Chunk* chunk)
{
	free(chunk->blocks);
}
