"""
The code will print 9 ten times because of the way Python's closures work.
The i captured in the lambda actually refers to the i in the enviroment it's in, it isn't copied by value.
In order to get the desired behaviour, the value needs to be copied rather than taken by reference.
This is done by adding i = i after the lambda keyword.
"""

# Original snippet
functions = [];

for i in range(10):
    functions.append(lambda: i);
    
for f in functions:
    print(f());
    
print("\n");
    
# Desired outcome
functions = [];

for i in range(10):
    functions.append(lambda i = i: i);
    
for f in functions:
    print(f());