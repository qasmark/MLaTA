n = int(input())
maze = []
for i in range(n):
    row = input().strip()
    maze.append(row)

wall_area = 3 * 3  # 3 meters high by 3 meters wide
visible_area = 0
for i in range(1, n - 1):
    for j in range(1, n - 1):
        if maze[i][j] == '#':  # wall is present
            visible_area += 4 * wall_area
            if maze[i-1][j] == '#':
                visible_area -= wall_area  # top wall is adjacent
            if maze[i+1][j] == '#':
                visible_area -= wall_area  # bottom wall is adjacent
            if maze[i][j-1] == '#':
                visible_area -= wall_area  # left wall is adjacent
            if maze[i][j+1] == '#':
                visible_area -= wall_area  # right wall is adjacent

print(visible_area, 'sq.m.')
