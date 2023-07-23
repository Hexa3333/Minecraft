#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Buffer.h"
#include "Shader.h"
#include "Sprite.h"
#include <cglm/struct.h>

struct Block
{
	struct Buffer_Instanced buffer;
	struct Shader* shader;
	vec3s position;
	mat4s model;
	enum BLOCK_TYPE type;

	struct {
		bool isVisible: 1;
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

enum BLOCK_TYPE
{
	BLOCK_AIR, BLOCK_STONE,
	BLOCK_DIRT,
	BLOCK_WATER,
	BLOCK_COAL
};

struct Block CreateBlock(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position);
struct Block CreateChunk(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position, vec3s* offsets, u32 nOffsets);
void DrawBlock(struct Block* go);

#endif // GAMEOBJECT_H
