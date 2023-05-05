def find_steps_count(field, infected_cells_count):
    steps_count = 0
    while infected_cells_count < len(field) * len(field[0]):
        steps_count += 1
        for x in range(len(field)):
            for y in range(len(field[0])):
                if field[x][y] == steps_count:
                    if x > 0 and field[x-1][y] == 0:
                        field[x-1][y] = steps_count + 1
                        infected_cells_count += 1
                    if x < len(field)-1 and field[x+1][y] == 0:
                        field[x+1][y] = steps_count + 1
                        infected_cells_count += 1
                    if y > 0 and field[x][y-1] == 0:
                        field[x][y-1] = steps_count + 1
                        infected_cells_count += 1
                    if y < len(field[0])-1 and field[x][y+1] == 0:
                        field[x][y+1] = steps_count + 1
                        infected_cells_count += 1
    return steps_count


n, m = map(int, input().split())
field = [[0] * n for _ in range(n)]
for i in range(m):
    x, y = map(int, input().split())
    field[x-1][y-1] = 1
print(find_steps_count(field, m))

