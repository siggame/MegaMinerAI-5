#include "AI.h"

/// The user name with which you logged into this computer
const char* AI::username()
{
  return "Shell AI";
}

/// The password with which you logged into this computer
const char* AI::password()
{
  return "password";
}

/// This function is run once, before your first turn.
void AI::init()
{
  sendTag("shellAI");
  sendTag("version 0");
}

/// This function is called each time it is your turn.

/// Return true to end your turn, return false to ask the server for updated information.
///
bool AI::run()
{
  return true;
}
