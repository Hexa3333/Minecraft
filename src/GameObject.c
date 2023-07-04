#include "GameObject.h"

#ifdef NO_SPRITE_SHEET
struct GameObject CreateGameObject(struct Buffer* buffer, struct Shader* shader, struct Sprite* sprite)
{
	struct GameObject ret;
	ret.buffer = *buffer;
	ret.shader = *shader;
	ret.sprite = *sprite;
	ret.render = DetermineDrawFunc(DetermineBufferType(buffer));
	ret.model = GLMS_MAT4_IDENTITY;
	
	return ret;
}

#else

struct GameObject CreateGameObject(struct Buffer* buffer, struct Shader* shader)
{
	struct GameObject ret;
	ret.buffer = *buffer;
	ret.shader = *shader;
	ret.render = DetermineDrawFunc(DetermineBufferType(buffer));
	ret.model = GLMS_MAT4_IDENTITY;

	return ret;
}

// TODO: Reverse Image Indexes
struct GameObject CreateVoxelGameObject(struct Shader* shader, float sheetIndexTopX, float sheetIndexTopY, float sheetIndexAroundX, float sheetIndexAroundY, float sheetIndexBottomX, float sheetIndexBottomY)
{
	float* top = GetSpriteXYFromTable(sheetIndexTopX, sheetIndexTopY);
	float* around = GetSpriteXYFromTable(sheetIndexAroundX, sheetIndexAroundY);
	float* bottom = GetSpriteXYFromTable(sheetIndexBottomX, sheetIndexBottomY);

	struct GameObject ret;
	float uv_topX0 = top[0] / g_SPRITE_SHEET.sheet.width;
	float uv_topX1 = (top[0] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	float uv_topY0 = top[1] / g_SPRITE_SHEET.sheet.width;
	float uv_topY1 = (top[1] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;

	float uv_aroundX0 = around[0] / g_SPRITE_SHEET.sheet.height;
	float uv_aroundX1 = (around[0] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;
	float uv_aroundY0 = around[1] / g_SPRITE_SHEET.sheet.height;
	float uv_aroundY1 = (around[1] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	float uv_bottomX0 = bottom[0] / g_SPRITE_SHEET.sheet.width;
	float uv_bottomX1 = (bottom[0] + g_SPRITE_SHEET.tileWidth) / g_SPRITE_SHEET.sheet.width;
	float uv_bottomY0 = bottom[1] / g_SPRITE_SHEET.sheet.height;
	float uv_bottomY1 = (bottom[1] + g_SPRITE_SHEET.tileHeight) / g_SPRITE_SHEET.sheet.height;

	float cubeVertices[] = {
	    // Back face
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, // Bottom-left
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, // top-right
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, // bottom-right         
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, // top-right
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, // bottom-left
	    -0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, // top-left
	    // Front face
	    -0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, // bottom-left
	     0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, // bottom-right
	     0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, // top-right
	     0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, // top-right
	    -0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, // top-left
	    -0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, // bottom-left
	    // Left face
	    -0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, // top-right
	    -0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, // top-left
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, // bottom-left
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, // bottom-left
	    -0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, // bottom-right
	    -0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, // top-right
	    // Right face
	     0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, // top-left
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, // bottom-right
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, // top-right         
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, // bottom-right
	     0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, // top-left
	     0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, // bottom-left     
	    // Bottom face
	    -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, // top-right
	     0.5f, -0.5f, -0.5f,  uv_bottomX0, uv_bottomY1, // top-left
	     0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, // bottom-left
	     0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, // bottom-left
	    -0.5f, -0.5f,  0.5f,  uv_bottomX1, uv_bottomY0, // bottom-right
	    -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, // top-right
	    // Top face
	    -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, // top-left
	     0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, // bottom-right
	     0.5f,  0.5f, -0.5f,  uv_topX1, uv_topY1, // top-right     
	     0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, // bottom-right
	    -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, // top-left
	    -0.5f,  0.5f,  0.5f,  uv_topX0, uv_topY0  // bottom-left        
	};

	ret.buffer = CreateBufferVTA(cubeVertices, sizeof(cubeVertices));
	ret.shader = *shader;
	ret.render = DetermineDrawFunc(DetermineBufferType(&ret.buffer));
	ret.model = GLMS_MAT4_IDENTITY;

	free(top);
	free(bottom);
	free(around);

	return ret;
}
#endif

void DrawGameObject(struct GameObject* go)
{
#ifdef NO_SPRITE_SHEET
	UseSprite(&go->sprite);
#endif
	SendUniformMat4(&go->shader, "model", &go->model); 
	UseShader(&go->shader);
	go->render(&go->buffer);
}
