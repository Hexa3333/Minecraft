#include "Buffer.h"
#include <glad/glad.h>
#include <stdbool.h>

struct Buffer CreateBufferVE(float* data, u32 sizeOfVertices,
							u32* indices, u32 sizeOfIndices)
{

	struct Buffer ret;
	ret.vertices = data;
	ret.indices = indices;
	ret.sizeOfIndices = sizeOfIndices;
	ret.stride = 3 * sizeof(float);

	glGenVertexArrays(1, &ret.VAO);
	glGenBuffers(1, &ret.VBO);
	glGenBuffers(1, &ret.EBO);

	glBindVertexArray(ret.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
	return ret;
}

struct Buffer CreateBufferVTE(float* data, u32 sizeOfData,
							u32* indices, u32 sizeOfIndices)
{

	struct Buffer ret;
	ret.vertices = data;
	ret.sizeOfData = sizeOfData;
	ret.indices = indices;
	ret.sizeOfIndices = sizeOfIndices;
	ret.stride = 5 * sizeof(float);

	glGenVertexArrays(1, &ret.VAO);
	glGenBuffers(1, &ret.VBO);
	glGenBuffers(1, &ret.EBO);

	glBindVertexArray(ret.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
	
	return ret;

}

struct Buffer CreateBufferVTNA(float* data, u32 sizeOfData)
{

	struct Buffer ret;
	ret.vertices = data;
	ret.sizeOfData = sizeOfData;
	ret.indices = NULL;
	ret.sizeOfIndices = 0;
	ret.stride = 8 * sizeof(float);

	glGenVertexArrays(1, &ret.VAO);
	glGenBuffers(1, &ret.VBO);

	glBindVertexArray(ret.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, ret.stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
	
	return ret;

}

struct Buffer CreateBufferVTA(float* data, u32 sizeOfData)
{

	struct Buffer ret;
	ret.vertices = data;
	ret.sizeOfData = sizeOfData;
	ret.indices = NULL;
	ret.sizeOfIndices = 0;
	ret.stride = 5 * sizeof(float);

	glGenVertexArrays(1, &ret.VAO);
	glGenBuffers(1, &ret.VBO);

	glBindVertexArray(ret.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, ret.stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
	
	return ret;

}

void BindBuffer(struct Buffer* buffer)
{
	enum BufferType bf = DetermineBufferType(buffer);
	glBindVertexArray(buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->VBO);
	if (bf == V | bf == VT | bf == VTN)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->VBO);
}

void DrawBufferE(struct Buffer* buffer)
{
	BindBuffer(buffer);
	glDrawElements(GL_TRIANGLES, buffer->sizeOfIndices, GL_UNSIGNED_INT, 0);
}

void DrawBufferA(struct Buffer* buffer)
{
	BindBuffer(buffer);
	glDrawArrays(GL_TRIANGLES, 0, buffer->sizeOfData);
}

enum BufferType DetermineBufferType(struct Buffer* buffer)
{
	switch (buffer->stride)
	{
		case (3 * sizeof(float)):
			if (buffer->indices) return V;
			else return VA;
			break;

		case (5 * sizeof(float)):
			if (buffer->indices) return VT;
			else return VTA;
			break;

		case (8 * sizeof(float)):
			if (buffer->indices) return VTN;
			else return VTNA;
			break;

		default:
			return -1;
	}
}


void* DetermineDrawFunc(enum BufferType bt)
{
	switch (bt)
	{
		case V:
			return &DrawBufferE;
		case VT:
			return &DrawBufferE;
		case VTN:
			return &DrawBufferE;

		case VA:
			return &DrawBufferA;
		case VTA:
			return &DrawBufferA;
		case VTNA:
			return &DrawBufferA;
	}		
}
