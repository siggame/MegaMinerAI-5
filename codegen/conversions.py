from util import *

import structures

import data

c = {int:'int', str:'char*', float:'float'}
java = {int:'int', str:'String', float:'float'}
python = {int:'c_int', str:'c_char_p', float:'c_float'}

for i in members(data):
    if isinstance(i, structures.Model):
      c[i] = '_' + i.name + '*' 
      java[i] = 'Pointer'
      python[i] = 'c_void_p'

