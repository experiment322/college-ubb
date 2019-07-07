def bubble_sort(array, key):
    v = array[:]
    ok = True
    while ok:
        ok = False
        for i in range(0, len(v) - 1):
            if key(v[i]) > key(v[i + 1]):
                ok = True
                v[i], v[i + 1] = v[i + 1], v[i]
    return v


def shell_sort(array, key):
    v = array[:]
    g = len(v) // 2
    while g > 0:
        for i in range(g, len(v)):
            t = v[i]
            j = i
            while j >= g and key(v[j - g]) > key(t):
                v[j] = v[j - g]
                j -= g
            v[j] = t
        g //= 2
    return v


def sorted_custom(array, method, *, key=lambda item: item, reverse=False):
    sort = {"bubble": bubble_sort, "shell": shell_sort}
    result = sort[method](array, key)
    if reverse is True:
        result.reverse()
    return result
