import random as r

def tree_gen(n):
    lis = [r.randint(0, i) for i in range(n - 1)]
    for i in range(n - 1):
        print(i + 2, lis[i] + 1)


def path_gen(n):
    for i in range(n - 1):
        print(i + 1, i + 2)


def star_gen(n):
    for i in range(n - 1):
        print(1, i + 2)


if __name__ == '__main__':
    tree_gen(10)