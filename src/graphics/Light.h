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

extern struct _Sun
{
	struct AmbientLight ambientLight;
	struct DirectionalLight directionalLight;
} g_Sun;

enum TimeOfDay
{
	MORNING, AFTERNOON, EVENING, NIGHT
};

struct AmbientLight CreateAmbientLight(vec3s color, float intensity);
struct DirectionalLight CreateDirectionalLight(vec3s color, float intensity, vec3s direction);
void SunSet(float timeOfDay);

#endif
