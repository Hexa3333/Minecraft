#include <stdio.h>
#include <stdlib.h>
#include <glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "Time.h"
#include "Game.h"
#include "util.h"
#include "graphics/Block.h"
#include "graphics/Camera.h"
#include "graphics/Shader.h"
#include "graphics/Light.h"

float sunMod = 1.0f;
static void KeyInput();
int main(void)
{
	InitGame("Minecraft", 720, 720);
	struct Shader blockShader = CreateShaderVF("res/Shaders/ChunkV.glsl", "res/Shaders/ChunkF.glsl");

	vec3s* offsets = GetChunkOffsets();

	struct Block block = CreateChunk(&blockShader, BLOCK_STONE, (vec3s) { 0, 0, 0 }, offsets, 16*16*16);
	struct Block block2 = CreateChunk(&blockShader, BLOCK_STONE, (vec3s) { CHUNK_WIDTH, 0, 0 }, offsets, 16*16*16);
	struct Block block3 = CreateChunk(&blockShader, BLOCK_STONE, (vec3s) { 0, 0, CHUNK_DEPTH }, offsets, 16*16*16);
	struct Block block4 = CreateChunk(&blockShader, BLOCK_STONE, (vec3s) { CHUNK_WIDTH, 0, CHUNK_DEPTH }, offsets, 16*16*16);

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

		printf("FPS: %.1f\n", 1 / DT);
		SunSet(sunMod);
		SendSun(&blockShader);

		DrawChunk(&block);
		DrawChunk(&block2);
		DrawChunk(&block3);
		DrawChunk(&block4);

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_ESCAPE)) break;

		glfwSwapBuffers(g_MainWindow.object);
		glfwPollEvents();
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
