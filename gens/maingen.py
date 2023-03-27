import sys
import random as r
from tcgen import random_fmt
from treegen import tree_gen, path_gen, star_gen

if __name__ == '__main__':
    n = 50000
    t = 1

    f = open("../input.txt", "r")
    s = f.read()
    f.close()

    s = s.split('#')

    sys.stdout = open("../input.txt", "w")
    print(s[0], end='')

    for i in range(t):
        print('#')
        print(n)
        print(*(r.randint(1, n * 2) for _ in range(n)))
        tree_gen(n)