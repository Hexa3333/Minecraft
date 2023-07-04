#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "common.h"
#include "Time.h"
#include "graphics/Shader.h"
#include "graphics/Buffer.h"
#include "graphics/Sprite.h"
#include "GameObject.h"
#include "graphics/Camera.h"
#include "Game.h"

#include <cglm/struct.h>
#include <cglm/cam.h>

#if 0
#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"
#endif

static void KeyInput();

int main(void)
{
	InitGame("Minecraft", 720, 720);
	float* sheetXY = GetSpriteXYFromTable(1,2);
	
	struct Shader shadethis = CreateShaderFromFile("res/Shaders/basicCube.glsl");

	mat4s proj = glms_perspective(glm_rad(45.0f), (float)(g_MainWindow.screenHeight / g_MainWindow.screenWidth), 0.1f, 100.0f);
	mat4s view = SetView();

	struct GameObject tiles[100];
	for (int i = 0; i < 100; i++) tiles[i] = CreateVoxelGameObject(&shadethis, 3,3, 2,3, 4,3);
	struct GameObject go = CreateVoxelGameObject(&shadethis, 3,3, 2,3, 4,3);

	glBindTexture(GL_TEXTURE_2D, g_SPRITE_SHEET.sheet.texObj); // Single bind babee
	while (GetGameShouldRun())
	{
		CalculateDT();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		KeyInput();

		view = UpdateView();
		SendUniformMat4(&shadethis, "view", &view);
		SendUniformMat4(&shadethis, "projection", &proj);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				tiles[(i*10)+j].model = glms_translate(GLMS_MAT4_IDENTITY, (vec3s){-50 + ((j*10)+i), 0.0f, 50 - ((i*10)+j)}); 
				DrawGameObject(&tiles[(i*10)+j]);
			}
		}

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_ESCAPE)) break;

		glfwSwapBuffers(g_MainWindow.object);
		glfwPollEvents();
	}

	KillGame();
}

void KeyInput()
{
		vec3s cross = glms_vec3_cross(g_MainCamera.front, g_MainCamera.up);
		vec3s moveSpeed = {8.0f * DT, 8.0f * DT, 8.0f * DT};

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_W))
			g_MainCamera.position = glms_vec3_add(g_MainCamera.position, glms_vec3_mul(g_MainCamera.front, moveSpeed));
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_S))
			g_MainCamera.position = glms_vec3_sub(g_MainCamera.position, glms_vec3_mul(g_MainCamera.front, moveSpeed));

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_A))
			g_MainCamera.position = glms_vec3_add(g_MainCamera.position, glms_vec3_mul(cross, moveSpeed));
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_D))
			g_MainCamera.position = glms_vec3_sub(g_MainCamera.position, glms_vec3_mul(cross, moveSpeed));

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_LEFT_CONTROL))
			g_MainCamera.position.y -= 8.0f * DT;
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_SPACE))
			g_MainCamera.position.y += 8.0f * DT;
}
