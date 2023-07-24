#ifndef BUFFER_H
#define BUFFER_H

#include "../common.h"
#include <glad.h>
#include <cglm/struct.h>

struct Buffer
{
	GLuint VAO, VBO, EBO;
	float* data;
	void (*render)(struct Buffer*);
	u32 sizeOfData;
	u32* indices;
	u32 sizeOfIndices;
	u8 stride;
};

struct Buffer_Instanced
{
	struct Buffer root;
	GLuint instanceVBO;
	u32 instanceCount;
};

enum BufferType
{
	VA, VE,				// 3 floats
	VTA, VTE,			// 5 floats
	VCA, VCE, VNA, VNE, // 6 floats
	VTNA, VTNE,			// 8 floats
	LINE = VCA
};

// Vertex
struct Buffer CreateBufferVA(float* data, u32 sizeOfData);
struct Buffer CreateBufferVE(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices);

// Vertex Color
struct Buffer CreateBufferVCA(float* data, u32 sizeOfData);
struct Buffer CreateBufferVCE(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices);

// Vertex-Normals
struct Buffer CreateBufferVNA(float* data, u32 sizeOfData);
struct Buffer CreateBufferVNE(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices);

// Vertex-Texture
struct Buffer CreateBufferVTA(float* data, u32 sizeOfData);
struct Buffer CreateBufferVTE(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices);

// Vertex-Texture-Normals
struct Buffer CreateBufferVTNA(float* data, u32 sizeOfData);
struct Buffer CreateBufferVTNE(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices);

// Vertex-Colors
struct Buffer_Instanced CreateBufferVCA_Instanced(float* data, u32 sizeOfData, vec3s* offsets, u32 nOffsets);
struct Buffer_Instanced CreateBufferVCE_Instanced(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices, vec3s* offsets, u32 nOffsets);

// Vertex-Texture-Normals (Instanced)
struct Buffer_Instanced CreateBufferVTNA_Instanced(float* data, u32 sizeOfData, vec3s* offsets, u32 nOffsets);
struct Buffer_Instanced CreateBufferVTNE_Instanced(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices, vec3s* offsets, u32 nOffsets);

void DrawBufferE(struct Buffer* buffer);
void DrawBufferA(struct Buffer* buffer);
void DrawBufferE_Instanced(struct Buffer_Instanced* buffer);
void DrawBufferA_Instanced(struct Buffer_Instanced* buffer);
void DrawBufferLine(struct Buffer* buffer);

enum BufferType DetermineBufferType(struct Buffer* buffer);
void* DetermineDrawFunc(enum BufferType bt);

#endif // BUFFER_H
