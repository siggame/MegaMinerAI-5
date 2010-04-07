#ifndef GETTERS_H 
#define GETTERS_H
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

int plantGetObjectID(_Plant* ptr);
int plantGetX(_Plant* ptr);
int plantGetY(_Plant* ptr);
int plantGetOwnerID(_Plant* ptr);
int plantGetRoot(_Plant* ptr);
int plantGetLeaf(_Plant* ptr);
int plantGetFlower(_Plant* ptr);
int plantGetHealth(_Plant* ptr);
int plantGetRootLevel(_Plant* ptr);
int plantGetLeafLevel(_Plant* ptr);
int plantGetFlowerLevel(_Plant* ptr);
int plantGetRootLevelUp(_Plant* ptr);
int plantGetLeafLevelUp(_Plant* ptr);
int plantGetFlowerLevelUp(_Plant* ptr);
int plantGetCanAct(_Plant* ptr);

#ifdef __cplusplus
}
#endif

#endif
