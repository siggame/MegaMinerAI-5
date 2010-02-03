import structures

client = 0
server = 1

Plant = structures.Model('Plant', key='objectID',
  data = ( ('objectID', int),
    ('ownerID', int),
    ('x', int),
    ('y', int),
    ('roots', int),
    ('flowers', int)),
  functions = ( ('growLeaf', () ),
    ('growRoot', () ),
    ('talk', ( ('message', str),) )),
  doc = 'A pretty plant.'
  )

turnNumber = structures.Global('turnNumber', int)
player0Light = structures.Global('player0Light', int, 'Player 0\'s light')
player0Water = structures.Global('player0Water', int, 'Player 0\'s water')
player1Light = structures.Global('player1Light', int, 'Player 1\'s light')
player1Water = structures.Global('player1Water', int, 'Player 1\'s water')

playerID = structures.Global('playerID', int, 'Player Number; either 0 or 1')

maxX = structures.Global('maxX', int)
maxY = structures.Global('maxY', int)

