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


# ################################

N = get_number()    # rows of cells in the wall
M = get_number()    # columns of cells in the wall
R = get_number()    # rows of cells in the pattern
C = get_number()    # columns of cells in the pattern

pattern = []
lowest_spot = [-1, -1]
lowest_price = -1
for i in range(R):
    row = []
    for j in range(C):
        price = get_number()
        row.append(price)
        if price < lowest_price or lowest_price == -1:
            lowest_price = price
            lowest_spot = [i, j]
    pattern.append(row)


def calc_price(x_off, y_off):
    total = 0
    for i in range(N):
        for j in range(M):
            total += pattern[(x_off + i) % R][(y_off + j) % C]
    return total

final = 0
for i in range(R):
    for j in range(C):
        price = calc_price(i, j)
        if price < final or not final:
            final = price

print(final)
