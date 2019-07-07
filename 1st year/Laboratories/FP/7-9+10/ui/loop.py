from inspect import signature
from domain.dto import DTO


def loop_ui(title, commands, screen_width=80, fill_char='='):
    while True:
        print()
        print("".center(screen_width, fill_char))
        print(title.center(screen_width, fill_char))
        print("".center(screen_width, fill_char))
        print("AVAILABLE COMMANDS:", "quit", *commands.keys(), sep="\n> ")
        command = input("CMD >>> ")
        if command in commands:
            arguments = []
            argument_count = len(signature(commands[command]).parameters)
            for i in range(argument_count):
                dto = DTO(input("ARG({}) >>> ".format(i)))
                arguments.append(dto)
            try:
                commands[command](*arguments)
            except (LookupError, PermissionError, ValueError) as err:
                print(err)
        elif command == "quit":
            break
        else:
            print("There is no such command")
