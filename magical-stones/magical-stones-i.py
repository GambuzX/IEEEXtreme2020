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

N = get_number()
succ_states = [0]
for _ in range(N):
    succ_states.append(get_number())
Q = get_number()
K_vals = []
while Q:
    K_vals.append(get_number())
    Q -= 1

class State(object):

    def __init__(self, N):
        self.stones = list(range(1, N+1))
        self.num_stones = [0]
    
    def spell(self):
        visited = set()
        stones = tuple(self.stones.copy())
        count = 0
        while stones not in visited:
            visited.add(stones)
            new_stones = []
            for x in stones:
                new_stone = succ_states[x]
                new_stones.append(new_stone)
            stones = tuple(set(new_stones))
            count += 1
            self.num_stones.append(len(stones))

st = State(N)
st.spell()
for v in K_vals:
    if v not in st.num_stones:
        print(-1)
        continue
    for x in range(len(st.num_stones)):
        if st.num_stones[x] == v:
            print(x)
            break
