#ifndef LIGHT_H
#define LIGHT_H

#include <cglm/struct.h>

struct AmbientLight
{
	vec3s color;
	float intensity;
};

struct DirectionalLight
{
	vec3s color;
	float intensity;
	vec3s direction;
};

struct AmbientLight CreateAmbientLight(vec3s color, float intensity);
struct DirectionalLight CreateDirectionalLight(vec3s color, float intensity, vec3s direction);

#endif
