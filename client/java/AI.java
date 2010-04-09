///The class implementing gameplay logic.
class AI extends BaseAI
{
  public String username()
  {
    return "Shell AI";
  }
  public String password()
  {
    return "password";
  }

  //This function is called each time it is your turn
  //Return true to end your turn, return false to ask the server for updated information
  public boolean run()
  {
    return true;
  }


  //This function is called once, before your first turn
  public void init()
  {
    sendTag("shell");
    sendTag("version 0");
  }
}
