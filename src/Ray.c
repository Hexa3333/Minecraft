#include "Ray.h"
#include "common.h"

void CastRay(vec3s direction, vec3s normal)
{
	mat4s inverseProjection = glms_mat4_inv(g_Projection);
	vec3s rayPos = { g_MainCamera.position.x, g_MainCamera.position.y, g_MainCamera.position.z };
	vec4s orthogonality = glms_mat4_mulv(inverseProjection, (vec4s) { direction.x, direction.y, direction.z, 0 });
	if (orthogonality.x == 0 && orthogonality.y == 0 && orthogonality.z == 0)
	{
		ERR("Perfectly f* vertical: Ray");
	}

	float dotNormal = glms_vec3_dot((vec3s) { normal.x - 0.5f, normal.y - 0.5f, normal.z - 0.5f }, normal);

	//			-(rayPos * normal + dotNormal)
	//			-------------------------------
	//					rayDir * normal
	vec3s intersection = glms_vec3_div(glms_vec3_mul((vec3s) { -1, -1, -1 }, glms_vec3_adds(glms_vec3_mul(rayPos, normal), dotNormal)),
									   glms_vec3_mul(direction, normal));
	vec3s point = glms_vec3_add(rayPos, glms_vec3_mul(intersection, direction));
}