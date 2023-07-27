#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 16

#define CHUNK_BLOCK_INDEXER(x,y,z) x + CHUNK_WIDTH * (y + CHUNK_DEPTH * z)

#include "graphics/Buffer.h"
#include "graphics/Shader.h"
#include "Block.h"

struct Chunk
{
	struct Block* blocks;
	struct Shader* shader;
	vec3s position;
};

struct Chunk CreateChunk(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position);
void DrawChunk(struct Chunk* chunk);

// Literally an instanced Block
struct Chunk_Instanced
{
	struct Buffer_Instanced buffer;
	struct Shader* shader;
	vec3s position;
	mat4s model;
	enum BLOCK_TYPE type;

	struct
	{
		struct Block* above;
		struct Block* below;
		struct Block* left;
		struct Block* right;
		struct Block* front;
		struct Block* behind;
	} neighbors;
};

struct Chunk_Instanced CreateChunk_Instanced(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position, vec3s* offsets, u32 nOffsets);
void DrawChunk_Instanced(struct Chunk_Instanced* chunk);

// IO
char* GetChunkFileName(struct Chunk* chunk);
char* GetChunkFilePath(struct Chunk* chunk);

void WriteChunk(struct Chunk* chunk);
void ModifyChunk(struct Chunk* chunk, u8 x, u8 y, u8 z);

#endif // CHUNK_H