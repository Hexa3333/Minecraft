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

float quadVerts[] = {
	-0.5f, -0.5f, 0.0f,		0, 0, 1, // sol alt
	0.5f, -0.5f, 0.0f,		0, 0, 1, // sag alt
	0.5f, 0.5f, 0.0f,		0, 0, 1, // sag ust

	0.5f, 0.5f, 0.0f,		0, 0, 1, // sag ust
	-0.5f, 0.5f, 0.0f,		0, 0, 1, // sol ust
	-0.5f, -0.5f, 0.0f,		0, 0, 1 // sol alt
};

struct BlockNormalLines
{
	struct Block* latch;
	struct Shader shader;
	float offset;
	struct Buffer originalLine;
};

struct BlockNormalLines SetBlockNormalLines(struct Block* block, float offset)
{
	struct BlockNormalLines ret;
	ret.latch = block;
	ret.shader = CreateShaderVF("res/Shaders/LineV.glsl", "res/Shaders/LineF.glsl");
	ret.offset = offset;

	float lineData[12];
	CreateLine(lineData, (vec3s) { 0, 0, offset }, (vec3s) { 0, 0, offset + 2 }, (vec3s) { 1, 0, 0 }); // front
	ret.originalLine = CreateBufferVCA(lineData, 12);

	return ret;
}

void DrawBlockNormalLines(struct BlockNormalLines* go)
{
	UseShader(&go->shader);
	
}

float sunMod = 1.0f;
static void KeyInput();
int main(void)
{
	InitGame("Minecraft", 720, 720);
	struct Shader quadShader = CreateShaderVF("res/Shaders/quadV.glsl", "res/Shaders/quadF.glsl");
	struct Shader chunkShader = CreateShaderVF("res/Shaders/ChunkV.glsl", "res/Shaders/ChunkF.glsl");
	
	struct Buffer quad = CreateBufferVNA(quadVerts, sizeof(quadVerts));
	mat4s quadModel = glms_translate(GLMS_MAT4_IDENTITY, (vec3s) { 0, 3, 0 });

	struct Block block = CreateBlock(&chunkShader, BLOCK_STONE, (vec3s) { 0, 3, 0 });
	struct BlockNormalLines bnl = SetBlockNormalLines(&block, 0.5f);

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
		SendSun(&chunkShader);

		DrawBlock(&block);
		DrawBlockNormalLines(&bnl);

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_ESCAPE)) break;

		glfwSwapBuffers(g_MainWindow.object);
		glfwPollEvents();
	}


	KillGame();
}

void KeyInput()
{
		vec3s direction = glms_vec3_cross(g_MainCamera.front, g_MainCamera.up);
		vec3s moveSpeed = {20.0f * DT, 20.0f * DT, 20.0f * DT};

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_W))
			g_MainCamera.position = glms_vec3_add(g_MainCamera.position, glms_vec3_mul(g_MainCamera.front, moveSpeed));
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_S))
			g_MainCamera.position = glms_vec3_sub(g_MainCamera.position, glms_vec3_mul(g_MainCamera.front, moveSpeed));

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_A))
			g_MainCamera.position = glms_vec3_add(g_MainCamera.position, glms_vec3_mul(direction, moveSpeed));
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_D))
			g_MainCamera.position = glms_vec3_sub(g_MainCamera.position, glms_vec3_mul(direction, moveSpeed));

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_LEFT_CONTROL))
			g_MainCamera.position.y -= 25.0f * DT;
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_SPACE))
			g_MainCamera.position.y += 25.0f * DT;

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_F))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
