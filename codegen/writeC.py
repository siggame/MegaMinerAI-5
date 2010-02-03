from mako.template import Template
from mako import exceptions
import glob

import structures
import conversions
import util

def write(data):
  data['conversions'] = conversions.c
  data['capitalize'] = util.capitalize
  data['lowercase'] = util.lowercase
  data['dashify'] = util.dashify
  data['Model'] = structures.Model
  for file in glob.glob('templates/c/files/*.txt'):
    writeFile(file[18:-4], data) #file[18:-4] should strip the templates/c/files/ and .txt

def writeFile(name, data):
  try:
    template = Template(filename='templates/c/files/%s.txt' % name)
    output = file('output/c/%s' % name, 'w')
    output.write(template.render(**data))
    output.close()
  except:
    print exceptions.text_error_template().render()

if __name__ == '__main__':
  write({})
