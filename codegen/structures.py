from copy import deepcopy as copy

from odict import OrderedDict

class Model(object):
  data = OrderedDict()
  functions = OrderedDict()
  key = ''
  name = ''
  doc = ''
  parent = None
  def __init__(self, name, **kwargs):
    self.data = OrderedDict()
    self.functions = OrderedDict()
    self.name = name
    if 'parent' in kwargs:
      self.parent =  kwargs['parent']
      self.data = copy(parent.data)
      self.functions = copy(parent.functions)
      self.key = parent.key
    if 'data' in kwargs:
      data = kwargs['data']
      for key, value in data:
        if key in self.data:
          raise ValueError('Duplicate datum %s in %s' % (key, name))
        self.data[key] = value
    if 'functions' in kwargs:
      functions = kwargs['functions']
      for key, value in functions:
        if key in self.functions:
          raise ValueError('Duplicate function %s in %s' % (key, name))
        self.functions[key] = value
    if 'key' in kwargs:
      self.key = kwargs['key']
    if 'doc' in kwargs:
      self.doc = kwargs['doc']

class Global(object):
  name = ''
  type = ''
  doc = ''
  
  def __init__(self, name, type, doc = ''):
    self.name = name
    self.type = type
    self.doc = doc

"""
TODO: Write these.
class Message(object):
  pass

class Function(object):
  arguments = None
  result = None
  
  def __init__(self, arguments, result):
    self.arguments = arguments
    self.result = result
"""