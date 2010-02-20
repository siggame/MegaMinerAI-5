import structures

Plant = structures.Model('Plant', key='objectID',
  data = [ ['objectID', int],
    ['x', int],
    ['y', int],
    ['ownerID', int],
    ['leaves', int],
    ['roots', int],
    ['flowers', int],
    ['bark', int],
    ['water', int],
    ['light', int]],
  functions = [ ['growLeaf', [] ],
    ['growRoot', [] ],
    ['growFlower', [] ],
    ['growBark', [] ],
    ['talk', [ ['message', str] ] ]],
  doc = 'A pretty plant.'
  )

add = structures.Animation('Add',
  data = [ ['plantID', int ] ]
  )

remove = structures.Animation('Remove',
  data = [ ['plantID', int ] ]
  )

growLeaf = structures.Animation('GrowLeaf',
  data = [ ['plantID', int ] ]
  )

growRoot = structures.Animation('GrowRoot',
  data = [ ['plantID', int ] ]
  )

growBark = structures.Animation('GrowBark',
  data = [ ['plantID', int ] ]
  )

growFlower = structures.Animation('GrowFlower',
  data = [ ['plantID', int ] ]
  )

talk = structures.Animation('Talk',
  data = [ ['plantID', int ],
    ['message', str] ]
  )

turnNumber = structures.Global('turnNumber', int)
player0Score = structures.Global('player0Score', int, 'Player 0\'s score')
player1Score = structures.Global('player1Score', int, 'Player 1\'s score')

playerID = structures.Global('playerID', int, 'Player Number; either 0 or 1')

maxX = structures.Global('maxX', int)
maxY = structures.Global('maxY', int)

gameNumber = structures.Global('gameNumber', int)