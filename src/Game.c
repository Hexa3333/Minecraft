#include "Game.h"
#include "Time.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "AdditionalRendering.h"
#include "Input.h"

struct Window g_MainWindow;

static bool mouseFirstEnter;
static GLFWwindow* windowObj;

bool InitGame(const char* Title, u16 width, u16 height)
{
	glfwInit();
	g_MainWindow.object = glfwCreateWindow(width, height, Title, NULL, NULL);
	g_MainWindow.screenWidth = width;
	g_MainWindow.screenHeight = height;
	if (!g_MainWindow.object)
	{
		ERR("GLFW failed.");
		return FAILED;
	}
	
	glfwSetInputMode(g_MainWindow.object, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(g_MainWindow.object, mouseCallback);
	glfwMakeContextCurrent(g_MainWindow.object);

	if (gladLoadGL() == 0)
	{
		ERR("Glad failed.");
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Component Setup
	ShaderSetup();
	SpriteSetup();
	SunSet(.3f);
	BuildSpriteSheet("res/Sprites/blocks.png", 0, 5, 5);
	AdditionalRenderingSetup();
	
	float zNear = 0.1f;
	float zFar = 400.0f;
	// Projection Matrix
	g_Projection = glms_perspective(glm_rad(45.0f), (float)(g_MainWindow.screenHeight / g_MainWindow.screenWidth), zNear, zFar);
	
	SetView();
	// Mouse Input
	g_MInput.lastX = g_MainWindow.screenWidth / 2.0f;
	g_MInput.lastY = g_MainWindow.screenHeight / 2.0f;

	return OK;
}

void KillGame()
{
	glfwTerminate();

	//TODO: Fix this
#ifndef NO_SPRITE_SHEET
	//glDeleteTextures(1, &g_SPRITE_SHEET.sheet.texObj);
#endif
}
