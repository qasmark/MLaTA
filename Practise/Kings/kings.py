def check_win(x, y):
    if x % 2 and y % 2:
        return 2
    else:
        return 1

answers = []
M = int(input())
for i in range(M):
    x, y = map(int, input().split())
    answers.append(check_win(x, y))

for answer in answers:
    print(answer)
