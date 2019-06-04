""" 
    The original function will print the final value of i (3) three times
    This is because i in the local function in make_functions is actually a reference
    to the nonlocal i variable in make_functions.
"""

def make_functions():
    flist = []
    
    for i in [ 1, 2, 3 ]:
        def print_i():
            print(i)
            
        flist.append(print_i)
        
    return flist
    
"""
    A simple way to fix this is to add a parameter called i to the local print_i function.
    This will create a new variable called i (that shadows the i in the outer function) that
    will have the value of the nonlocal i, but won't refer to it. The parameter will have a
    default value of the nonlocal i, meaning that the function doesn't need to be passed any
    parameters and will function as intended.
"""

def make_functions_fixed():
    flist = []
    
    for i in [ 1, 2, 3 ]:
        def print_i(i = i):
            print(i)
            
        flist.append(print_i)
        
    return flist
    
functions = make_functions()
fixed_functions = make_functions_fixed()

for f in functions:
    f()
    
for f in fixed_functions:
    f()