import com.sun.jna.Pointer;

///A pretty plant.
class Plant
{
    Pointer ptr;
    int ID;
    int iteration;
    public Plant(Pointer p)
    {
            ptr = p;
            ID = Client.INSTANCE.plantGetObjectID(ptr);
            iteration = BaseAI.iteration;
    }

    boolean validify()
    {
        if(iteration == BaseAI.iteration) return true;
        for(int i = 0; i < BaseAI.plants.length; i++)
        {
          if(BaseAI.plants[i].ID == ID)
            {
                ptr = BaseAI.plants[i].ptr;
                iteration = BaseAI.iteration;
                return true;
            }
        }
      throw new ExistentialError();
    }
    
    //commands
    
    boolean growLeaf()
    {
        validify();
        return Client.INSTANCE.plantGrowLeaf(ptr);
    }
    boolean growRoot()
    {
        validify();
        return Client.INSTANCE.plantGrowRoot(ptr);
    }
    boolean growFlower(int rootUp, int leafUp, int flowerUp)
    {
        validify();
        return Client.INSTANCE.plantGrowFlower(ptr, rootUp, leafUp, flowerUp);
    }
    boolean spread(int x, int y)
    {
        validify();
        return Client.INSTANCE.plantSpread(ptr, x, y);
    }
    boolean spawn(int x, int y)
    {
        validify();
        return Client.INSTANCE.plantSpawn(ptr, x, y);
    }
    boolean talk(String message)
    {
        validify();
        return Client.INSTANCE.plantTalk(ptr, message);
    }
    
    //getters
    
    public int getObjectID()
    {
        validify();
        return Client.INSTANCE.plantGetObjectID(ptr);
    }
    public int getX()
    {
        validify();
        return Client.INSTANCE.plantGetX(ptr);
    }
    public int getY()
    {
        validify();
        return Client.INSTANCE.plantGetY(ptr);
    }
    public int getOwnerID()
    {
        validify();
        return Client.INSTANCE.plantGetOwnerID(ptr);
    }
    public int getRoot()
    {
        validify();
        return Client.INSTANCE.plantGetRoot(ptr);
    }
    public int getLeaf()
    {
        validify();
        return Client.INSTANCE.plantGetLeaf(ptr);
    }
    public int getFlower()
    {
        validify();
        return Client.INSTANCE.plantGetFlower(ptr);
    }
    public int getHealth()
    {
        validify();
        return Client.INSTANCE.plantGetHealth(ptr);
    }
    public int getRootLevel()
    {
        validify();
        return Client.INSTANCE.plantGetRootLevel(ptr);
    }
    public int getLeafLevel()
    {
        validify();
        return Client.INSTANCE.plantGetLeafLevel(ptr);
    }
    public int getFlowerLevel()
    {
        validify();
        return Client.INSTANCE.plantGetFlowerLevel(ptr);
    }
    public int getRootLevelUp()
    {
        validify();
        return Client.INSTANCE.plantGetRootLevelUp(ptr);
    }
    public int getLeafLevelUp()
    {
        validify();
        return Client.INSTANCE.plantGetLeafLevelUp(ptr);
    }
    public int getFlowerLevelUp()
    {
        validify();
        return Client.INSTANCE.plantGetFlowerLevelUp(ptr);
    }
    public int getCanAct()
    {
        validify();
        return Client.INSTANCE.plantGetCanAct(ptr);
    }
}
