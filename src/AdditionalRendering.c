#include "AdditionalRendering.h"
#include "graphics/Camera.h"

static struct Buffer _lineBuffer;
static struct Shader _lineShader;

static float normalsAroundBlockLine[] = {
	0.5f, 0, 0,		1,0,0,		1, 0, 0,		1,0,0, // right
	-0.5f, 0, 0,	1,0,0,		-1, 0, 0,		1,0,0, // left
	0, 0.5f, 0,		0,1,0,		0, 1, 0,		0,1,0, // up
	0, -0.5f, 0,	0,1,0,		0, -1, 0,		0,1,0, // down
	0, 0, 0.5f,		0,0,1,		0, 0, 1,		0,0,1, // front
	0, 0, -0.5f,	0,0,1,		0, 0, -1,		0,0,1  // back
};

void AdditionalRenderingSetup(void)
{
	_lineBuffer = CreateBufferVCA(normalsAroundBlockLine, sizeof(normalsAroundBlockLine));
	_lineShader = CreateShaderVF("res/Shaders/LineV.glsl", "res/Shaders/LineF.glsl");
}

struct AdditionalRenderable CreateGameObject(struct Buffer* buffer, struct Shader* shader)
{
	struct AdditionalRenderable ret;
	ret.buffer = *buffer;
	ret.shader = shader;
	ret.model = GLMS_MAT4_IDENTITY;

	return ret;
}

struct AdditionalRenderable CreateGameObjectSpex(struct Buffer* buffer, struct Shader* shader, void* func)
{
	struct AdditionalRenderable ret;
	ret.buffer = *buffer;
	ret.shader = shader;
	ret.model = GLMS_MAT4_IDENTITY;
	ret.buffer.render = func;

	return ret;
}



void DebugDrawLine(struct Block* latch)
{
	mat4s trans = glms_translate(GLMS_MAT4_IDENTITY, (vec3s) { latch->position.x + 1, latch->position.y + 1, latch->position.z + 1 });
	UseShader(&_lineShader);
	SendUniformMat4(&_lineShader, "model", &trans);
	SendUniformMat4(&_lineShader, "view", &g_View);
	SendUniformMat4(&_lineShader, "projection", &g_Projection);
	DrawBufferLine(&_lineBuffer);
}