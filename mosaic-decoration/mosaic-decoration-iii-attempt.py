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
for i in range(R):
    row = []
    for j in range(C):
        row.append(get_number())
    pattern.append(row)


def calc_price():
    total = 0
    for y in range(N):
        for x in range(M):
            total += pattern[y % R][x % C]
    return total

def calc_new_price(orig, offset_x, offset_y):
    new_price = orig
    for row in range(offset_y):
        for cell in range(offset_y):
            new_price -= pattern[row % R][cell % C]
            new_price += pattern[(N+row) % R][(M+cell) % C]
    for row in range(offset_y):
        for cell in range(offset_x, M):
            new_price -= pattern[row % R][cell % C]
            new_price += pattern[(N+row) % R][cell % C]
    for col in range(offset_x):
        for cell in range(offset_y, N):
            new_price -= pattern[cell % R][col % C]
            new_price += pattern[cell % R][(M+col) % C]
    return new_price


price = calc_price()
final = price
for y in range(R):
    for x in range(C):
        new_price = calc_new_price(price, x, y)
        if new_price < final:
            final = new_price

print(final)
