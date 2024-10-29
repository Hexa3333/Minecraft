#ifndef UTIL_H
#define UTIL_H

#include "common.h"
#include <cglm/struct.h>
#include <assert.h>
#include "Block.h"
#include "Chunk.h"

void CreateLine(float* out, vec3s start, vec3s end, vec3s color);
vec3s* GetChunkOffsets();
float* GetSpriteXYFromSheet(u8 tileIndexX, u8 tileIndexY);
enum BLOCK_TEX_NAMES MapBlocksToTextures(enum BLOCK_TYPE blockType);
void CalculateUVsOfBlock(float* out, enum BLOCK_TEX_NAMES texName);
void SetNeighboringBlocks(struct Chunk* chunk, u8 blockIndexX, u8 blockIndexY, u8 blockIndexZ);
void SetNeighboringBlocksOfChunk(struct Chunk* chunk);
void SetChunkInnerBlocksInvisible(struct Chunk* chunk);
void CullBackFaces(struct Chunk* chunk);

#endif // UTIL_H
