#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 16

#include "graphics/Buffer.h"

// Literally an instanced Block
struct Chunk
{
	struct Buffer_Instanced buffer;
	struct Shader* shader;
	vec3s position;
	mat4s model;
	enum BLOCK_TYPE type;

	struct {
		bool isVisible : 1;
	} props;

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

struct Chunk CreateChunk(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position, vec3s* offsets, u32 nOffsets);
void DrawChunk(struct Chunk* chunk);

#endif // CHUNK_H