#ifndef UTIL_H
#define UTIL_H

#include "common.h"
#include "Chunk.h"
#include <cglm/struct.h>

void CreateLine(float* out, vec3s start, vec3s end, vec3s color);
void GetNeighboringBlocks(struct Chunk* chunk, u16 blockIndex);

#endif // UTIL_H
