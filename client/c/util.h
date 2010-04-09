#ifndef UTIL_H
#define UTIL_H

#include "structures.h"

#ifdef __cplusplus
extern "C"
{
#endif

int plantLeafCost(_Plant* ptr);
int plantRootCost(_Plant* ptr);
int plantFlowerCost(_Plant* ptr);

int plantSpreadCost(_Plant* ptr);
int plantSpawnCost(_Plant* ptr);
  
#ifdef __cplusplus
}
#endif

#endif
