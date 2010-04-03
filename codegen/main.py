#!/usl/bin/env python
import data
import structures
from util import *

def insertModel(list, model):
  if model.parent and model.parent not in list:
    insertModel(list, model.parent)
  list.append(model)

def parseData():
  models = []
  globals = []
  animations = []
  for i in members(data):
    if isinstance(i, structures.Model):
      insertModel(models, i)
    elif isinstance(i, structures.Global):
      globals.append(i)
    elif isinstance(i, structures.Animation):
      animations.append(i)
  return {'models':models, 'globals':globals, 'animations':animations}



if __name__ == '__main__':
  objects = parseData()
  import writeC
  writeC.write(objects)

  import writeJava
  writeJava.write(objects)

  import writePython
  writePython.write(objects)


  import writeVisualizer
  writeVisualizer.write(objects)