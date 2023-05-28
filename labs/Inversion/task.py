from random import randint, shuffle
size = randint(5, 500000)
lst = [i for i in range(1, size)]
shuffle(lst)

with open('cin5.txt', 'w') as f:
    f.write(str(size) + '\n')
    f.write(' '.join(map(str, lst)))
