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


def consistent(x, v):
    return len(x) == len(v) - 1


def solution(x, v):
    s = v[0]
    for i in range(len(x)):
        if x[i] == 0:
            s -= v[i + 1]
        else:
            s += v[i + 1]
    return s >= 0


def iterative(numbers):
    pass
    # stack = []
    # num_len = len(numbers)
    # for i in range(num_len):
    #     stack.append(0)
    #     if consistent(stack, numbers):
    #         if solution(stack, numbers)


def backtrack(numbers, ops, op):
    ops.append(op)
    if consistent(ops, numbers):
        if solution(ops, numbers):
            print(*['-' if o == 0 else '+' for o in ops])
    else:
        backtrack(numbers, ops, 0)
        backtrack(numbers, ops, 1)
    ops.pop()


def main():
    method, numbers = read()
    if method == "iterative":
        iterative(numbers)
    if method == "recursive":
        backtrack(numbers, [], 0)
        backtrack(numbers, [], 1)


if __name__ == '__main__':
    main()
