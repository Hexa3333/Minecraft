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
	enum BLOCK_TYPE type;

	struct {
		bool isVisible: 1;
		bool isTransparent: 1;
		bool canLeaveParticles: 1;
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

struct Block CreateGameObject(struct Buffer* buffer, struct Shader* shader);
struct Block CreateGameObjectSpex(struct Buffer* buffer, struct Shader* shader, void* func);
struct Block CreateBlock(struct Shader* shader, enum BLOCK_TYPE texName, vec3s position);
void DrawGameObject(struct Block* go);
void DestroyGameObject(struct Block* go);

#endif // GAMEOBJECT_H
