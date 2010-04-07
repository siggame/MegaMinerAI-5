public class Main
{
    public static void main(String[] args)
    {
        boolean practice = false; //this must not be touched!
        if(args.length < 1)
        {
            System.out.println("Please enter a hostname");
            return;
        }

        AI ai = new AI();
        int socket = Client.INSTANCE.open_server_connection(args[0], "19000");
        if(socket == -1)
        {
          System.err.println("Unable to connect to server");
          return;
        }
        if(!(Client.INSTANCE.serverLogin(socket, ai.username(), ai.password())))
        {
          return;
        }

        if(args.length < 2)
        {
          socket = Client.INSTANCE.createGame();
        }
        else
        {
          socket = Client.INSTANCE.joinGame(Integer.parseInt(args[1]));
        }
        while(Client.INSTANCE.networkLoop(socket) != 0)
        {
            if(ai.startTurn())
            {
              Client.INSTANCE.endTurn();
            }
            else
            {
              Client.INSTANCE.getStatus();
            }
        }
        //request the log file
        while(Client.INSTANCE.networkLoop(socket) != 0)
        return;
    }
}
