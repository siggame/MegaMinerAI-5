from StatementUtils import require_login, require_length, dict_wrapper
statements = {}
mapper = dict_wrapper(statements)

@mapper("login")
@require_length(3)
def login(self, expression):
    if  self.user:
        self.writeSExpr(['login-denied', 'already logged in'])
    else:
        if self.login(expression[1], expression[2]):
            self.writeSExpr(['login-accepted', 1.0])#client_version])
        else:
            self.writeSExpr(['login-denied', 'invalid username or password'])

@mapper("logout")
@require_length(1)
def logout(self, expression):
    if self.logout():
        self.writeSExpr(['logout-accepted'])
        return True
    else:
        self.writeSExpr(['logout-denied', 'not logged in'])
        return False

