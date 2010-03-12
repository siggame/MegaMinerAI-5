class GameObject(object):
    """
    All objects that appear in the game will inherit from this class.
    This class assigns each object a unique id.

    All objects in the game should specify a toList function first call's
    the toList function of its base class and then adds all of its relevant
    stats to the list. These stats will be sent in S-Expressions to the
    client whenever the player can see this object.

    All objects in the game should also specify a nextTurn function to be
    called at the beginning of each turn.
    """

    def __init__(self, game):
        self.game = game
        self.id = game.nextid
        self.turnCreated = game.turnNum
        self.changed = True
        game.nextid += 1
        if game.nextid > game.maxid:
            game.nextid = 0

    def toList(self):
        list = [self.id]
        return list

    def nextTurn(self):
        pass

