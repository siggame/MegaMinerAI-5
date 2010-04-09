# -*- python -*-

from library import library

class BaseAI:
    """@brief A basic AI interface.

    This class implements most the code an AI would need to interface with the lower-level game code.
    AIs should extend this class to get a lot of builer-plate code out of the way
    The provided AI class does just that.
    """
    initialized = False
    iteration = 0
    plants = []

    def startTurn(self):
        from GameObject import Plant

        BaseAI.plants = [Plant(library.getPlant(i)) for i in xrange(library.getPlantCount())]

        if not self.initialized:
            self.initialized = True
            self.init()
        BaseAI.iteration += 1;
        return self.run()
    
    @staticmethod
    def boardX():
        return library.getBoardX()

    @staticmethod
    def boardY():
        return library.getBoardY()

    @staticmethod
    def gameNumber():
        return library.getGameNumber()

    @staticmethod
    def player0Light():
        """Player 0's light
        """
        return library.getPlayer0Light()

    @staticmethod
    def player0Score():
        """Player 0's score
        """
        return library.getPlayer0Score()

    @staticmethod
    def player1Light():
        """Player 1's light
        """
        return library.getPlayer1Light()

    @staticmethod
    def player1Score():
        """Player 1's score
        """
        return library.getPlayer1Score()

    @staticmethod
    def playerID():
        """Player Number; either 0 or 1
        """
        return library.getPlayerID()

    @staticmethod
    def turnNumber():
        return library.getTurnNumber()

    @staticmethod
    def sendTag(tag):
        return library.sendTag(tag)

