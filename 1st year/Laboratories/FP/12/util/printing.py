def print_table(data, screen_width=80, sep="~"):
    if len(data) == 0:
        print("There is nothing to print")
    else:
        hr = screen_width * sep
        heads = data[0].keys()
        lines = [item.values() for item in data]
        col_width = screen_width // len(heads)
        last_col_width = col_width + screen_width % len(heads)

        def format_column(string, i):
            width = col_width if i < len(heads) else last_col_width
            return sep + string[:width - 2].center(width - 2) + sep

        print(hr)
        print(*[format_column(head, i) for i, head in enumerate(heads, 1)], sep="")
        print(hr)
        for line in lines:
            print(*[format_column(item, i) for i, item in enumerate(line, 1)], sep="")
            print(hr)
