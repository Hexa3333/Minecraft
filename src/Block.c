#include "Block.h"
#include "graphics/Camera.h"
#include "util.h"

struct Block CreateBlock(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position)
{
	enum BLOCK_TEX_NAMES texName = MapBlocksToTextures(blockType);

	float UVs[12];
	CalculateUVsOfBlock(UVs, texName);

	float cubeVertices[] = {
		// VERTICES				UVs						NORMALS
	    // Back face
	    -0.5f, -0.5f, -0.5f,  UVs[4], UVs[6], 0.0f, 0.0f, -1.0f, // bottom left far
	     0.5f,  0.5f, -0.5f,  UVs[5], UVs[7], 0.0f, 0.0f, -1.0f, // top right far
	     0.5f, -0.5f, -0.5f,  UVs[5], UVs[6], 0.0f, 0.0f, -1.0f, // bottom right far
	     0.5f,  0.5f, -0.5f,  UVs[5], UVs[7], 0.0f, 0.0f, -1.0f, // bottom right far
	    -0.5f, -0.5f, -0.5f,  UVs[4], UVs[6], 0.0f, 0.0f, -1.0f, // bottom left far
	    -0.5f,  0.5f, -0.5f,  UVs[4], UVs[7], 0.0f, 0.0f, -1.0f, // top left far
	    // Front face
	    -0.5f, -0.5f,  0.5f,  UVs[4], UVs[6], 0.0f, 0.0f, 1.0f, // bottom left near
	     0.5f, -0.5f,  0.5f,  UVs[5], UVs[6], 0.0f, 0.0f, 1.0f, // bottom right near
	     0.5f,  0.5f,  0.5f,  UVs[5], UVs[7], 0.0f, 0.0f, 1.0f, // top right near
	     0.5f,  0.5f,  0.5f,  UVs[5], UVs[7], 0.0f, 0.0f, 1.0f, // top right near
	    -0.5f,  0.5f,  0.5f,  UVs[4], UVs[7], 0.0f, 0.0f, 1.0f, // top left near
	    -0.5f, -0.5f,  0.5f,  UVs[4], UVs[6], 0.0f, 0.0f, 1.0f, // bottom left near
	    // Left face
	    -0.5f,  0.5f,  0.5f,  UVs[5], UVs[7], -1.0f, 0.0f, 0.0f, // top lef near
	    -0.5f,  0.5f, -0.5f,  UVs[4], UVs[7], -1.0f, 0.0f, 0.0f, // top left far
	    -0.5f, -0.5f, -0.5f,  UVs[4], UVs[6], -1.0f, 0.0f, 0.0f, // bottom left far
	    -0.5f, -0.5f, -0.5f,  UVs[4], UVs[6], -1.0f, 0.0f, 0.0f, // bottom left far
	    -0.5f, -0.5f,  0.5f,  UVs[5], UVs[6], -1.0f, 0.0f, 0.0f, // bottom left near
	    -0.5f,  0.5f,  0.5f,  UVs[5], UVs[7], -1.0f, 0.0f, 0.0f, // top left near
	    // Right face
	     0.5f,  0.5f,  0.5f,  UVs[4], UVs[7], 1.0f, 0.0f, 0.0f, // top right near
	     0.5f, -0.5f, -0.5f,  UVs[5], UVs[6], 1.0f, 0.0f, 0.0f, // bottom right far
	     0.5f,  0.5f, -0.5f,  UVs[5], UVs[7],	1.0f, 0.0f, 0.0f, // top right far
	     0.5f, -0.5f, -0.5f,  UVs[5], UVs[6],	1.0f, 0.0f, 0.0f, // bottom right far
	     0.5f,  0.5f,  0.5f,  UVs[4], UVs[7],	1.0f, 0.0f, 0.0f, // top right far
	     0.5f, -0.5f,  0.5f,  UVs[4], UVs[6],	1.0f, 0.0f, 0.0f, // bottom right far 
	    // Bottom face
	    -0.5f, -0.5f, -0.5f,  UVs[9], UVs[11], 0.0f, -1.0f, 0.0f, // bottom left far
	     0.5f, -0.5f, -0.5f,  UVs[8], UVs[11], 0.0f, -1.0f, 0.0f, // bottom right far
	     0.5f, -0.5f,  0.5f,  UVs[8], UVs[10], 0.0f, -1.0f, 0.0f, // bottom right near
	     0.5f, -0.5f,  0.5f,  UVs[8], UVs[10], 0.0f, -1.0f, 0.0f, // bottom right near
	    -0.5f, -0.5f,  0.5f,  UVs[9], UVs[10], 0.0f, -1.0f, 0.0f, // bottom left near
	    -0.5f, -0.5f, -0.5f,  UVs[9], UVs[11], 0.0f, -1.0f, 0.0f, // bottom left far
	    // Top face
	    -0.5f,  0.5f, -0.5f,  UVs[0], UVs[3], 0.0f, 1.0f, 0.0f, // top left far
	     0.5f,  0.5f,  0.5f,  UVs[1], UVs[2], 0.0f, 1.0f, 0.0f, // top right near
	     0.5f,  0.5f, -0.5f,  UVs[1], UVs[3], 0.0f, 1.0f, 0.0f, // top right far
	     0.5f,  0.5f,  0.5f,  UVs[1], UVs[2], 0.0f, 1.0f, 0.0f, // top right near
	    -0.5f,  0.5f, -0.5f,  UVs[0], UVs[3], 0.0f, 1.0f, 0.0f, // top left far
	    -0.5f,  0.5f,  0.5f,  UVs[0], UVs[2], 0.0f, 1.0f, 0.0f // top left near
	};
	
	struct Block ret;
	ret.buffer = CreateBufferVTNA(cubeVertices, sizeof(cubeVertices));
	ret.shader = shader;
	ret.position = position;
	ret.model = glms_translate(GLMS_MAT4_IDENTITY, ret.position);
	ret.type = blockType;
	ret.isVisible = (blockType != BLOCK_AIR) ? true : false;
	memset(&ret.neighbors, 0, 6*sizeof(struct Block*));

	return ret;
}

void SetBlockProperties(struct Block* block)
{
	switch (block->type)
	{

	}
}

void DrawBlock(struct Block* go)
{
#ifdef NO_SPRITE_SHEET
	UseSprite(&go->sprite);
#endif
	UseShader(go->shader);
	SendSun(go->shader);
	SendUniformMat4(go->shader, "model", &go->model); 
	SendUniformMat4(go->shader, "view", &g_View); 
	SendUniformMat4(go->shader, "projection", &g_Projection); 
	DrawBufferA(&go->buffer);
}