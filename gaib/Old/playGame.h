#ifndef PLAY_GAME_H
#define PLAY_GAME_H

/* This file is a functionalized version of the main.cpp standard for this competition
   It is used by GAIB to stage a match, returns false if game failed.
   Results = First players score - second players score after game
*/

#include <iostream>
#include <cstring>

#include "AI.h"
#include "network.h"
#include "game.h"
#include "sexp/sexp.h"

#include <sys/types.h>
#include <unistd.h>

using namespace std;
//controls initialization

bool playGame(AI& firstPlayer,AI& secondPlayer,char* host,int&results);
#endif

