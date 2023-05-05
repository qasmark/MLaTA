with open("INPUT.TXT", "r") as f:
    x, y = map(int, f.readline().split())

dp = [[0] * (x+1) for _ in range(y+1)]
dp[0][x] = 1

for i in range(1, y+1):
    for j in range(1, x+1):
        dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1] if 1 <= j-1 <= x else dp[i-1][j+1]

result = sum(dp[y])
with open("OUTPUT.TXT", "w") as f:
    f.write(str(result))
