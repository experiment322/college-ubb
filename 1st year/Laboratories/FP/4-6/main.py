"""Main module - P1 Numbers"""


import track
import console
import drivers


def start_ui():
    """
    > Start the main program loop.
    """
    options = {
        # Feature group 1
        "Append complex number at the end of the list":
            drivers.append_complex_number_to_list,
        "Insert complex number at index":
            drivers.insert_complex_number_at_index,
        # Feature group 2
        "Remove complex number at index":
            drivers.remove_complex_number_at_index,
        "Remove complex numbers between indexes(inclusive)":
            drivers.remove_complex_numbers_sequence,
        "Replace complex number with another complex number":
            drivers.replace_complex_number,
        # Feature group 3
        "Print imaginary part of complex numbers between indexes(inclusive)":
            drivers.print_imaginary_parts,
        "Print all complex numbers with absolute value less than 10":
            drivers.print_absolute_less_than_ten,
        "Print all complex numbers with absolute value equal with 10":
            drivers.print_absolute_equal_with_ten,
        # Feature group 4
        "Print sum of complex numbers between indexes(inclusive)":
            drivers.print_complex_numbers_sum,
        "Print product of complex numbers between indexes(inclusive)":
            drivers.print_complex_numbers_product,
        "Print all complex numbers in descending order by imaginary part":
            drivers.print_reverse_sorted_by_j,
        # Feature group 5
        "Remove all complex numbers where the real part is prime":
            drivers.filter_real_part_not_prime,
        "Remove all complex numbers by relation with given absolute value":
            drivers.filter_by_absolute_relation,
        # Feature group 6
        "Undo last operation":
            drivers.undo_list_track,
        # Quit
        "Quit":
            exit_ui
    }
    options_texts = list(options.keys())
    options_handlers = list(options.values())
    complex_number_list = track.create(2, [])
    while True:
        print("NUMBERS: ", track.peek(complex_number_list))
        try:
            option_index = console.input_option(options_texts)
            option_handler = options_handlers[option_index]
            option_handler(console, complex_number_list)
        except (EOFError, IndexError, ValueError):
            print("INVALID INPUT.")
        print()


def exit_ui(_console, _data):
    """
    > Exit the main program loop.
    """
    exit()


start_ui()
