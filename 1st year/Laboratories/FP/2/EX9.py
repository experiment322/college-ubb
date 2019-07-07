def input_natural_number():
    '''
        Description:
            Read a natural number from standard input and return it. Try to
            read until a valid number is given or quit the script by pressing
            [CTRL] + [C].

        Parameters:
            none

        Returns:
            A natural number
    '''
    n = None
    while True:
        try:
            n = int(input('N = '))
            if n < 0:
                raise ValueError
        except KeyboardInterrupt:
            print()
            raise SystemExit # Quits the script
        except (ValueError, EOFError):
            print('Error... Try again or press [CTRL] + [C] to quit.')
        else:
            return n

def form_palindrome(n):
    '''
        Description:
            Form the palindrome of n and return it.

        Parameters:
            n - natural number

        Returns:
            A natural number
    '''
    return int(str(n)[::-1])

def run():
    n = input_natural_number()
    p = form_palindrome(n)
    print('P = ' + str(p))

run()

