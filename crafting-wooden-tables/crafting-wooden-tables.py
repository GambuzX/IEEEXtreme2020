# a simple parser for python. use get_number() and get_word() to read
import numpy


def parser():
    while 1:
        data = list(input().split(' '))
        for number in data:
            if len(number) > 0:
                yield(number)


input_parser = parser()


def get_word():
    global input_parser
    return next(input_parser)


def get_number():
    data = get_word()
    try:
        return int(data)
    except ValueError:
        return float(data)


# numpy and scipy are available for use
# import scipy
from math import ceil

C = get_number()    # pieces of wood to build a table
N = get_number()    # slots in Rolan's pocket
P = get_number()    # pieces of wood in a pile
W = get_number()    # pieces of wood at the beginning

# How many tables can Rolan build?
max_tables = W // C

def can_fit_leftover_wood_in_pockets():
    return N - tables >= ceil(leftover / P)

tables = max_tables
leftover = W % C

while not can_fit_leftover_wood_in_pockets() and tables:
    tables -= 1
    leftover += C

print(tables)
