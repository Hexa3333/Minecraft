#include "GameObject.h"

struct GameObject CreateGameObject(struct Buffer* buffer, struct Shader* shader)
{
	struct GameObject ret;
	ret.buffer = *buffer;
	ret.shader = *shader;
	ret.render = DetermineDrawFunc(DetermineBufferType(buffer));
	ret.model = GLMS_MAT4_IDENTITY;

	return ret;
}

// out: float[3] 				in: float[9]
static float* CalculateAverageNormals(float* Triangle)
{
	vec3s vertices1 = { Triangle[0], Triangle[1], Triangle[2] };
	vec3s vertices2 = { Triangle[3], Triangle[4], Triangle[5] };
	vec3s vertices3 = { Triangle[6], Triangle[7], Triangle[8] };

	vec3s u = glms_vec3_sub(vertices2, vertices1);
	vec3s v = glms_vec3_sub(vertices3, vertices1);

	vec3s Normal;
	Normal.x = (u.y * v.z) - (u.z * v.y);
	Normal.y = (u.z * v.x) - (u.x * v.z);
	Normal.z = (u.x * v.y) - (u.y * v.x);
	
	float* ret = malloc(3 * sizeof(float));
	ret[0] = Normal.x;
	ret[1] = Normal.y;
	ret[2] = Normal.z;

	return ret;
}
struct GameObject CreateVoxelGameObject(struct Shader* shader, enum BLOCK_TEX_NAMES texName)
{
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
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, -1.0f, // Bottom-left
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top-right
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom-right
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top-right
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, -1.0f, // bottom-left
	    -0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, 0.0f, 0.0f, -1.0f, // top-left
	    // Front face
	    -0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom-left
	     0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom-right
	     0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top-right
	     0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top-right
	    -0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, 0.0f, 0.0f, 1.0f, // top-left
	    -0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0, 0.0f, 0.0f, 1.0f, // bottom-left
	    // Left face
	    -0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top-right
	    -0.5f,  0.5f, -0.5f,  uv_aroundX0, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top-left
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom-left
	    -0.5f, -0.5f, -0.5f,  uv_aroundX0, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom-left
	    -0.5f, -0.5f,  0.5f,  uv_aroundX1, uv_aroundY0, -1.0f, 0.0f, 0.0f, // bottom-right
	    -0.5f,  0.5f,  0.5f,  uv_aroundX1, uv_aroundY1, -1.0f, 0.0f, 0.0f, // top-right
	    // Right face
	     0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1, 1.0f, 0.0f, 0.0f, // top-left
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0, 1.0f, 0.0f, 0.0f,// bottom-right
	     0.5f,  0.5f, -0.5f,  uv_aroundX1, uv_aroundY1,	1.0f, 0.0f, 0.0f,// top-right
	     0.5f, -0.5f, -0.5f,  uv_aroundX1, uv_aroundY0,	1.0f, 0.0f, 0.0f,// bottom-right
	     0.5f,  0.5f,  0.5f,  uv_aroundX0, uv_aroundY1,	1.0f, 0.0f, 0.0f,// top-left
	     0.5f, -0.5f,  0.5f,  uv_aroundX0, uv_aroundY0,	1.0f, 0.0f, 0.0f,// bottom-left
	    // Bottom face
	    -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, 0.0f, -1.0f, 0.0f, // top-right
	     0.5f, -0.5f, -0.5f,  uv_bottomX0, uv_bottomY1, 0.0f, -1.0f, 0.0f,// top-left
	     0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, 0.0f, -1.0f, 0.0f,// bottom-left
	     0.5f, -0.5f,  0.5f,  uv_bottomX0, uv_bottomY0, 0.0f, -1.0f, 0.0f,// bottom-left
	    -0.5f, -0.5f,  0.5f,  uv_bottomX1, uv_bottomY0, 0.0f, -1.0f, 0.0f,// bottom-right
	    -0.5f, -0.5f, -0.5f,  uv_bottomX1, uv_bottomY1, 0.0f, -1.0f, 0.0f,// top-right
	    // Top face
	    -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, 0.0f, 1.0f, 0.0f, // top-left
	     0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, 0.0f, 1.0f, 0.0f, // bottom-right
	     0.5f,  0.5f, -0.5f,  uv_topX1, uv_topY1, 0.0f, 1.0f, 0.0f, // top-right
	     0.5f,  0.5f,  0.5f,  uv_topX1, uv_topY0, 0.0f, 1.0f, 0.0f, // bottom-right
	    -0.5f,  0.5f, -0.5f,  uv_topX0, uv_topY1, 0.0f, 1.0f, 0.0f, // top-left
	    -0.5f,  0.5f,  0.5f,  uv_topX0, uv_topY0, 0.0f, 1.0f, 0.0f // bottom-left
	};                                             
	
	struct GameObject ret;
	ret.buffer = CreateBufferVTNA(cubeVertices, sizeof(cubeVertices));
	ret.shader = *shader;
	ret.render = DetermineDrawFunc(DetermineBufferType(&ret.buffer));
	ret.model = GLMS_MAT4_IDENTITY;

	return ret;
}

void DrawGameObject(struct GameObject* go)
{
#ifdef NO_SPRITE_SHEET
	UseSprite(&go->sprite);
#endif
	SendUniformMat4(&go->shader, "model", &go->model); 
	UseShader(&go->shader);
	BindBuffer(&go->buffer);
	go->render(&go->buffer);
}
