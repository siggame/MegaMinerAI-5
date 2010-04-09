from sexpr.sexpr import *
import bz2
import os

class Scribe:
    """
    A mock connection that joins every game as a 
    spectator and creates game logs.
    """
    def __init__(self, logPath):
        self.messages = [] #A list of messages this player has received
        self.user = "Scribe"
        self.screenName = "Scribe"
        self.logPath = logPath
        self.tags = ["", "", ""]
        if (not os.path.exists("logs/")):
            os.mkdir("logs/")
        if (os.path.exists(self.logPath)):
            os.remove(self.logPath)

    def writeSExpr(self, message):
        log = open(self.logPath, "a")
        log.write(sexpr2str(message))

    def addTag(self, message, playerIndex = -1):
        if (self.tags[playerIndex+1] != ""):
            message = ", %s"%(message,)
        self.tags[playerIndex + 1] += message

    def finalize(self):
        compressedLog = bz2.BZ2File("%s.bz2"%(self.logPath,), "w")
        log = open(self.logPath, "r")
        compressedLog.write(log.read())
        tagFileName = "%s.tags"%(self.logPath[:-len(".gamelog")],)
        tagFile = open(tagFileName, "w")
        for line in self.tags:
            tagFile.write("%s\n"%(line,))

