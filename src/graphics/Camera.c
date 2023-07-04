#include "Camera.h"

struct Camera g_MainCamera;
static vec3s _up = (vec3s) { 0.0f, 1.0f, 0.0f };
static vec3s _towards_monitor = (vec3s) { 0.0f, 0.0f, -1.0f};

mat4s SetView()
{
	g_MainCamera.position = (vec3s) { 0.0f, 0.0f, 3.0f };
	g_MainCamera.reverseDirection = glms_normalize(glms_vec3_sub(g_MainCamera.position, _towards_monitor)); // looking towards -Z which is towards the monitor
	g_MainCamera.front = glms_vec3_mul((vec3s){-1.0f,-1.0f,-1.0f}, g_MainCamera.reverseDirection);
	g_MainCamera.right = glms_normalize(glms_cross(_up, g_MainCamera.front));
	g_MainCamera.up = glms_cross(g_MainCamera.reverseDirection, g_MainCamera.right);

	mat4s view = glms_lookat(g_MainCamera.position, g_MainCamera.reverseDirection, _up);

	return view;
}

mat4s UpdateView()
{
	mat4s view = glms_lookat(g_MainCamera.position, glms_vec3_add(g_MainCamera.position, g_MainCamera.front), _up);
	return view;
}
