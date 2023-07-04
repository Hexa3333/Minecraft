#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common.h"

#include "Shader.h"

struct Shader CreateShaderFromFile(const char* path)
{
	struct Shader ret = {0};
	FILE* fp = fopen(path, "r");
	if (!fp)
	{
		ERR("Shader source could not be read.");
		return ret;
	}

	fseek(fp, 0, SEEK_END);
	size_t sourceLength = ftell(fp);
	rewind(fp);

	char* sourceBuffer = malloc(sourceLength+1);
	int sourceBufferIndexer = 0;

	while(!feof(fp))
	{
		sourceBuffer[sourceBufferIndexer] = fgetc(fp);
		++sourceBufferIndexer;
	} 
	sourceBuffer[sourceBufferIndexer] = '\0';


	// Check the index where vertex ends
	u32 vertexEnd = 0;
	u8 shebangs = 0; // 3 Shebangs split the file
	for (u32 i = 0; i < sourceLength; i++)
		if (sourceBuffer[i] == '$')
		{
			u8 splitCheck;
			char splitCheckBuf[4];
			strncpy(splitCheckBuf, &sourceBuffer[i], 4);
			for (int j = 0; j < 4; ++j)
				if (splitCheckBuf[j] == '$') ++splitCheck;

			if (splitCheck == 3)
			{
				vertexEnd = i-1;
				break;
			}
		}


	char* vertexSource = malloc(vertexEnd);
	strncpy(vertexSource, sourceBuffer, vertexEnd);
	vertexSource[vertexEnd] = '\0';

	char* fragmentSource = malloc(sourceLength - (vertexEnd + 4));
	strcpy(fragmentSource, &sourceBuffer[vertexEnd + 4]);
	fragmentSource[sourceLength - (vertexEnd + 4)] = '\0';

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (char const **) &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, (char const **) &fragmentSource, NULL);

	glCompileShader(vertexShader);
	{
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			ERR("%s", infoLog);
		}
	}
	glCompileShader(fragmentShader);
	{
		int success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) 
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			ERR("%s", infoLog);
		}
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	{
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		}
	}

	ret.vertexShader = vertexShader;
	ret.fragmentShader = fragmentShader;
	ret.program = shaderProgram;

	free(vertexSource);
	free(fragmentSource);
	free(sourceBuffer);
	fclose(fp);

	return ret;
}


void UseShader(struct Shader* shader)
{
	glUseProgram(shader->program);
}

void SendUniformMat4(struct Shader* shader, const char* uniformName, mat4s* var)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->program, uniformName), 1, GL_FALSE, (const GLfloat*) &var->raw);
}

void DestroyShader(struct Shader* shader)
{
	glDeleteShader(shader->vertexShader);
	glDeleteShader(shader->fragmentShader);
	glDeleteProgram(shader->program);
}
