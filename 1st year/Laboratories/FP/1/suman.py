n = 0

try:
    n = int(input('N = '))
except (EOFError, ValueError):
    print('Invalid input')

try:
    s = 0
    for i in range(n):
        msg = 'L[' + str(i + 1) + '] = '
        x = int(input(msg))
        s = s + x

    print('SUM = ' + str(s))

except (EOFError, ValueError):
    print('Invalid input')
