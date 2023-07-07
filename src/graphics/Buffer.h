#ifndef BUFFER_H
#define BUFFER_H

#include "../common.h"
#include <glad/glad.h>

struct Buffer
{
	GLuint VAO, VBO, EBO;
	float* vertices;
	u32 sizeOfData;
	u32* indices;
	u32 sizeOfIndices;
	u8 stride;
};

enum BufferType
{
	V, VT, VTN, 
	VA, VTA, VTNA
};

// Vertex
struct Buffer CreateBufferV(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices);
// Vertex-Texture
struct Buffer CreateBufferVTE(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices);
struct Buffer CreateBufferVTA(float* data, u32 sizeOfData);
// Vertex-Texture-Normals
struct Buffer CreateBufferVTNA(float* data, u32 sizeOfData);
struct Buffer CreateBufferTEST(float* data, u32 sizeOfData);
void DrawBufferE(struct Buffer* buffer);
void DrawBufferA(struct Buffer* buffer);
enum BufferType DetermineBufferType(struct Buffer* buffer);
void* DetermineDrawFunc(enum BufferType bt);

#endif // BUFFER_H
