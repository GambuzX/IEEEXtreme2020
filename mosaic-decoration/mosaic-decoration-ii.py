# a simple parser for python. use get_number() and get_word() to read
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
import numpy
import math

W = get_number()    # width of wall in inches
H = get_number()    # height of wall in inches
A = get_number()    # witdh of tile in inches
B = get_number()    # height of tile in inches
M = get_number()    # price of 10 tiles
C = get_number()    # price per inch of cut

inches_of_cut = 0

tiles_per_row = math.ceil(W/A)
if W % A: inches_of_cut += H
tiles_per_col = math.ceil(H/B)
if H % B: inches_of_cut += W

num_tiles = tiles_per_col * tiles_per_row
num_purchases = math.ceil(num_tiles/10)

output = num_purchases * M + inches_of_cut * C

print(output)
