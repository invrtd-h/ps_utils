import random as r

def tree_gen(n):
    lis = [r.randint(0, i) for i in range(n - 1)]
    for i in range(n - 1):
        print(i + 2, lis[i] + 1)


if __name__ == '__main__':
    tree_gen(10)