#ifndef UTIL_H
#define UTIL_H

#include "common.h"
#include "Chunk.h"
#include <cglm/struct.h>
#include <assert.h>

void CreateLine(float* out, vec3s start, vec3s end, vec3s color);
void SetNeighboringBlocks(struct Chunk* chunk, u8 blockIndexX, u8 blockIndexY, u8 blockIndexZ);
void SetChunkInnerBlocksInvisible(struct Chunk* chunk);
void CullBackFaces(struct Chunk* chunk);

#endif // UTIL_H
