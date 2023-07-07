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
struct Shader CreateShaderVF(const char* vshPath, const char* fshPath);
struct Shader CreateShaderFromFile(const char* path);
void UseShader(struct Shader* shader);
void SendUniformMat4(struct Shader* shader, const char* uniformName, mat4s* var);
void SendUniformF(struct Shader* shader, const char* uniformName, float var);
void SendUniformVec3(struct Shader* shader, const char* uniformName, vec3s* var);
void DestroyShader(struct Shader* shader);
void DetermineUniformFunc();

#endif // SHADER_H
