#include "Light.h"

struct _Sun g_Sun;
struct AmbientLight CreateAmbientLight(vec3s color, float intensity)
{
	struct AmbientLight ret;
	ret.color = color;
	ret.intensity = intensity;
	return ret;
}

struct DirectionalLight CreateDirectionalLight(vec3s color, float intensity, vec3s direction)
{
	struct DirectionalLight ret;
	ret.color = color;
	ret.intensity = intensity;
	ret.direction = direction;
	return ret;
}

// TODO: Sun and time of day modifiers
void SunSet(float timeOfDay)
{
	float reverseFactor = 1.0f - timeOfDay;
	g_Sun.ambientLight = CreateAmbientLight((vec3s){1,1,1}, 1);
	g_Sun.directionalLight = CreateDirectionalLight((vec3s){1,0,0}, 1, (vec3s){timeOfDay, reverseFactor, 0.1f});
}
