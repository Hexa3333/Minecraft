#include "Game.h"
#include "Time.h"
#include "graphics/Camera.h"
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
	SpriteSetup();
	BuildSpriteSheet("res/Sprites/blocks.png", 0, 5, 5);
	
	
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
