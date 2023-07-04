#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <cglm/struct.h>

struct Shader
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
};

// Use 3 $ to split vertex/fragment sources
struct Shader CreateShaderFromFile(const char* path);
void UseShader(struct Shader* shader);
void SendUniformMat4(struct Shader* shader, const char* uniformName, mat4s* var);
void DestroyShader(struct Shader* shader);
void DetermineUniformFunc();

#endif // SHADER_H
