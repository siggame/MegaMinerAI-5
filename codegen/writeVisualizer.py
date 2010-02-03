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
  for file in glob.glob('templates/visualizer/files/*.txt'):
    writeFile(file[26:-4], data)

def writeFile(name, data):
  try:
    template = Template(filename='templates/visualizer/files/%s.txt' % name)
    output = file('output/visualizer/%s' % name, 'w')
    output.write(template.render(**data))
    output.close()
  except:
    print exceptions.text_error_template().render()

if __name__ == '__main__':
  write({})
