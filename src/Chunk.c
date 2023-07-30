#include "Chunk.h"
#include "graphics/Sprite.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "util.h"

static const char* ChunksFolder = "GameData/";

struct Chunk CreateChunk(vec3s position)
{
	if (GetChunkFileExists(position)) return LoadChunk(position);

	struct Chunk ret = { 0 };
	ret.position = position;
	ret.blocks = malloc(CHUNK_WIDTH * CHUNK_DEPTH * CHUNK_HEIGHT * sizeof(struct Block));

	for (int y = 0; y < CHUNK_HEIGHT; ++y)
		for (int z = 0; z < CHUNK_DEPTH; ++z)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		ret.blocks[CHUNK_BLOCK_INDEXER(x, y, z)] = CreateBlock(&g_TerrainShader, BLOCK_STONE, (vec3s) { position.x + x, position.y + y, position.z + z });
	}

	SetNeighboringBlocksOfChunk(&ret);
	SetChunkInnerBlocksInvisible(&ret);

	return ret;
}

void UpdateChunk(struct Chunk* chunk)
{
	for (int y = 0; y < CHUNK_HEIGHT; ++y)
		for (int z = 0; z < CHUNK_DEPTH; ++z)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		if (chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z)].type != BLOCK_STONE)
			chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z)] = CreateBlock(&g_TerrainShader, chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z)].type, chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z)].position);
	}
}

void DrawChunk(struct Chunk* chunk)
{
	//CullBackFaces(chunk);
	for (int y = 0; y < CHUNK_HEIGHT; ++y)
		for (int z = 0; z < CHUNK_DEPTH; ++z)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		if (chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z)].isVisible)
		{
			DrawBlock(&chunk->blocks[CHUNK_BLOCK_INDEXER(x, y, z)]);
		}
	}
}

struct Chunk_Instanced CreateChunk_Instanced(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position, vec3s* offsets, u32 nOffsets)
{
	enum BLOCK_TEX_NAMES texName = MapBlocksToTextures(blockType);
	float blockTextureUVs[6];
	GetBlockTexture(blockTextureUVs, texName);

