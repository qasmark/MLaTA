segments = {}
f = open("input4.txt", 'r')
line = f.readline()
m, n = map(int, line.split())
for i in range(m):
    line = f.readline()
    par = line.strip().split()
    a, b = map(int, line.split())
    for j in range(a, b+1):
        if j not in segments:
            segments[j] = 1
        else:
            segments[j] += 1
repair_segments = [seg for seg in segments if segments[seg] >= n]
groups = []
for seg in repair_segments:
    if not groups:
        groups.append([seg])
    elif seg == groups[-1][-1] + 1:
        groups[-1].append(seg)
    else:
        groups.append([seg])
print(len(groups) - 1)
f.close()
