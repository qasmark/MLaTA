from random import randint

with open('input.txt', 'w') as f:
    comets = randint(2, 100000)
    time = randint(1, 1000)
    
    temp = str(comets) + ' ' + str(time) + '\n'
    f.write(temp)
    
    for i in range(comets):
        A = randint(-100, 100)
        B = randint(-100, 100)
        temp = str(A) + ' ' + str(B) + '\n'
        f.write(temp)
