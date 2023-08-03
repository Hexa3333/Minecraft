#include "Ray.h"
#include "common.h"
#include "graphics/Camera.h"

void CastRay3D(vec3s caste)
{
	vec3s p = glms_vec3_add(g_MainCamera.position, g_MainCamera.front);
	for (int i = 0; i < 100; ++i)
	{
		// NOTE:
		// The block vertices go from -.5f to +.5f,
		// meaning x,y,z points to the middle of the block,
		// therefore we offset them.
		if (p.x > caste.x - 0.5f && p.x < caste.x + 0.5f &&
			p.y > caste.y - 0.5f && p.y < caste.y + 0.5f &&
			p.z < caste.z + 0.5f && p.z > caste.z - 0.5f
			)
		{
			LOG("INTERSECTION!");
			return;
		}
		p = glms_vec3_add(p, glms_vec3_divs(g_MainCamera.front, 2));
	}
}