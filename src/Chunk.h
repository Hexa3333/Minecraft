#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 8
#define CHUNK_DEPTH 16

#define CHUNK_BLOCK_INDEXER(_x,_y,_z) _x + (_y * CHUNK_WIDTH) + (_z * CHUNK_WIDTH * CHUNK_HEIGHT)

#include "graphics/Buffer.h"
#include "graphics/Shader.h"
#include "Block.h"

struct Chunk
{
	struct Block* blocks;
	vec3s position;
};

struct Chunk CreateChunk(vec3s position);
void UpdateChunk(struct Chunk* chunk);
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
char* GetChunkFileName(vec3s position);
char* GetChunkFilePath(vec3s position);

bool GetChunkFileExists(vec3s position);

void WriteChunk(struct Chunk* chunk);
struct Chunk LoadChunk(vec3s position);

#endif // CHUNK_H