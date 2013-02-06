"""
    Various utilities for statement files.
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

from functools import wraps

def dict_wrapper(statements):
    def wrapper(string):
        def dec(f):
            statements[string] = f
            return f
        return dec
    return wrapper

def verifyLength(self, expression, *lengths):
    if len(expression) not in lengths:
        self.writeSExpr(['argument-count', expression, lengths])
        return False
    return True

def require_length(*n):
    def dec(f):
        @wraps(f)
        def wrapper(self, expression):
            if not verifyLength(self, expression, *n):
                return False
            return f(self, expression)
        return wrapper
    return dec

def require_login(f):
    @wraps(f)
    def wrapper(self, expression):
        if not self.user:
            self.writeSExpr([expression[0]+'-denied', 'not logged in'])
            return False
        return f(self, expression)
    return wrapper

def require_game(f):
    @wraps(f)
    def wrapper(self, expression):
        if self.game is None:
            self.writeSExpr([expression[0]+'-denied', 'not in a game'])
            return False
        return f(self, expression)
    return wrapper
