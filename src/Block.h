#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "graphics/Buffer.h"
#include "graphics/Shader.h"
#include "graphics/Sprite.h"
#include <cglm/struct.h>

struct Block
{
	struct Buffer buffer;
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

enum BLOCK_TYPE
{
	BLOCK_AIR,
	BLOCK_STONE,
	BLOCK_DIRT,
	BLOCK_WATER,
	BLOCK_COAL
};

struct Block CreateBlock(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position);
void SetBlockProperties(struct Block* block);
void DrawBlock(struct Block* go);

#endif // GAMEOBJECT_H
