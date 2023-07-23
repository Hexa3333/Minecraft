#include <stdio.h>
#include <stdlib.h>
#include <glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "Time.h"
#include "Chunk.h"
#include "graphics/Camera.h"
#include "Game.h"
#include "util.h"
#include "graphics/Light.h"

float sunMod = 1.0f;
static void KeyInput();
int main(void)
{
	InitGame("Minecraft", 720, 720);
	struct Chunk* heyya[3*3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			heyya[i*3 + j] = CreateChunk(i*CHUNK_WIDTH,j*CHUNK_DEPTH);
		}
	bool morning = true;
	glBindTexture(GL_TEXTURE_2D, g_SPRITE_SHEET.sheet.texObj);
	while (GetGameShouldRun())
	{
		CalculateDT();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.529f, 0.807f, 0.921f, 1.0f);

		UpdateView();
		KeyInput();

		float pX = g_MainCamera.position.x;
		float pY = g_MainCamera.position.y;
		float pZ = g_MainCamera.position.z;

		SunSet(sunMod);
		SendSun(&g_TerrainShader);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
		{
			DrawChunk(heyya[i*3 + j]);
		}

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_ESCAPE)) break;

		glfwSwapBuffers(g_MainWindow.object);
		glfwPollEvents();
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			free(heyya[i * 3 + j]);
		}

	KillGame();
}
void KeyInput()
{
		vec3s area = glms_vec3_cross(g_MainCamera.front, g_MainCamera.up);
		vec3s moveSpeed = {20.0f * DT, 20.0f * DT, 20.0f * DT};

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_W))
			g_MainCamera.position = glms_vec3_add(g_MainCamera.position, glms_vec3_mul(g_MainCamera.front, moveSpeed));
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_S))
			g_MainCamera.position = glms_vec3_sub(g_MainCamera.position, glms_vec3_mul(g_MainCamera.front, moveSpeed));

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_A))
			g_MainCamera.position = glms_vec3_add(g_MainCamera.position, glms_vec3_mul(area, moveSpeed));
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_D))
			g_MainCamera.position = glms_vec3_sub(g_MainCamera.position, glms_vec3_mul(area, moveSpeed));

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_LEFT_CONTROL))
			g_MainCamera.position.y -= 25.0f * DT;
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_SPACE))
			g_MainCamera.position.y += 25.0f * DT;

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_F))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
