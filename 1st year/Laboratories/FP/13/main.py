def read():
    method = input("Method(iterative/recursive): ")
    if method not in ["iterative", "recursive"]:
        raise ValueError("invalid method: " + method)

    n = int(input("N = "))
    if n <= 1:
        raise ValueError("n should be greater than 1")

    numbers = []
    for i in range(n):
        x = int(input("X({}) = ".format(i + 1)))
        numbers.append(x)

    return method, numbers


def iterative(numbers):
    num_len = len(numbers)
    for mask in range(1 << num_len - 1):
        result = numbers[0]
        for i in range(1, num_len):
            if (mask >> num_len - i - 1) & 1 == 1:
                result += numbers[i]
            else:
                result -= numbers[i]
        if result >= 0:
            bin_str = "{0:b}".format(mask).zfill(num_len - 1)
            ops_str = bin_str.replace("1", "+").replace("0", "-")
            print(ops_str, result)


def backtrack(result, numbers, ops_str):
    if len(numbers) == 0:
        if result >= 0:
            print(ops_str, result)
    else:
        backtrack(result - numbers[0], numbers[1:], ops_str + "-")
        backtrack(result + numbers[0], numbers[1:], ops_str + "+")


def main():
    method, numbers = read()
    if method == "iterative":
        iterative(numbers)
    if method == "recursive":
        backtrack(numbers[0], numbers[1:], "")


if __name__ == '__main__':
    main()
