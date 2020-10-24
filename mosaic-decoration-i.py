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
import scipy
import math

N = get_number()
Cb = get_number()
Cp = get_number()
totalB = 0
totalP = 0

for _ in range(N):
    totalB += get_number()
    totalP += get_number()

result = Cb * math.ceil(totalB/10) + Cp * math.ceil(totalP/10)
print(result)
