def song_ui(controller):
    commands = {
        "add": (4, controller.add_song),
        "mod": (4, controller.mod_song),
        "generate": (1, controller.generate_songs),
        "export": (1, controller.export_songs)
    }
    while True:
        cmd = input("COMMAND > ")
        if cmd == "quit":
            break
        if cmd == "?":
            print(*commands.keys())
            continue
        if cmd in commands:
            dto = ""
            command_args = commands[cmd][0]
            command_controller = commands[cmd][1]
            for i in range(command_args):
                dto += input("ARG({}) > ".format(i))
                if i < command_args - 1:
                    dto += ","
            try:
                command_controller(dto)
            except ValueError as err:
                print("ERROR: {}".format(err))
        else:
            print("Invalid command")
