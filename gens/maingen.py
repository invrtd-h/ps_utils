import sys
import random as r
from tcgen import random_fmt
from treegen import tree_gen

if __name__ == '__main__':
    n = 10
    f = open("../input.txt", "r")
    s = f.read()
    f.close()

    sys.stdout = open("../input.txt", "w")
    print(s)

    for i in range(100):
        print('*')
        print(n)
        print(*(r.randint(1, n * 2) for _ in range(n)))
        tree_gen(n)