for i in range(10):
    print(f(i))

def f(x):
    if x==0:
        return 0
    return f(x-1)+1