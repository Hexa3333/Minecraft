#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "common.h"

struct MouseInput
{
	bool mouseFirstEnter: 1;
	float lastX, lastY;
	float yaw, pitch;
};
extern struct MouseInput g_MInput;

void mouseCallback(GLFWwindow* window, double xpos, double ypos);

#endif
