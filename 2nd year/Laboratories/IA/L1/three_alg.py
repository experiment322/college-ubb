def bfs(tree, start):
    marked = []
    queue = [s]
    while len(queue) > 0:
        n = queue.pop(0)
        if (n in tree):
            queue += tree[n]
        marked.append(n)
    return marked

def dfs(tree, s):
    marked = []
    stack = [s]
    while len(stack) > 0:
        n = stack.pop()
        if (n in tree):
            stack += tree[n]
        marked.append(n)
    return marked
