K, N = map(int, input().split())
timeOfWaiting = list(map(int, input().split()))

summaryTime = 10 ** 6
minTime = 0

for t in range(K):
    tempSummaryTime = 0
    for i in range(N):
        waitTime = (t - timeOfWaiting[i] % K + K) % K
        tempSummaryTime += waitTime

    if tempSummaryTime < summaryTime:
        summaryTime = tempSummaryTime
        minTime = t

print(minTime)