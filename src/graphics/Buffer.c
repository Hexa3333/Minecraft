#include "Buffer.h"
#include <glad.h>
#include <stdbool.h>

struct Buffer CreateBufferVA(float* data, u32 sizeOfData)
{
	struct Buffer ret;
	ret.data = data;
	ret.sizeOfData = sizeOfData;
	ret.indices = NULL;
	ret.sizeOfIndices = 0;
	ret.stride = 3 * sizeof(float);

	glGenVertexArrays(1, &ret.VAO);
	glGenBuffers(1, &ret.VBO);

	glBindVertexArray(ret.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)0);
	glEnableVertexAttribArray(0);

#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif

	return ret;
}

struct Buffer CreateBufferVE(float* data, u32 sizeOfData,
							u32* indices, u32 sizeOfIndices)
{

	struct Buffer ret;
	ret.data = data;
	ret.indices = indices;
	ret.sizeOfIndices = sizeOfIndices;
	ret.stride = 3 * sizeof(float);

	glGenVertexArrays(1, &ret.VAO);
	glGenBuffers(1, &ret.VBO);
	glGenBuffers(1, &ret.EBO);

	glBindVertexArray(ret.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)0);
	glEnableVertexAttribArray(0);


#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
	return ret;
}

struct Buffer CreateBufferVCA(float* data, u32 sizeOfData)
{
	struct Buffer ret;
	ret.data = data;
	ret.sizeOfData = sizeOfData;
	ret.indices = NULL;
	ret.sizeOfIndices = 0;
	ret.stride = 6 * sizeof(float);

	glGenVertexArrays(1, &ret.VAO);
	glGenBuffers(1, &ret.VBO);
	
	glBindVertexArray(ret.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
	
	return ret;
}

struct Buffer CreateBufferVTE(float* data, u32 sizeOfData,
							u32* indices, u32 sizeOfIndices)
{
	struct Buffer ret;
	ret.data = data;
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, ret.stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
	
	return ret;

}


struct Buffer CreateBufferVTN(float* data, u32 sizeOfData, u32* indices, u32 sizeOfIndices)
{
	struct Buffer ret;
	ret.data = data;
	ret.sizeOfData = sizeOfData;
	ret.indices = indices;
	ret.sizeOfIndices = sizeOfIndices;
	ret.stride = 8 * sizeof(float);

	glGenVertexArrays(1, &ret.VAO);
	glGenBuffers(1, &ret.VBO);
	glGenBuffers(1, &ret.EBO);

	glBindVertexArray(ret.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, ret.stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, ret.stride, (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

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
	ret.data = data;
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

struct Buffer_Instanced CreateBufferVTNA_Instanced(float* data, u32 sizeOfData, vec3s* offsets, u32 nOffsets)
{
	struct Buffer_Instanced ret;

	ret.root.data = data;
	ret.root.sizeOfData = sizeOfData;
	ret.root.indices = NULL;
	ret.root.sizeOfIndices = 0;
	ret.root.stride = 11 * sizeof(float);
	ret.instanceCount = nOffsets;

	glGenVertexArrays(1, &ret.root.VAO);
	glGenBuffers(1, &ret.root.VBO);

	glBindVertexArray(ret.root.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.root.VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ret.root.stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, ret.root.stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, ret.root.stride, (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// InstanceVBO
	glGenBuffers(1, &ret.instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.instanceVBO);

	glBufferData(GL_ARRAY_BUFFER, nOffsets * sizeof(vec3s), offsets, GL_STATIC_DRAW);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, ret.root.stride, (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
	
	glVertexAttribDivisor(3, 1);

#ifdef MC_DEBUG
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif

	return ret;
}


struct Buffer CreateBufferVTA(float* data, u32 sizeOfData)
{

	struct Buffer ret;
	ret.data = data;
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

void DrawBufferE(struct Buffer* buffer)
{
	glBindVertexArray(buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->EBO);

	glDrawElements(GL_TRIANGLES, buffer->sizeOfIndices, GL_UNSIGNED_INT, 0);
}

void DrawBufferA(struct Buffer* buffer)
{
	glBindVertexArray(buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->VBO);

	glDrawArrays(GL_TRIANGLES, 0, buffer->sizeOfData);
}

void DrawBufferE_Instanced(struct Buffer_Instanced* buffer)
{

}
void DrawBufferA_Instanced(struct Buffer_Instanced* buffer)
{
	glBindVertexArray(buffer->root.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->root.VBO);
	printf("Instance Cnt: %u\n", buffer->instanceCount);
	glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->root.sizeOfData, buffer->instanceCount);
}

void DrawBufferLine(struct Buffer* buffer)
{
	glBindVertexArray(buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->VBO);

	glDrawArrays(GL_LINES, 0, buffer->sizeOfData);
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

		case (6 * sizeof(float)):
			if (buffer->indices) return VC;
			else return VCA;
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
		case VC:
			return &DrawBufferE;

		case VA:
			return &DrawBufferA;
		case VTA:
			return &DrawBufferA;
		case VTNA:
			return &DrawBufferA;
		case VCA:
			return &DrawBufferA;


		default:
			return &DrawBufferA;
	}
}
