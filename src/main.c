#include <stdio.h>
#include <stdlib.h>
#include <glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "Time.h"
#include "Game.h"
#include "util.h"
#include "Block.h"
#include "Chunk.h"
#include "graphics/Camera.h"
#include "graphics/Shader.h"
#include "graphics/Light.h"
#include "AdditionalRendering.h"
#include "Ray.h"

float quadVerts[] = {
	-0.1f, -0.1f, 0.0f,		0, 0, 1,  // sol alt
	0.1f, -0.1f, 0.0f,		0, 0, 1,  // sag alt
	0.1f, 0.1f, 0.0f,		0, 0, 1,  // sag ust

	0.1f, 0.1f, 0.0f,		0, 0, 1,  // sag ust
	-0.1f, 0.1f, 0.0f,		0, 0, 1,  // sol ust
	-0.1f, -0.1f, 0.0f,		0, 0, 1 // sol alt
};

static float dis = 1000.f;
float sunMod = 1.0f;
static void KeyInput();
int main(void)
{
	InitGame("Minecraft", 720, 720);
	struct Shader chunkShader = CreateShaderVF("res/Shaders/ChunkV.glsl", "res/Shaders/ChunkF.glsl");
	struct Shader quadShader = CreateShaderVF("res/Shaders/QuadV.glsl", "res/Shaders/QuadF.glsl");
	struct Buffer quadBuf = CreateBufferVNA(quadVerts, sizeof(quadVerts));

	struct Chunk chunk = CreateChunk(&chunkShader, (vec3s) { 0, 0, 0 });

	float t = 0; bool tIncreasing = true;
	vec3s quadPos = { 0, -1, 0 };
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
		DrawChunk(&chunk);

		quadPos = glms_vec3_lerp((vec3s) { 0, -1, 0 }, (vec3s) { CHUNK_WIDTH, -1, 0 }, t);
		mat4s quaddraw = glms_translate(GLMS_MAT4_IDENTITY, quadPos);

		UseShader(&quadShader);
		SendUniformMat4(&quadShader, "model", &quaddraw);
		SendUniformMat4(&quadShader, "view", &g_View);
		SendUniformMat4(&quadShader, "projection", &g_Projection);
		DrawBufferA(&quadBuf);

		if (tIncreasing)
		{
			t += 0.01f;
			if (t >= 1.f) tIncreasing = false;
		}
		else
		{
			t -= 0.01f;
			if (t <= 0.f) tIncreasing = true;
		}

		printf("\033[H\033[J");
		

#if 0
		for (int z = 0; z < 5; ++z)
			for (int x = 0; x < 5; ++x)
			{
				struct Chunk_Instanced* curChunk = &chunks[z*5 + x];

				if (glms_vec3_distance2(glms_vec3_add(curChunk->position, (vec3s){ CHUNK_WIDTH / 2, CHUNK_HEIGHT / 2, -CHUNK_DEPTH / 2 }), g_MainCamera.position) < dis)
					DrawChunk_Instanced(curChunk);
				else
				{
					// replace chunk

				}
			}
#endif

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_ESCAPE)) break;

		glfwSwapBuffers(g_MainWindow.object);
		glfwPollEvents();
	}
	free(chunk.blocks);

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
			g_MainCamera.position.y -= 15.0f * DT;
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_SPACE))
			g_MainCamera.position.y += 15.0f * DT;

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_L))
		{
			dis -= 100.f;
			LOG("Render Dist: %.1f", dis);
		}
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_I))
		{
			dis += 100.f;
			LOG("Render Dist: %.1f", dis);
		}


		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_F))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
