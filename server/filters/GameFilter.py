"""
    Stub for Game Implementation.
    Copyright (C) 2009  Josh Bohde <josh.bohde@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""                                             

from LogicFilter import LogicFilter
import statements.Statements as Statements
import statements.GameStatements as GameStatements
import statements.ServerStatements as ServerStatements

class GameFilter(LogicFilter):
     def _init(self):
        LogicFilter._init(self)
        self.statements = Statements.statements
        for k in GameStatements.statements.keys():
            self.statements[k] = GameStatements.statements[k]
        for k in ServerStatements.statements.keys():
            self.statements[k] = ServerStatements.statements[k]


