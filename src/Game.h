#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/Sprite.h"
#include <cglm/struct.h>

struct Window
{
	GLFWwindow* object;
	u16 screenWidth, screenHeight;
};
extern struct Window g_MainWindow;
extern mat4s g_projection;

bool InitGame(const char* Title, u16 width, u16 height);
static inline bool GetGameShouldRun() { return !glfwWindowShouldClose(g_MainWindow.object); };
void KillGame();

#endif // GAME_H
