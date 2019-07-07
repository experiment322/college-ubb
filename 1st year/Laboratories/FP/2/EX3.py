from datetime import date, timedelta

def input_custom_date():
    '''
        Description:
            Read a date from standard input composed from two integers Y and D
            which represent the year and the day number and return it. Try to
            read until a valid date is given or quit the script by pressing
            [CTRL] + [C].

        Parameters:
            none

        Returns:
            A tuple containing the day and year in this order
    '''
    days = None
    year = None
    while True:
        try:
            days = int(input('Days = '))
            year = int(input('Year = '))
            first_day = date(year, 1, 1)
            last_day = date(year, 12, 31)
            max_days = (last_day - first_day + timedelta(1)).days
            if days not in range(1, max_days + 1):
                raise ValueError
        except KeyboardInterrupt:
            print()
            raise SystemExit # Quits the script
        except (ValueError, EOFError):
            print('Error... Try again or press [CTRL] + [C] to quit.')
        else:
            return (days - 1, year)

def form_date(days, year):
    '''
        Description:
            Calculate the date by adding the days to the given year.

        Parameters:
            days - an integer
            year - an integer between date.min and date.max year

        Returns:
            A date
    '''
    return date(year, 1, 1) + timedelta(days)

def run():
    days, year = input_custom_date()
    formed_date = form_date(days, year)
    print('Date = ' + formed_date.strftime('%d/%m/%Y'))

run()

