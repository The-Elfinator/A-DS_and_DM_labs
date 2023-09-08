def in_3(x):
    if x == 0:
        return 0
    s = ''
    while x > 0:
        c = x % 3
        s = str(c) + s
        x = x // 3
    return s


for x in range(1, 40):
    print(x, end='\t')
    print(in_3(x), end='\t')
    print(bin(x)[2:])
