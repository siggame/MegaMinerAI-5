"""
    Class files for a game server, interacting with the redirect server.
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

from networking.Client import Client
from filters.LogicFilter import SexprHandlerMixin
from statements.StatementUtils import require_login, require_length, dict_wrapper 

def protocol():
    statements = {}
    mapper = dict_wrapper(statements)

    @mapper("add")
    @require_length(2)
    def add(self, expr):
        '''
        takes an id, but how do I know what to display?
        '''
        pass

    @mapper("remove")
    @require_length(2)
    def remove(self, expr):
        pass
    
    @mapper("move")
    @require_length(4)
    def move(self, expr):
        pass

    @mapper("attack")
    @require_length(4)
    def attack(self, expr):
        pass

    @mapper("hurt")
    @requires_length(3)
    def hurt(self, expr):
        pass

    @mapper("build")
    @requires_length(4)
    def build(self, expr):
        pass

    @mapper("train")
    @requires_length(3)
    def train(self, expr):
        pass

    return statements

class VisualizerClient(Client, SexprHandlerMixin):
    """
    Glues the visualizer and protocol together
    """
    def __init__(self, *args, **kwargs):
        Client.__init__(self, *args, **kwargs)
        self.statements = protocol()

    
    
