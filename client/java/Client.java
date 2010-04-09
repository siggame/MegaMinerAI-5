import com.sun.jna.Library;
import com.sun.jna.Pointer;
import com.sun.jna.Native;

public interface Client extends Library {
    Client INSTANCE = (Client)Native.loadLibrary("client", Client.class);
    int open_server_connection(String host, String port);

    boolean serverLogin(int socket, String username, String password);
    int createGame();
    int joinGame(int id);

    void endTurn();
    void getStatus();

    int networkLoop(int socket);


    //commands
    boolean plantGrowLeaf(Pointer object);
    boolean plantGrowRoot(Pointer object);
    boolean plantGrowFlower(Pointer object, int rootUp, int leafUp, int flowerUp);
    boolean plantSpread(Pointer object, int x, int y);
    boolean plantSpawn(Pointer object, int x, int y);
    boolean plantTalk(Pointer object, String message);

    //accessors
    int getBoardX();
    int getBoardY();
    int getGameNumber();
    int getPlayer0Light();
    int getPlayer0Score();
    int getPlayer1Light();
    int getPlayer1Score();
    int getPlayerID();
    int getTurnNumber();

    Pointer getPlant(int num);
    int getPlantCount();


    //getters
    int plantGetObjectID(Pointer ptr);
    int plantGetX(Pointer ptr);
    int plantGetY(Pointer ptr);
    int plantGetOwnerID(Pointer ptr);
    int plantGetRoot(Pointer ptr);
    int plantGetLeaf(Pointer ptr);
    int plantGetFlower(Pointer ptr);
    int plantGetHealth(Pointer ptr);
    int plantGetRootLevel(Pointer ptr);
    int plantGetLeafLevel(Pointer ptr);
    int plantGetFlowerLevel(Pointer ptr);
    int plantGetRootLevelUp(Pointer ptr);
    int plantGetLeafLevelUp(Pointer ptr);
    int plantGetFlowerLevelUp(Pointer ptr);
    int plantGetCanAct(Pointer ptr);
    int plantLeafCost(Pointer ptr);
    int plantRootCost(Pointer ptr);
    int plantFlowerCost(Pointer ptr);
    int plantLeafHealthCost(Pointer ptr);
    int plantRootHealthCost(Pointer ptr);
    int plantFlowerHealthCost(Pointer ptr);
    int plantSpreadCost(Pointer ptr);
    int plantSpawnCost(Pointer ptr);



}
