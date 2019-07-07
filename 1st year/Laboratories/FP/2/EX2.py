from datetime import date, datetime

def input_birthdate():
    '''
        Description:
            Read a birthdate from standard input having the format DD/MM/YYYY
            and return it. Try to read until a valid date is given or quit the
            script by pressing [CTRL] + [C].

        Parameters:
            none

        Returns:
            A date object
    '''
    bdate = None
    while True:
        try:
            bdate = datetime.strptime(input('Birthdate = '), '%d/%m/%Y').date()
            if bdate >= date.today():
                raise ValueError
        except KeyboardInterrupt:
            print()
            raise SystemExit # Quits the script
        except (ValueError, EOFError):
            print('Error... Try again or press [CTRL] + [C] to quit.')
        else:
            return bdate

def get_age(tdate):
    '''
        Description:
            Calculate the age in days from the tdate.

        Parameters:
            tdate - a date object

        Returns:
            An integer
    '''
    return (date.today() - tdate).days

def run():
    birthdate = input_birthdate()
    age = get_age(birthdate)
    print('Age(days) = ' + str(age))

run()

