def isPrime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    for i in range(2, n // 2):
        if n % i == 0:
            return False
    return True

try:
    n = int(input('N = '))
    if isPrime(n):
        print('Prime')
    else:
        print('Not prime')
except (EOFError, ValueError):
    print('Invalid input')