	float uv_topX0 = blockTextureUVs[0] / g_SPRITE_SHEET.sheet.width;
	float uv_topX1 = (blockTextureUVs[0] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	float uv_topY0 = blockTextureUVs[1] / g_SPRITE_SHEET.sheet.width;
	float uv_topY1 = (blockTextureUVs[1] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;

	float uv_aroundX0 = blockTextureUVs[2] / g_SPRITE_SHEET.sheet.height;
	float uv_aroundX1 = (blockTextureUVs[2] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;
	float uv_aroundY0 = blockTextureUVs[3] / g_SPRITE_SHEET.sheet.height;
	float uv_aroundY1 = (blockTextureUVs[3] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	float uv_bottomX0 = blockTextureUVs[4] / g_SPRITE_SHEET.sheet.width;
	float uv_bottomX1 = (blockTextureUVs[4] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	float uv_bottomY0 = blockTextureUVs[5] / g_SPRITE_SHEET.sheet.height;
	float uv_bottomY1 = (blockTextureUVs[5] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	float cubeVertices[] = {
		// VERTICES				UVs						NORMALS
		// Back face
		-0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom left far
		 0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top right far
		 0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom right far
		 0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, -1.0f, // bottom right far
		-0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom left far
		-0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top left far
		// Front face
		-0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom left near
		 0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom right near
		 0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top right near
		 0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top right near
		-0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top left near
		-0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom left near
		// Left face
		-0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top lef near
		-0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top left far
		-0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left far
		-0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left far
		-0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left near
		-0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top left near
		// Right face
		 0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, 1.0f, 0.0f, 0.0f, // top right near
		 0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, 1.0f, 0.0f, 0.0f, // bottom right far
		 0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1,	1.0f, 0.0f, 0.0f, // top right far
		 0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0,	1.0f, 0.0f, 0.0f, // bottom right far
		 0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1,	1.0f, 0.0f, 0.0f, // top right far
		 0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0,	1.0f, 0.0f, 0.0f, // bottom right far 
		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom left far
		  0.5f, -0.5f, -0.5f,  uv_bottomX0, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom right far
		  0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom right near
		  0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom right near
		 -0.5f, -0.5f,  0.5f,  uv_bottomX1, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom left near
		 -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom left far
		 // Top face
		 -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, 0.0f, 1.0f, 0.0f, // top left far
		  0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, 0.0f, 1.0f, 0.0f, // top right near
		  0.5f,  0.5f, -0.5f,  uv_topX1, uv_topY1, 0.0f, 1.0f, 0.0f, // top right far
		  0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, 0.0f, 1.0f, 0.0f, // top right near
		 -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, 0.0f, 1.0f, 0.0f, // top left far
		 -0.5f,  0.5f,  0.5f,  uv_topX0, uv_topY0, 0.0f, 1.0f, 0.0f // top left near
	};

	struct Chunk_Instanced ret;
	ret.buffer = CreateBufferVTNA_Instanced(cubeVertices, sizeof(cubeVertices), offsets, nOffsets);
	ret.shader = shader;
	ret.position = position;
	ret.model = glms_translate(GLMS_MAT4_IDENTITY, ret.position);
	ret.type = blockType;
	memset(&ret.neighbors, 0, 6 * sizeof(struct Block*));

	return ret;
}

void DrawChunk_Instanced(struct Chunk_Instanced* chunk)
{
	UseShader(chunk->shader);
	SendSun(chunk->shader);
	SendUniformMat4(chunk->shader, "model", &chunk->model);
	SendUniformMat4(chunk->shader, "view", &g_View);
	SendUniformMat4(chunk->shader, "projection", &g_Projection);
	DrawBufferA_Instanced(&chunk->buffer);
}

char* GetChunkFileName(vec3s position)
{
	u32 x = position.x / CHUNK_WIDTH;
	u32 z = position.z / CHUNK_DEPTH;

	u8 xFigures = 1;
	u8 zFigures = 1;

	u32 xBak = x;
	u32 zBak = z;
	while (x /= 10) ++xFigures;
	while (z /= 10) ++zFigures;

	x = xBak;
	z = zBak;

	// 7: c h u n k _ _
	char* name = malloc(7 + xFigures + zFigures + 1);

	char x_Str[7];
	char z_Str[7];
	sprintf(x_Str, "%u", x);
	sprintf(z_Str, "%u", z);

	sprintf(name, "chunk_%s_%s", x_Str, z_Str);

	return name;
}

char* GetChunkFilePath(vec3s position)
{
	char* fileName = GetChunkFileName(position);

	char* path = malloc(strlen(fileName) + strlen(ChunksFolder) + 1);
	strcpy(path, ChunksFolder);
	strcpy(path + strlen(ChunksFolder), fileName);

	free(fileName);

	return path;
}

bool GetChunkFileExists(vec3s position)
{
	char* filePath = GetChunkFilePath(position);
	FILE* checkFp = fopen(filePath, "rb");
	free(filePath);

	if (!checkFp) return 0;
	else return 1;
}

void WriteChunk(struct Chunk* chunk)
{
	u32 x = chunk->position.x / CHUNK_WIDTH;
	u32 z = chunk->position.z / CHUNK_DEPTH;

	char* filePath = GetChunkFilePath(chunk->position);
	FILE* fp = fopen(filePath, "wb");
	if (!fp)
	{
		char* name = GetChunkFileName(chunk->position);
		u8 nameLen = strlen(name);

		ERR("Failed to save chunk: %s", name);
		free(name);
		return;
	}

	#define CH_DATA_SIZE CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH
	unsigned char* blockBuffer = malloc(CH_DATA_SIZE);
	for (int i = 0; i < CH_DATA_SIZE; ++i)
	{
		blockBuffer[i] = (unsigned char)chunk->blocks[i].type;
	}

	fwrite(blockBuffer, 1, CH_DATA_SIZE, fp); // 1 byte is enough

	fclose(fp);
	free(blockBuffer);
	free(filePath);
}

struct Chunk LoadChunk(vec3s position)
{
	struct Chunk ret;
	const char* filePath = GetChunkFilePath(position);
	FILE* fp = fopen(filePath, "rb");

	#define CH_DATA_SIZE CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH
	unsigned char* blockBuffer = malloc(CH_DATA_SIZE);
	fread(blockBuffer, 1, CH_DATA_SIZE, fp);

	ret.blocks = malloc(CHUNK_WIDTH * CHUNK_DEPTH * CHUNK_HEIGHT * sizeof(struct Block));
	for (int y = 0; y < CHUNK_HEIGHT; ++y)
		for (int z = 0; z < CHUNK_DEPTH; ++z)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		ret.blocks[CHUNK_BLOCK_INDEXER(x, y, z)] = CreateBlock(&g_TerrainShader, blockBuffer[CHUNK_BLOCK_INDEXER(x,y,z)], (vec3s) { position.x + x, position.y + y, position.z + z });
	}

	SetNeighboringBlocksOfChunk(&ret);
	SetChunkInnerBlocksInvisible(&ret);

	fclose(fp);
	free(filePath);
	free(blockBuffer);
	return ret;
}