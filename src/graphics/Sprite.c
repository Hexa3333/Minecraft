#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Sprite.h"

struct SpriteSheet g_SPRITE_SHEET;

void SpriteSetup()
{
	stbi_set_flip_vertically_on_load(1);
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

#ifdef MC_DEBUG
	glBindTexture(GL_TEXTURE_2D, 0);
#endif
	return ret;
}

void BuildSpriteSheet(const char* path, enum ImageType imgType, float tileCountX, float tileCountY)
{
	g_SPRITE_SHEET.sheet = CreateSprite(path, imgType);
	g_SPRITE_SHEET.tileWidth = g_SPRITE_SHEET.sheet.width / tileCountX;
	g_SPRITE_SHEET.tileHeight = g_SPRITE_SHEET.sheet.height / tileCountY;
}

void GetBlockTexture(float* arr, enum BLOCK_TEX_NAMES texName)
{
	static float BlockTextureIndexes[5][6] =
	{
		// TOP - AROUND- BOTTOM
		{ 0,0, 0,0, 0,0 },  // AIR
		{ 5,2, 5,2, 5,2 },	// ROCK
		{ 4,4, 3,4, 5,4 },  // DIRTWGRASS
		{ 5,4, 5,4, 5,4 },  // DIRT
		{ 3,5, 3,5, 3,5 }	// SAND
	};

	for (int i = 0; i < 6; i+=2)
	{
		arr[i] = g_SPRITE_SHEET.tileWidth * (BlockTextureIndexes[texName][i]-1);
		arr[i+1] = g_SPRITE_SHEET.sheet.height - (g_SPRITE_SHEET.tileHeight * BlockTextureIndexes[texName][i+1]);
	}
}

void BindSprite(struct Sprite* sprite)
{
	glBindTexture(GL_TEXTURE_2D, sprite->texObj);
}

void DeleteSprite(struct Sprite* sprite)
{
	glDeleteTextures(1, &sprite->texObj);
}
