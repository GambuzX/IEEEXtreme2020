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
# import scipy

class Student:
    def __init__(self):
        self.bffs = []
        self.bff_pos = 1
    def set_pos(self, x: int):
        self.pos = x
    def add_bff(self, stu: Student):
        self.bffs.append(stu)
        self.opp_pos = stu.pos
    

class Classroom:
    def __init__(self):
        stu = Student()
        stu.set_pos(0)
        self.students = [stu]
        self.count = 1

    def addStudent(self, bff: int):
        self.count += 1
        stu = Student()
        self.students.append(stu)
        self.students[bff-1].add_bff(stu)
    

N = get_number()
cr = Classroom()
for _ in range(N-1):
    bff = get_number()
    cr.addStudent(bff)

for s in cr.students:
    print(s, s.bffs)

# dists = [[] for _ in range(N)]

# for key in classroom:
#     bffs = classroom[key]
#     if len(bffs) < 3:
#         dists[key][bffs[0]] = 1
#         dists[key][bffs[1]] = 1
#         dists[bffs[0]][bffs[1]] = 2
#     else:
#         for i in range(len(bffs)//2):



# total = 0
# for n in dists:
#     for m in n:
#         total += m
# print(total)