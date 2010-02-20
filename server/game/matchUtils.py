from functools import wraps

def verifyReferences(self, expression, references):
    for i in range(0, len(references)):
        if references[i] is not None:
            if expression[i] not in self.objects:
                return str(expression[i]) + " does not exist"
            if not isinstance(self.objects[expression[i]], references[i]):
                return str(expression[i]) + " does not reference a " \
                    + references[i].__name__
    return True


def requireReferences(*n):
    def dec(f):
        @wraps(f)
        def wrapper(self, *expression):
            errMsg = verifyReferences(self, expression, n)
            if not (errMsg == True):
                return errMsg
            return f(self, *expression)
        return wrapper
    return dec
