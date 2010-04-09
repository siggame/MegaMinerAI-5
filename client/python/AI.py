#-*-python-*-
from BaseAI import BaseAI
from GameObject import *

class AI(BaseAI):
    """The class implementing gameplay logic."""
    @staticmethod
    def username():
        return "Shell AI"

    @staticmethod
    def password():
        return "password"

    #This function is called once, before your first turn
    def init(self):
        self.sendTag("shell")
	self.sendTag("version 0")

    #This function is called each time it is your turn
    #Return true to end your turn, return false to ask the server for updated information
    def run(self):
        return 1


      
