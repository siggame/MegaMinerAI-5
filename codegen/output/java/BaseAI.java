
/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of builer-plate code out of the way
///The provided AI class does just that.
public abstract class BaseAI
{
    static Plant[] plants;
    static int iteration;
    boolean initialized;
    
    ///
    ///Make this your username, which should be provided.
    public abstract String username();
    ///
    ///Make this your password, which should be provided.
    public abstract String password();
    ///
    ///This is run on turn 1 before run
    public abstract void init();
    ///
    ///This is run every turn . Return true to end the turn, return false
    ///to request a status update from the server and then immediately rerun this function with the
    ///latest game status.
    public abstract boolean run();

    public boolean startTurn()
    {
        int count = 0;
        count = Client.INSTANCE.getPlantCount();
        plants = new Plant[count];
        for(int i = 0; i < count; i++)
        {
            plants[i] = new Plant(Client.INSTANCE.getPlant(i));
        }

        iteration++;

        if(!initialized)
        {
          initialized = true;
          init();
        }
        return run();
    }


    int boardX()
    {
        return Client.INSTANCE.getBoardX();
    }
    int boardY()
    {
        return Client.INSTANCE.getBoardY();
    }
    int gameNumber()
    {
        return Client.INSTANCE.getGameNumber();
    }
    ///Player 0's light
    int player0Light()
    {
        return Client.INSTANCE.getPlayer0Light();
    }
    ///Player 0's score
    int player0Score()
    {
        return Client.INSTANCE.getPlayer0Score();
    }
    ///Player 1's light
    int player1Light()
    {
        return Client.INSTANCE.getPlayer1Light();
    }
    ///Player 1's score
    int player1Score()
    {
        return Client.INSTANCE.getPlayer1Score();
    }
    ///Player Number; either 0 or 1
    int playerID()
    {
        return Client.INSTANCE.getPlayerID();
    }
    int turnNumber()
    {
        return Client.INSTANCE.getTurnNumber();
    }
}
