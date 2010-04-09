#include "parser.h"
#include "sexp/sexp.h"

#include <cstdio>
#include <cstring>

using namespace std;


static void parsePlant(Plant& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object.objectID = atoi(sub->val);
  sub = sub->next;
  object.x = atoi(sub->val);
  sub = sub->next;
  object.y = atoi(sub->val);
  sub = sub->next;
  object.ownerID = atoi(sub->val);
  sub = sub->next;
  object.root = atoi(sub->val);
  sub = sub->next;
  object.leaf = atoi(sub->val);
  sub = sub->next;
  object.flower = atoi(sub->val);
  sub = sub->next;
  object.health = atoi(sub->val);
  sub = sub->next;
  object.rootLevel = atoi(sub->val);
  sub = sub->next;
  object.leafLevel = atoi(sub->val);
  sub = sub->next;
  object.flowerLevel = atoi(sub->val);
  sub = sub->next;
  object.rootLevelUp = atoi(sub->val);
  sub = sub->next;
  object.leafLevelUp = atoi(sub->val);
  sub = sub->next;
  object.flowerLevelUp = atoi(sub->val);
  sub = sub->next;
  object.canAct = atoi(sub->val);
  sub = sub->next;
  
}

static void parseAdd(Add& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->next;
  
  object.type = ADD;
  
  object.plantID = atoi(sub->val);
  sub = sub->next;
  
}
static void parseGrowFlower(GrowFlower& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->next;
  
  object.type = GROWFLOWER;
  
  object.plantID = atoi(sub->val);
  sub = sub->next;
  
}
static void parseGrowLeaf(GrowLeaf& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->next;
  
  object.type = GROWLEAF;
  
  object.plantID = atoi(sub->val);
  sub = sub->next;
  
}
static void parseGrowRoot(GrowRoot& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->next;
  
  object.type = GROWROOT;
  
  object.plantID = atoi(sub->val);
  sub = sub->next;
  
}
static void parseRemove(Remove& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->next;
  
  object.type = REMOVE;
  
  object.plantID = atoi(sub->val);
  sub = sub->next;
  
}
static void parseSpawn(spawn& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->next;
  
  object.type = SPAWN;
  
  object.parentID = atoi(sub->val);
  sub = sub->next;
  object.childID = atoi(sub->val);
  sub = sub->next;
  
}
static void parseSpread(Spread& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->next;
  
  object.type = SPREAD;
  
  object.parentID = atoi(sub->val);
  sub = sub->next;
  object.childID = atoi(sub->val);
  sub = sub->next;
  
}
static void parseTalk(Talk& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->next;
  
  object.type = TALK;
  
  object.plantID = atoi(sub->val);
  sub = sub->next;
  object.message = new char[strlen(sub->val)+1];
  strncpy(object.message, sub->val, strlen(sub->val));
  object.message[strlen(sub->val)] = 0;
  sub = sub->next;
  
}

static bool parseSexp(Game& game, sexp_t* expression)
{
  sexp_t* sub, *subsub;
  expression = expression->list;
  if(expression->val != NULL && strcmp(expression->val, "status") == 0)
  {
    GameState gs;
    while(expression->next != NULL)
    {
      expression = expression->next;
      sub = expression->list;
      if(string(sub->val) == "game")
      {
          sub = sub->next;
          gs.turnNumber = atoi(sub->val);
          sub = sub->next;
          
          gs.player0Score = atoi(sub->val);
          sub = sub->next;
          
          gs.player1Score = atoi(sub->val);
          sub = sub->next;
          
          gs.player0Light = atoi(sub->val);
          sub = sub->next;

          gs.player1Light = atoi(sub->val);
          sub = sub->next;
          
          gs.boardX = atoi(sub->val);
          sub = sub->next;
          
          gs.boardY = atoi(sub->val);
      }
      else if(string(sub->val) == "Plant")
      {
        sub = sub->next;
        while(sub)
        {
          Plant object;
          parsePlant(object, sub);
          gs.plants.push_back(object);
          
          sub = sub->next;
        }
      }
    }
    game.states.push_back(gs);
  }
  else if(string(expression->val) == "animations")
  {
    std::vector<Animation*> animations;
    while(expression->next)
    {
      expression = expression->next;
      sub = expression->list;
      if(string(sub->val) == "add")
      {
        Add* animation = new Add;
        parseAdd(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "grow-flower")
      {
        GrowFlower* animation = new GrowFlower;
        parseGrowFlower(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "grow-leaf")
      {
        GrowLeaf* animation = new GrowLeaf;
        parseGrowLeaf(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "grow-root")
      {
        GrowRoot* animation = new GrowRoot;
        parseGrowRoot(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "remove")
      {
        Remove* animation = new Remove;
        parseRemove(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "spawn")
      {
        spawn* animation = new spawn;
        parseSpawn(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "spread")
      {
        Spread* animation = new Spread;
        parseSpread(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "talk")
      {
        Talk* animation = new Talk;
        parseTalk(*animation, sub);
        animations.push_back(animation);
      }
    }
    game.states[game.states.size()-1].animations = animations;
  }
  else if(string(expression->val) == "ident")
  {
    expression = expression->next;
    sub = expression->list;
    while(sub)
    {
      subsub = sub->list;
      int number = atoi(subsub->val);
      if(number >= 0)
      {
        subsub = subsub->next->next;
        game.players[number] = subsub->val;
      }
      sub = sub->next;
    }
  }
  else if(string(expression->val) == "game-winner")
  {
    expression = expression->next;
    game.winner = atoi(expression->val);
  }
}

bool parseFile(Game& game, char* filename)
{
  bool value;
  FILE* in = fopen(filename, "r");
  int size;
  if(!in)
    return false;
  
  fseek(in, 0, SEEK_END);
  size = ftell(in);
  fseek(in, 0L, SEEK_SET);
  
  char* buffer = new char[size+1];
  fread(buffer, 1, size, in);
  buffer[size] = 0;
  
  fclose(in);
  
  value = parseString(game, buffer);
  
  delete[] buffer;
  
  return value;
}


bool parseString(Game& game, char* string)
{
  sexp_t* st = NULL;
  pcont_t* cc;
  cc = init_continuation(string);
  
  while(st = iparse_sexp( string, strlen(string), cc))
  {
    parseSexp(game, st);
    destroy_sexp(st);
  }
  
  return true;
}