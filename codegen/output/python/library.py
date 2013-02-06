# -*-python-*-

import os

from ctypes import *

try:
  if os.name == 'posix':
    library = CDLL("../c/libclient.so")
  elif os.name == 'nt':
    library = CDLL("../c/client.dll")
  else:
    raise Exception("Unrecognized OS: "+os.name)
except OSError:
  raise Exception("It looks like you didn't build libclient. Run 'make' and try again.")

# commands

library.serverLogin.restype = c_bool
library.serverLogin.argtypes = [c_int, c_char_p, c_char_p]

library.createGame.restype = c_int
library.createGame.argtypes = []

library.joinGame.restype = c_int
library.joinGame.argtypes = [c_int]

library.endTurn.restype = None
library.endTurn.argtypes = []

library.getStatus.restype = None
library.getStatus.argtypes = []

library.networkLoop.restype = c_int
library.networkLoop.argtypes = [c_int]

library.plantGrowLeaf.restype = c_bool
library.plantGrowLeaf.argtypes = [c_void_p]

library.plantGrowRoot.restype = c_bool
library.plantGrowRoot.argtypes = [c_void_p]

library.plantGrowFlower.restype = c_bool
library.plantGrowFlower.argtypes = [c_void_p, c_int, c_int, c_int]

library.plantSpread.restype = c_bool
library.plantSpread.argtypes = [c_void_p, c_int, c_int]

library.plantSpawn.restype = c_bool
library.plantSpawn.argtypes = [c_void_p, c_int, c_int]

library.plantTalk.restype = c_bool
library.plantTalk.argtypes = [c_void_p, c_char_p]

# accessors

library.getBoardX.restype = c_int
library.getBoardX.argtypes = []

library.getBoardY.restype = c_int
library.getBoardY.argtypes = []

library.getGameNumber.restype = c_int
library.getGameNumber.argtypes = []

library.getPlayer0Light.restype = c_int
library.getPlayer0Light.argtypes = []

library.getPlayer0Score.restype = c_int
library.getPlayer0Score.argtypes = []

library.getPlayer1Light.restype = c_int
library.getPlayer1Light.argtypes = []

library.getPlayer1Score.restype = c_int
library.getPlayer1Score.argtypes = []

library.getPlayerID.restype = c_int
library.getPlayerID.argtypes = []

library.getTurnNumber.restype = c_int
library.getTurnNumber.argtypes = []

library.getPlant.restype = c_void_p
library.getPlant.argtypes = [c_int]

library.getPlantCount.restype = c_int
library.getPlantCount.argtypes = []

# getters

library.plantGetObjectID.restype = c_int
library.plantGetObjectID.argtypes = [c_void_p]

library.plantGetX.restype = c_int
library.plantGetX.argtypes = [c_void_p]

library.plantGetY.restype = c_int
library.plantGetY.argtypes = [c_void_p]

library.plantGetOwnerID.restype = c_int
library.plantGetOwnerID.argtypes = [c_void_p]

library.plantGetRoot.restype = c_int
library.plantGetRoot.argtypes = [c_void_p]

library.plantGetLeaf.restype = c_int
library.plantGetLeaf.argtypes = [c_void_p]

library.plantGetFlower.restype = c_int
library.plantGetFlower.argtypes = [c_void_p]

library.plantGetHealth.restype = c_int
library.plantGetHealth.argtypes = [c_void_p]

library.plantGetRootLevel.restype = c_int
library.plantGetRootLevel.argtypes = [c_void_p]

library.plantGetLeafLevel.restype = c_int
library.plantGetLeafLevel.argtypes = [c_void_p]

library.plantGetFlowerLevel.restype = c_int
library.plantGetFlowerLevel.argtypes = [c_void_p]

library.plantGetRootLevelUp.restype = c_int
library.plantGetRootLevelUp.argtypes = [c_void_p]

library.plantGetLeafLevelUp.restype = c_int
library.plantGetLeafLevelUp.argtypes = [c_void_p]

library.plantGetFlowerLevelUp.restype = c_int
library.plantGetFlowerLevelUp.argtypes = [c_void_p]

library.plantGetCanAct.restype = c_int
library.plantGetCanAct.argtypes = [c_void_p]

