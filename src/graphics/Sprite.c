#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Sprite.h"

struct SpriteSheet g_SPRITE_SHEET;

void SpriteSetup()
{
	stbi_set_flip_vertically_on_load(0);
}

struct Sprite CreateSprite(const char* path, enum ImageType imageType)
{
	struct Sprite ret;
	glGenTextures(1, &ret.texObj);
	glBindTexture(GL_TEXTURE_2D, ret.texObj);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	ubyte* data = stbi_load(path, &ret.width, &ret.height, &ret.nrChannels, 0);
	
	if (!data) ERR("Failed to load a sprite.");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ret.width, ret.height, 0, (imageType) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

#ifdef DEBUG
	glBindTexture(GL_TEXTURE_2D, 0);
#endif
	return ret;
}

void BuildSpriteSheet(const char* path, enum ImageType imgType, float tileCountX, float tileCountY)
{
	g_SPRITE_SHEET.sheet = CreateSprite(path, imgType);
	g_SPRITE_SHEET.tileWidth = g_SPRITE_SHEET.sheet.width / tileCountX;
	g_SPRITE_SHEET.tileHeight = g_SPRITE_SHEET.sheet.height / tileCountY;
	//g_SPRITE_SHEET.lookupTable = malloc(blabla);
}

// TODO: Find a better way maybe
float* GetSpriteXYFromTable(u8 tileIndexX, u8 tileIndexY)
{
	float x = g_SPRITE_SHEET.tileWidth * tileIndexX;
	float y = g_SPRITE_SHEET.tileHeight * tileIndexY;
	float* ret = malloc(2 * sizeof(float));
	ret[0] = x;
	ret[1] = y;

	return ret;
}

void UseSprite(struct Sprite* sprite)
{
	glBindTexture(GL_TEXTURE_2D, sprite->texObj);
}

void DeleteSprite(struct Sprite* sprite)
{
	glDeleteTextures(1, &sprite->texObj);
}
