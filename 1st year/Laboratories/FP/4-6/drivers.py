"""Module containing driver functions for controllers"""


import controllers


def append_complex_number_to_list(console, list_track):
    """
    Read a complex number from console and append it to the list.
    """
    item = console.input_complex()
    controllers.append_complex_number_to_list(list_track, item)


def insert_complex_number_at_index(console, list_track):
    """
    Read a complex number from console, read an index from console and
    append the number to the list before the read index.
    """
    item = console.input_complex()
    index = console.input_integer("INDEX: ")
    controllers.insert_complex_number_at_index(list_track, item, index)


def remove_complex_number_at_index(console, list_track):
    """
    Read an index from console and remove the number at specified index.
    IndexError is raised if index is out of bounds.
    """
    index = console.input_integer("INDEX: ")
    controllers.remove_complex_number_at_index(list_track, index)


def remove_complex_numbers_sequence(console, list_track):
    """
    Read two indexes from console and remove the numbers from the first index to the second one.
    """
    index_left = console.input_integer("INDEX L: ")
    index_right = console.input_integer("INDEX R: ")
    controllers.remove_complex_numbers_sequence(list_track, index_left, index_right)


def replace_complex_number(console, list_track):
    """
    Read two complex numbers from console and
    replace all occurrences of the first number with the second one.
    """
    old_item = console.input_complex("OLD: ")
    new_item = console.input_complex("NEW: ")
    controllers.replace_complex_number(list_track, old_item, new_item)


def print_imaginary_parts(console, list_track):
    """
    Read two indexes from console and
    print the numbers' imaginary parts from the first index to the second one.
    """
    index_left = console.input_integer("INDEX L: ")
    index_right = console.input_integer("INDEX R: ")
    imaginary_parts = controllers.print_imaginary_parts(list_track, index_left, index_right)
    console.print_object(imaginary_parts, "IMAGINARY PARTS: ")


def print_absolute_less_than_ten(console, list_track):
    """
    Print the numbers with absolute value less than 10.
    """
    list_sequence = controllers.print_absolute_less_than_ten(list_track)
    console.print_object(list_sequence, "NUMBERS WITH ABS < 10: ")


def print_absolute_equal_with_ten(console, list_track):
    """
    Print the numbers with absolute value equal with 10.
    """
    list_sequence = controllers.print_absolute_equal_with_ten(list_track)
    console.print_object(list_sequence, "NUMBERS WITH ABS = 10: ")


def print_complex_numbers_sum(console, list_track):
    """
    Read two indexes from console and
    print the sum of numbers from the first index to the second one.
    """
    index_left = console.input_integer("INDEX L: ")
    index_right = console.input_integer("INDEX R: ")
    list_sum = controllers.print_complex_numbers_sum(list_track, index_left, index_right)
    console.print_object(list_sum, "SUM: ")


def print_complex_numbers_product(console, list_track):
    """
    Read two indexes from console and
    print the product of numbers from the first index to the second one.
    """
    index_left = console.input_integer("INDEX L: ")
    index_right = console.input_integer("INDEX R: ")
    list_product = controllers.print_complex_numbers_product(list_track, index_left, index_right)
    console.print_object(list_product, "PRODUCT: ")


def print_reverse_sorted_by_j(console, list_track):
    """
    Print the numbers sorted by the imaginary part in reverse order.
    """
    sorted_list = controllers.print_reverse_sorted_by_j(list_track)
    console.print_object(sorted_list, "SORTED LIST BY IMG: ")


def filter_real_part_not_prime(_console, list_track):
    """
    Remove the numbers with the real part prime number.
    """
    controllers.filter_real_part_not_prime(list_track)


def filter_by_absolute_relation(console, list_track):
    """
    Read two integers, the first one represents the value to compare to and
    the second one represents the relation with the first read number.
    If the second number is negative the relation is `<`,
    if it is positive the relation is `>` or if it is 0 the relation is `=`.
    Remove the numbers which satisfy the given relation with the first number.
    """
    target = console.input_integer("VALUE: ")
    relation = console.input_integer("RELATION: ")
    controllers.filter_by_absolute_relation(list_track, target, relation)


def undo_list_track(_console, list_track):
    """
    Undo the last snapshot from list_track.
    """
    controllers.undo_list_track(list_track)
