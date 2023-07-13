#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "common.h"
#include "Time.h"
#include "graphics/Block.h"
#include "graphics/Camera.h"
#include "graphics/Chunk.h"
#include "graphics/Shader.h"
#include "Game.h"

#include <cglm/struct.h>
#include <cglm/cam.h>

// out: 12 floats
void CreateLine(float* out, vec3s start, vec3s end, vec3s color)
{
	float data[] = {
		start.x, start.y, start.z,	color.x, color.y, color.z,
		end.x, end.y, end.z,		color.x, color.y, color.z
	};

	memcpy(out, data, sizeof(data));
}

vec3s GetMiddle(vec3s in)
{
	return (vec3s) {in.x / 2, in.y / 2, in.z / 2};
}


static void KeyInput();
int main(void)
{
	InitGame("Minecraft", 720, 720);
	
	struct Shader shadethis = CreateShaderVF("res/Shaders/BasicCubeV.glsl", "res/Shaders/BasicCubeF.glsl");
	struct AmbientLight ambientLight = CreateAmbientLight((vec3s){1.0f, 1.0f, 1.0f}, 1.0f);
	struct DirectionalLight directionalLight = CreateDirectionalLight((vec3s){1.0f,1.0f,1.0f}, 1.0f, (vec3s) { -0.1f, 0.2f, 0.0f });

	float renderDistance = CHUNK_WIDTH * 4; // 4 chunks

	struct Chunk* chunks = malloc(8 * 8 * sizeof(struct Chunk));
	for (int x = 0; x < 8; x++)
		for (int z = 0; z < 8; z++)
		{
			chunks[x*8 + z] = CreateChunk((-4 * CHUNK_WIDTH) + (x * CHUNK_WIDTH), -z * CHUNK_DEPTH);
		}
	
	glBindTexture(GL_TEXTURE_2D, g_SPRITE_SHEET.sheet.texObj);
	while (GetGameShouldRun())
	{
		CalculateDT();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.0f, 1.0, 0.0f, 1.0f);
		//printf("\033[H\033[J"); // Clear

		LOG("Cam: (%.1f,%.1f,%.1f)", g_MainCamera.position.x, g_MainCamera.position.y, g_MainCamera.position.z);

		UpdateView();
		KeyInput();


		float pX = g_MainCamera.position.x;
		float pY = g_MainCamera.position.y;
		float pZ = g_MainCamera.position.z;

		for (int x = 0; x < 8; x++)
			for (int z = 0; z < 8; z++)
			{
				vec3s nextChunkPos = GetMiddle((vec3s){chunks[x*8 + z].x, 0, chunks[x*8 + z].z});

				if (nextChunkPos.x < pX + renderDistance && nextChunkPos.x > pX - renderDistance)
				{
					DrawChunk(&chunks[x*8 + z]);
				}
			}

		
		SendAmbientLight(&g_TerrainShader, ambientLight);
		SendDirectionalLight(&g_TerrainShader, directionalLight);

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_ESCAPE)) break;

		glfwSwapBuffers(g_MainWindow.object);
		glfwPollEvents();
	}

	free(chunks);

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

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_F))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
