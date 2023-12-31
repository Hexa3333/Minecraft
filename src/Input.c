#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "graphics/Camera.h"
#include <cglm/struct.h>

struct MouseInput g_MInput;

static bool mouseFirstEnter = true;
void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (mouseFirstEnter)
	{
		g_MInput.lastX = (float)xpos;
		g_MInput.lastY = (float)ypos;
		g_MInput.yaw = -90.0f;
		mouseFirstEnter = false;
	}

	double xOffset = xpos - g_MInput.lastX;
	double yOffset = ypos - g_MInput.lastY;
	g_MInput.lastX = (float)xpos;
	g_MInput.lastY = (float)ypos;

	g_MInput.yaw += (float)xOffset;
	g_MInput.pitch += (float)yOffset;

	vec3s direction;
	direction.x = (float)(cos(glm_rad(g_MInput.yaw)) * cos(glm_rad(g_MInput.pitch)));
	direction.y = (float)(-sin(glm_rad(g_MInput.pitch)));
	direction.z = (float)(sin(glm_rad(g_MInput.yaw)) * cos(glm_rad(g_MInput.pitch)));
	g_MainCamera.front = glms_vec3_normalize(direction);
	
	if(g_MInput.pitch > 89.0f) g_MInput.pitch =  89.0f;
	if(g_MInput.pitch < -89.0f) g_MInput.pitch = -89.0f;
}
