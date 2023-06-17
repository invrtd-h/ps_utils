import sys
import random as r
from tcgen import random_fmt
from treegen import tree_gen, path_gen, star_gen


def main_print():
    print(1000)
    for _ in range(1000):
        print(2**58, end=' ')


if __name__ == '__main__':
    test_case_num = 1

    f = open("../src/input.txt", "r")
    s = f.read()
    f.close()

    s = s.split('#')

    sys.stdout = open("../src/input.txt", "w")
    print(s[0], end='')
    if not s[0].endswith('\n'):
        print("")

    for i in range(test_case_num):
        print('#')
        main_print()