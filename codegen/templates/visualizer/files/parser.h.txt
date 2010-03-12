#ifndef PARSER_H
#define PARSER_H

#include "structures.h"

bool parseFile(Game& game, char* filename);
bool parseString(Game& game, char* string);

#endif
