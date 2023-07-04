#include <GLFW/glfw3.h>

static float previousTime=0;
static float currentTime=0;
float DT;

void CalculateDT()
{
	currentTime = (float)glfwGetTime();
	DT = currentTime - previousTime;
	previousTime = (float)glfwGetTime();
}
