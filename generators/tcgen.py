import math as m
import random as r
import re
import sys

primary_rule = re.compile(r"\{([^}{]*)}")
re_range = re.compile(r"(-?\d+)\.\.(-?\d+)")


def random_fmt(template: str):
    patterns = primary_rule.findall(template)
    for s in patterns:
        x = re_range.fullmatch(s)
        lo, hi = int(x[1]), int(x[2])
        template = template.replace('{' + s + '}', str(r.randint(lo, hi)), 1)
    return int(template)


n = 30000
t = 10000000

if __name__ == '__main__':
    sys.stdout = open("../src/output.txt", "w")
    print(n, t)
    for i in range(n):
        print(round(t * m.cos(i * 2 * m.pi / n)),
              round(t * m.sin(i * 2 * m.pi / n)),
              0, 0)
