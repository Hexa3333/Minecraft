#include "Block.h"
#include "Camera.h"
#include "../util.h"

struct Block CreateBlock(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position)
{
	enum BLOCK_TEX_NAMES texName = MapBlocksToTextures(blockType);
	float blockTextureUVs[6];
	GetBlockTexture(blockTextureUVs, texName);

	float uv_topX0 = blockTextureUVs[0] / g_SPRITE_SHEET.sheet.width;
	float uv_topX1 = (blockTextureUVs[0] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	float uv_topY0 = blockTextureUVs[1] / g_SPRITE_SHEET.sheet.width;
	float uv_topY1 = (blockTextureUVs[1] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;

	float uv_aroundX0 = blockTextureUVs[2] / g_SPRITE_SHEET.sheet.height;
	float uv_aroundX1 = (blockTextureUVs[2] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;
	float uv_aroundY0 = blockTextureUVs[3] / g_SPRITE_SHEET.sheet.height;
	float uv_aroundY1 = (blockTextureUVs[3] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	float uv_bottomX0 = blockTextureUVs[4] / g_SPRITE_SHEET.sheet.width;
	float uv_bottomX1 = (blockTextureUVs[4] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	float uv_bottomY0 = blockTextureUVs[5] / g_SPRITE_SHEET.sheet.height;
	float uv_bottomY1 = (blockTextureUVs[5] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;
	
	float cubeVertices[] = {
		// VERTICES				UVs						NORMALS
	    // Back face
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom left far
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top right far
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom right far
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, -1.0f, // bottom right far
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom left far
	    -0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top left far
	    // Front face
	    -0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom left near
	     0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom right near
	     0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top right near
	     0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top right near
	    -0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top left near
	    -0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom left near
	    // Left face
	    -0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top lef near
	    -0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top left far
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left far
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left far
	    -0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left near
	    -0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top left near
	    // Right face
	     0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, 1.0f, 0.0f, 0.0f, // top right near
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, 1.0f, 0.0f, 0.0f, // bottom right far
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1,	1.0f, 0.0f, 0.0f, // top right far
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0,	1.0f, 0.0f, 0.0f, // bottom right far
	     0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1,	1.0f, 0.0f, 0.0f, // top right far
	     0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0,	1.0f, 0.0f, 0.0f, // bottom right far 
	    // Bottom face
	    -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom left far
	     0.5f, -0.5f, -0.5f,  uv_bottomX0, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom right far
	     0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom right near
	     0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom right near
	    -0.5f, -0.5f,  0.5f,  uv_bottomX1, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom left near
	    -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom left far
	    // Top face
	    -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, 0.0f, 1.0f, 0.0f, // top left far
	     0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, 0.0f, 1.0f, 0.0f, // top right near
	     0.5f,  0.5f, -0.5f,  uv_topX1, uv_topY1, 0.0f, 1.0f, 0.0f, // top right far
	     0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, 0.0f, 1.0f, 0.0f, // top right near
	    -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, 0.0f, 1.0f, 0.0f, // top left far
	    -0.5f,  0.5f,  0.5f,  uv_topX0, uv_topY0, 0.0f, 1.0f, 0.0f // top left near
	};
	
	struct Block ret;
	ret.buffer.root = CreateBufferVTNA(cubeVertices, sizeof(cubeVertices));
	ret.shader = shader;
	ret.position = position;
	ret.model = glms_translate(GLMS_MAT4_IDENTITY, ret.position);
	ret.type = blockType;
	memset(&ret.neighbors, 0, 6*sizeof(struct Block*));

	return ret;
}

struct Block CreateChunk(struct Shader* shader, enum BLOCK_TYPE blockType, vec3s position, vec3s* offsets, u32 nOffsets)
{
	enum BLOCK_TEX_NAMES texName = MapBlocksToTextures(blockType);
	float blockTextureUVs[6];
	GetBlockTexture(blockTextureUVs, texName);

	float uv_topX0 = blockTextureUVs[0] / g_SPRITE_SHEET.sheet.width;
	float uv_topX1 = (blockTextureUVs[0] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	float uv_topY0 = blockTextureUVs[1] / g_SPRITE_SHEET.sheet.width;
	float uv_topY1 = (blockTextureUVs[1] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;

	float uv_aroundX0 = blockTextureUVs[2] / g_SPRITE_SHEET.sheet.height;
	float uv_aroundX1 = (blockTextureUVs[2] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;
	float uv_aroundY0 = blockTextureUVs[3] / g_SPRITE_SHEET.sheet.height;
	float uv_aroundY1 = (blockTextureUVs[3] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	float uv_bottomX0 = blockTextureUVs[4] / g_SPRITE_SHEET.sheet.width;
	float uv_bottomX1 = (blockTextureUVs[4] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	float uv_bottomY0 = blockTextureUVs[5] / g_SPRITE_SHEET.sheet.height;
	float uv_bottomY1 = (blockTextureUVs[5] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	float cubeVertices[] = {
		// VERTICES				UVs						NORMALS
		// Back face
		-0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom left far
		 0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top right far
		 0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom right far
		 0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, -1.0f, // bottom right far
		-0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom left far
		-0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top left far
		// Front face
		-0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom left near
		 0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom right near
		 0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top right near
		 0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top right near
		-0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top left near
		-0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom left near
		// Left face
		-0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top lef near
		-0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top left far
		-0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left far
		-0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left far
		-0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom left near
		-0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top left near
		// Right face
		 0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, 1.0f, 0.0f, 0.0f, // top right near
		 0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, 1.0f, 0.0f, 0.0f, // bottom right far
		 0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1,	1.0f, 0.0f, 0.0f, // top right far
		 0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0,	1.0f, 0.0f, 0.0f, // bottom right far
		 0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1,	1.0f, 0.0f, 0.0f, // top right far
		 0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0,	1.0f, 0.0f, 0.0f, // bottom right far 
		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom left far
		  0.5f, -0.5f, -0.5f,  uv_bottomX0, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom right far
		  0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom right near
		  0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom right near
		 -0.5f, -0.5f,  0.5f,  uv_bottomX1, uv_bottomY0, 0.0f, -1.0f, 0.0f, // bottom left near
		 -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, 0.0f, -1.0f, 0.0f, // bottom left far
		 // Top face
		 -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, 0.0f, 1.0f, 0.0f, // top left far
		  0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, 0.0f, 1.0f, 0.0f, // top right near
		  0.5f,  0.5f, -0.5f,  uv_topX1, uv_topY1, 0.0f, 1.0f, 0.0f, // top right far
		  0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, 0.0f, 1.0f, 0.0f, // top right near
		 -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, 0.0f, 1.0f, 0.0f, // top left far
		 -0.5f,  0.5f,  0.5f,  uv_topX0, uv_topY0, 0.0f, 1.0f, 0.0f // top left near
	};

	struct Block ret;
	ret.buffer = CreateBufferVTNA_Instanced(cubeVertices, sizeof(cubeVertices), offsets, nOffsets);
	ret.shader = shader;
	ret.position = position;
	ret.model = glms_translate(GLMS_MAT4_IDENTITY, ret.position);
	ret.type = blockType;
	memset(&ret.neighbors, 0, 6 * sizeof(struct Block*));

	return ret;
}


void DrawBlock(struct Block* go)
{
#ifdef NO_SPRITE_SHEET
	UseSprite(&go->sprite);
#endif
	UseShader(go->shader);
	SendUniformMat4(go->shader, "model", &go->model); 
	SendUniformMat4(go->shader, "view", &g_View); 
	SendUniformMat4(go->shader, "projection", &g_Projection); 
	DrawBufferA(&go->buffer.root);
}

void DrawChunk(struct Block* chunk)
{
	UseShader(chunk->shader);
	SendUniformMat4(chunk->shader, "model", &chunk->model);
	SendUniformMat4(chunk->shader, "view", &g_View);
	SendUniformMat4(chunk->shader, "projection", &g_Projection);
	DrawBufferA_Instanced(&chunk->buffer);
}