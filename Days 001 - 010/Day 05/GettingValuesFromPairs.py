def cons(a, b):
    def pair(f):
        return f(a, b);
    
    return pair;
    
def car(pair):
    def first_var(a, b):
        return a;
        
    return pair(first_var);
    
def cdr(pair):
    def second_var(a, b):
        return b;
        
    return pair(second_var);
    
print(car(cons(3, 4)));
print(cdr(cons(3, 4)));