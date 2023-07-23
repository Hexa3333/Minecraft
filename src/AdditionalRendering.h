#ifndef ADDITIONAL_RENDERING_H
#define ADDITIONAL_RENDERING_H

#include "graphics/Buffer.h"
#include <cglm/struct.h>

struct AdditionalRenderable
{
	struct Buffer buffer;	
	struct Shader* shader;
	vec3s position;
	mat4s model;
};

struct AdditionalRenderable CreateGameObject(struct Buffer* buffer, struct Shader* shader);
struct AdditionalRenderable CreateGameObjectSpex(struct Buffer* buffer, struct Shader* shader, void* func);

#endif // ADDITIONAL_RENDERING_H