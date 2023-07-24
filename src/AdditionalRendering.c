#include "AdditionalRendering.h"

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

