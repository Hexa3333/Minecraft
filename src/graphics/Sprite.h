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
	char** lookupTable;
};
extern struct SpriteSheet g_SPRITE_SHEET;

typedef struct SheetIndex
{
	float x,y;
} sheetindex_t;

//#define SPRITESHEET_BLOCK(NAME)
/*
 *	DirtGrass, Dirt, Rock, Water, Sand, Tree,
 *	Leaves, TNT, Glass, Gold, Diamond, RedThing,
 *	Wood, Coal
 * */

void SpriteSetup();
struct Sprite CreateSprite(const char* path, enum ImageType);
void BuildSpriteSheet(const char* path, enum ImageType, float tileCountX, float tileCountY);
float* GetSpriteXYFromTable(u8 tileIndexX, u8 tileIndexY);
void UseSprite(struct Sprite* sprite);
void DeleteSprite(struct Sprite* sprite);

#endif // SPRITE_H
