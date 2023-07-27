#ifndef UTIL_H
#define UTIL_H

#include "common.h"
#include <cglm/struct.h>
#include <assert.h>

void CreateLine(float* out, vec3s start, vec3s end, vec3s color);
vec3s* GetChunkOffsets();
float* GetSpriteXYFromSheet(u8 tileIndexX, u8 tileIndexY);
enum BLOCK_TEX_NAMES MapBlocksToTextures(enum BLOCK_TYPE blockType);
u8* ChunkFlattenIndex(u16 index);
void SetNeighboringBlocks(struct Chunk_Instanced* chunk, u8 blockIndexX, u8 blockIndexY, u8 blockIndexZ);
void SetNeighboringBlocksOfChunk(struct Chunk_Instanced* chunk);
void SetChunkInnerBlocksInvisible(struct Chunk_Instanced* chunk);
void CullBackFaces(struct Chunk_Instanced* chunk);

#endif // UTIL_H