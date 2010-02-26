import structures

Plant = structures.Model('Plant', key='objectID',
  data = [ ['objectID', int],
    ['x', int],
    ['y', int],
    ['ownerID', int],
    ['root', int],
    ['leaf', int],
    ['flower', int],
    ['health', int],
    ['rootLevel', int],
    ['leafLevel', int],
    ['flowerLevel', int],
    ['rootLevelUp', int],
    ['leafLevelUp', int],
    ['flowerLevelUp', int],
    ['canAct', int]],
  functions = [ ['growLeaf', [] ],
    ['growRoot', [] ],
    ['growFlower', [ ['rootUp', int], ['leafUp', int], ['flowerUp', int] ] ],
    ['spread', [ ['x', int], ['y', int] ] ],
    ['spawn', [ ['x', int], ['y', int] ] ],
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

growFlower = structures.Animation('GrowFlower',
  data = [ ['plantID', int ] ]
  )

spread = structures.Animation('Spread',
  data = [ ['parentID', int ], ['childID', int] ]
  )

spawn = structures.Animation('spawn',
  data = [ ['parentID', int ], ['childID', int] ]
  )

talk = structures.Animation('Talk',
  data = [ ['plantID', int ],
    ['message', str] ]
  )

turnNumber = structures.Global('turnNumber', int)
player0Score = structures.Global('player0Score', int, 'Player 0\'s score')
player1Score = structures.Global('player1Score', int, 'Player 1\'s score')

player0Light = structures.Global('player0Light', int, 'Player 0\'s light')
player1Light = structures.Global('player1Light', int, 'Player 1\'s light')

playerID = structures.Global('playerID', int, 'Player Number; either 0 or 1')

boardX = structures.Global('boardX', int)
boardY = structures.Global('boardY', int)

gameNumber = structures.Global('gameNumber', int)
