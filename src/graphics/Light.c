#include "Light.h"

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
