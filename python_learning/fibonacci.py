# fibonacci.py
# Ryan Jensen
# 2018-12-31
"""Provides a function to generate Fibonacci numbers."""
def gen(n):
    """generate, print, and return the first n terms of the Fibonacci series."""
    
    minimum = 1
    if n < minimum:
        print("n cannot be less than", minimum)
        return 0
    
    if not( (type(n) is int) or (type(n) is float) ):
        print("input number must be a number!")
        return 0
    
    if int(n) != n:
        print("input number must be an integer")
        return 0
    
    a,b = 0,1
    list = []
    for i in range(n):
        a,b = b,b+a
        list.append(a)
    
    return list
#