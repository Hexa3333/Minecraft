#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Buffer.h"
#include "Shader.h"
#include "Sprite.h"
#include <cglm/struct.h>

struct Block
{
	struct Buffer buffer;
	struct Shader* shader;
	vec3s position;
	mat4s model;
	void (*render)(struct Buffer* buffer);
};

enum Direction
{
	FRONT = 1,
	BACK = -1,

	UP = 2,
	DOWN = -2,

	LEFT = -3,
	RIGHT = 3
};


static vec3s Faces[6] = {
	{ 0, 0, 1 }, // BACK
	{ 0, 0, -1 }, // FRONT 

	{ 0, 1, 0 }, // UP
	{ 0, -1, 0 }, // DOWN

	{ -1, 0, 0 }, // LEFT
	{ 1, 0, 0 }, // RIGHT
};

struct Block CreateGameObject(struct Buffer* buffer, struct Shader* shader);
struct Block CreateGameObjectSpex(struct Buffer* buffer, struct Shader* shader, void* func);
struct Block CreateBlock(struct Shader* shader, enum BLOCK_TEX_NAMES texName);
void DrawGameObject(struct Block* go);
void DestroyGameObject(struct Block* go);

#endif // GAMEOBJECT_H
