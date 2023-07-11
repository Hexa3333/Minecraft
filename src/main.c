#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "common.h"
#include "Time.h"
#include "GameObject.h"
#include "graphics/Camera.h"
#include "Game.h"

#include <cglm/struct.h>
#include <cglm/cam.h>

// 12 floats
void CreateLine(float* out, vec3s start, vec3s end, vec3s color)
{
	float data[] = {
		start.x, start.y, start.z,	color.x, color.y, color.z,
		end.x, end.y, end.z,		color.x, color.y, color.z
	};
	memcpy(out, data, sizeof(data));
}

static void KeyInput();
int main(void)
{
	InitGame("Minecraft", 720, 720);
	struct Shader shadethis = CreateShaderVF("res/Shaders/BasicCubeV.glsl", "res/Shaders/BasicCubeF.glsl");

	float dataR[12];
	float dataG[12];
	float dataB[12];
	CreateLine(dataR, (vec3s){0,0,0}, (vec3s){1,0,0}, (vec3s){1,0,0});
	CreateLine(dataG, (vec3s){0,0,0}, (vec3s){0,1,0}, (vec3s){0,1,0});
	CreateLine(dataB, (vec3s){0,0,0}, (vec3s){0,0,1}, (vec3s){0,0,1});
	
	struct Buffer LineBufR = CreateBufferVCA(dataR, sizeof(dataR));
	struct Buffer LineBufG = CreateBufferVCA(dataG, sizeof(dataG));
	struct Buffer LineBufB = CreateBufferVCA(dataB, sizeof(dataB));

	struct Shader lineShader = CreateShaderVF("res/Shaders/LineV.glsl", "res/Shaders/LineF.glsl");

	struct GameObject LineR = CreateGameObjectSpex(&LineBufR, &lineShader, DrawBufferLine);
	struct GameObject LineG = CreateGameObjectSpex(&LineBufG, &lineShader, DrawBufferLine);
	struct GameObject LineB = CreateGameObjectSpex(&LineBufB, &lineShader, DrawBufferLine);

	struct AmbientLight ambientLight = CreateAmbientLight((vec3s){1.0f, 1.0f, 1.0f}, 1.0f);
	struct DirectionalLight directionalLight = CreateDirectionalLight((vec3s){1.0f,1.0f,1.0f}, 1.0f, (vec3s) { -0.1f, 0.3f, 0.0f });
#if 1
	struct GameObject tiles[100];
	for (int i = 0; i < 100; i++) tiles[i] = CreateVoxelGameObject(&shadethis, DIRTWGRASS);
#endif

	glBindTexture(GL_TEXTURE_2D, g_SPRITE_SHEET.sheet.texObj);
	while (GetGameShouldRun())
	{
		CalculateDT();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.0f, 1.0, 0.0f, 1.0f);

		UpdateView();
		KeyInput();

		SendAmbientLight(&shadethis, ambientLight);
		SendDirectionalLight(&shadethis, directionalLight);

		//DrawGameObject(&LineR);
		//DrawGameObject(&LineG);
		//DrawGameObject(&LineB);
		
#if 1
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
			{
				tiles[(i*10)+j].model = glms_translate(GLMS_MAT4_IDENTITY, (vec3s){ -5.0f + i, -1.0f, 5.0f - j });
				SendUniformMat4(&shadethis, "model", &tiles[(i*10)+j].model);
				DrawGameObject(&tiles[(i*10)+j]);
			}
#endif

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
