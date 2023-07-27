#include "Camera.h"

struct Camera g_MainCamera;
static vec3s _up = { 0.0f, 1.0f, 0.0f };
static vec3s _towards_monitor = { 0.0f, 0.0f, -1.0f};

mat4s g_View;
mat4s g_Projection;

void SetView()
{
	g_MainCamera.position = (vec3s) { 0.0f, 0.0f, 40.0f };
	g_MainCamera.reverseDirection = glms_normalize(glms_vec3_sub(g_MainCamera.position, _towards_monitor)); // looking towards -Z which is towards the monitor
	g_MainCamera.front = glms_vec3_negate(g_MainCamera.reverseDirection);
	g_MainCamera.right = glms_normalize(glms_cross(_up, g_MainCamera.front));
	g_MainCamera.up = glms_cross(g_MainCamera.reverseDirection, g_MainCamera.right);

	g_View = glms_lookat(g_MainCamera.position, g_MainCamera.reverseDirection, _up);
}

#include "../common.h"
void UpdateView()
{
	g_View = glms_lookat(g_MainCamera.position, glms_vec3_add(g_MainCamera.position, g_MainCamera.front), _up);
}
