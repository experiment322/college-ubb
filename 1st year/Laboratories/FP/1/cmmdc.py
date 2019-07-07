def gcd(a, b):
    if a > b:
        return gcd(a - b, b)
    if a < b:
        return gcd(a, b - a)
    if a == b:
        return a

try:
    a = int(input('A = '))
    b = int(input('B = '))
    print(gcd(a,b))
except (EOFError, ValueError):
    print('Invalid input')
