#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "graphics/Buffer.h"
#include "graphics/Shader.h"
#include "graphics/Sprite.h"
#include <cglm/struct.h>

struct GameObject
{
	struct Buffer buffer;
	struct Shader shader;
#ifdef NO_SPRITE_SHEET
	struct Sprite sprite;
#endif
	mat4s model;
	void (*render)(struct Buffer* buffer);
};

#ifdef NO_SPRITE_SHEET
struct GameObject CreateGameObject(struct Buffer* buffer, struct Shader* shader, struct Sprite* sprite);
#else
struct GameObject CreateGameObject(struct Buffer* buffer, struct Shader* shader);
struct GameObject CreateVoxelGameObject(struct Shader* shader, float sheetIndexTopX, float sheetIndexTopY, float sheetIndexAroundX, float sheetIndexAroundY, float sheetIndexBottomX, float sheetIndexBottomY);
#endif
void DrawGameObject(struct GameObject* go);

#endif // GAMEOBJECT_H
