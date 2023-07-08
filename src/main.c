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

//#define STB_PERLIN_IMPLEMENTATION
//#include "stb_perlin.h"

static void KeyInput();
int main(void)
{
	InitGame("Minecraft", 720, 720);
	struct Shader shadethis = CreateShaderVF("res/Shaders/BasicCubeV.glsl", "res/Shaders/BasicCubeF.glsl");
	mat4s view = SetView();

	struct AmbientLight ambientLight = CreateAmbientLight((vec3s){1.0f, 1.0f, 1.0f}, 1.0f);
	struct DirectionalLight directionalLight = CreateDirectionalLight((vec3s){1.0f,1.0f,1.0f}, 1.0f, (vec3s) { -1.5f, 1.0f, 0.0f });
	struct GameObject tiles[1000];
	for (int i = 0; i < 1000; i++) tiles[i] = CreateVoxelGameObject(&shadethis, DIRTWGRASS);
	struct GameObject go2 = CreateVoxelGameObject(&shadethis, SAND);
	struct GameObject go3 = CreateVoxelGameObject(&shadethis, SAND);

	glBindTexture(GL_TEXTURE_2D, g_SPRITE_SHEET.sheet.texObj);
	while (GetGameShouldRun())
	{
		CalculateDT();
		LOG("FPS: %.1f", 1 / DT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		KeyInput();

		view = UpdateView();
		SendUniformMat4(&shadethis, "view", &view);
		SendUniformMat4(&shadethis, "projection", &g_projection);

		SendAmbientLight(&shadethis, ambientLight);
		SendDirectionalLight(&shadethis, directionalLight);


		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 100; ++j)
			{
				tiles[(i*10)+j].model = glms_translate(GLMS_MAT4_IDENTITY, (vec3s){ -5.0f + i, -j, 5.0f - i });
				SendUniformMat4(&shadethis, "model", &tiles[(i*10)+j].model);
				DrawGameObject(&tiles[i*10 + j]);
			}

		go2.model = glms_translate(GLMS_MAT4_IDENTITY, (vec3s){-1.0f, 0.0f, 0.0f});
		DrawGameObject(&go2);
		go3.model = glms_translate(GLMS_MAT4_IDENTITY, (vec3s){1.0f, 0.0f, 0.0f});
		DrawGameObject(&go3);

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
