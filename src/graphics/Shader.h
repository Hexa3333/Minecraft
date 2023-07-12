#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <cglm/struct.h>
#include "Light.h"

struct Shader
{
	GLuint program;
	struct Trash
	{
		GLuint vertexShader;
		GLuint fragmentShader;
	} _trash;
};

extern struct Shader g_TerrainShader;

void ShaderSetup();
struct Shader CreateShaderVF(const char* vshPath, const char* fshPath);
#if 0
struct Shader CreateShaderFromFile(const char* path);
#endif
void UseShader(struct Shader* shader);
void SendUniformMat4(struct Shader* shader, const char* uniformName, mat4s* var);
void SendUniformF(struct Shader* shader, const char* uniformName, float var);
void SendUniformVec3(struct Shader* shader, const char* uniformName, vec3s* var);
void SendAmbientLight(struct Shader* shader, struct AmbientLight ambientLight);
void SendDirectionalLight(struct Shader* shader, struct DirectionalLight directionalLight);
void DestroyShader(struct Shader* shader);
void DetermineUniformFunc();

#endif // SHADER_H
