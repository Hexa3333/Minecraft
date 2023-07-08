#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include "../common.h"

struct Sprite
{
	i32 width, height, nrChannels;
	GLuint texObj;
};

enum ImageType
{
	RGB = 0,
	RGBA = 1
};

struct SpriteSheet
{
	struct Sprite sheet;
	float tileWidth, tileHeight;
};
extern struct SpriteSheet g_SPRITE_SHEET;
enum BLOCK_TEX_NAMES
{
	DIRTWGRASS,
	DIRT,
	TREE,
	ROCK,
	SAND
};

void SpriteSetup();

struct Sprite CreateSprite(const char* path, enum ImageType);
void BuildSpriteSheet(const char* path, enum ImageType, float tileCountX, float tileCountY);
float* GetSpriteXYFromSheet(u8 tileIndexX, u8 tileIndexY);
void GetBlockTexture(float* arr, enum BLOCK_TEX_NAMES texName);

void BindSprite(struct Sprite* sprite);
void DeleteSprite(struct Sprite* sprite);

#endif // SPRITE_H
