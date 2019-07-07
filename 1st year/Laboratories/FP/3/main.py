def start_ui():
    """
    Start the main program loop.
    :return: None
    """
    options = {
        "Read number sequence": input_number_sequence,
        "Find longest sequence with max sum": find_longest_sequence_with_max_sum,
        "Find longest sequence with sum five": find_longest_sequence_with_sum_five,
        "Quit": exit_ui
    }
    options_texts = list(options.keys())
    options_handlers = list(options.values())
    number_list = []
    while True:
        print("NUMBERS: ", number_list)
        option_index = input_option(options_texts)
        if option_index is not None:
            option_handler = options_handlers[option_index]
            option_handler(number_list)
        print()


def input_option(options):
    """
    Print options along with their index and return the selected one.
    :param options: list of strings to be presented as options along with their index
    :return: a number representing the chosen option or None if input was not a valid index
    """
    options_range = range(len(options))
    for index in options_range:
        print(index, options[index])
    try:
        inp = input("OPTION: ")
        num = int(inp)
        if num not in options_range:
            raise IndexError
        return num
    except (EOFError, ValueError, IndexError):
        print("INVALID OPTION.")


def input_number_sequence(data):
    """
    Read a list of numbers separated by commas and save them in data.
    :param data: an array in which the read number sequence is stored;
    remains untouched if input is invalid
    :return: None
    """
    try:
        raw_inp = input("INPUT NUMBERS: ")
        stripped_inp = "".join(raw_inp.split())  # remove whitespaces
        partitioned_inp = stripped_inp.split(",")  # split the stripped input by commas
        number_sequence = []
        for number_str in partitioned_inp:
            number_sequence.append(int(number_str))
        data.clear()  # clear the old list
        data.extend(number_sequence)  # fill the list with the read numbers
    except (EOFError, ValueError):
        print("INVALID INPUT.")


def find_longest_sequence_with_max_sum(data):
    """
    Given a list return the longest sequence which has maximum sum.
    :param data: a list of integers
    :return: a list of integers
    """
    data_len = len(data)
    sequence = data[0:1]  # consider the first number in data the longest sequence
    for i in range(data_len):
        for j in range(i, data_len):
            sub_data = data[i:j + 1]
            if sum(sub_data) > sum(sequence)\
                    or sum(sub_data) == sum(sequence) and len(sub_data) > len(sequence):
                sequence = sub_data
    print("SEQUENCE: ", sequence)
    return sequence


def find_longest_sequence_with_sum_five(data):
    """
    Given a list return the longest sequence which has sum five.
    :param data: a list of integers
    :return: a list of integers
    """
    data_len = len(data)
    sequence = []
    for i in range(data_len):
        for j in range(i, data_len):
            sub_data = data[i:j + 1]
            if sum(sub_data) == 5 and len(sub_data) > len(sequence):
                sequence = sub_data
    print("SEQUENCE: ", sequence)
    return sequence


def exit_ui(_data):
    """
    Leave the main program loop.
    :return: None
    """
    exit()


start_ui()
