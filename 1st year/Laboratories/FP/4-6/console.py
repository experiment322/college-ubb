"""Module containing common console functions"""


def input_option(options, prompt="OPTION: "):
    """
    > Read and return an option number.
    * `options` list of strings to be presented as options along with their index
    * `prompt` text to display as input prompt
    * :return: a number representing the chosen option
    * *raises* EOFError, ValueError, IndexError
    """
    options_range = range(len(options))
    for index in options_range:
        print(index, options[index])
    option = int(input(prompt))
    if option not in options_range:
        raise IndexError
    return option


def input_complex(prompt="COMPLEX NUMBER: "):
    """
    > Read and return a complex number.
    * `prompt` text to display as input prompt
    * :return: a complex number
    * *raises* EOFError, ValueError
    """
    complex_number = complex(input(prompt))
    return complex_number


def input_integer(prompt="INTEGER: "):
    """
    > Read and return an integer.
    * `prompt` text to display as input prompt
    * :return: an integer
    * *raises* EOFError, ValueError
    """
    integer = int(input(prompt))
    return integer


def print_object(obj, text=""):
    """
    > Print obj with additional leading text.
    * `obj` any object
    * `text` string
    """
    print(text, obj)
