from mako.template import Template
from mako import exceptions
import glob

import structures
import conversions
import util

def write(data):
  data['conversions'] = conversions.java
  data['capitalize'] = util.capitalize
  data['lowercase'] = util.lowercase
  data['Model'] = structures.Model
  for file in glob.glob('templates/java/files/*.txt'):
    writeFile(file[21:-4], data) #file[18:-4] should strip the templates/c/files/ and .txt
  for model in data['models']:
    data['model'] = model
    writeModel(data)

def writeFile(name, data):
  try:
    
    template = Template(filename='templates/java/files/%s.txt' % name)
    output = file('output/java/%s' % name, 'w')
    output.write(template.render(**data))
    output.close()
  except:
    print exceptions.text_error_template().render()

def writeModel(data):
  try:
    template = Template(filename='templates/java/model.txt')
    output = file('output/java/%s.java' % data['model'].name, 'w')
    output.write(template.render(**data))
    output.close()
  except:
    print exceptions.text_error_template().render()

if __name__ == '__main__':
  write({})
