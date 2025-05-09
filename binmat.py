from collections import deque

def in_border(x, y, n, m):
    return x == 0 or y == 0 or x == n-1 or y == m-1

def read_input(filename):
    with open(filename, 'r') as f:
        n, m = map(int, f.readline().split())
        mat = [list(map(int, list(f.readline().strip()))) for _ in range(n)]
    return n, m, mat

def write_output(filename, result):
    with open(filename, 'w') as f:
        f.write(str(result))

def solve(n, m, mat):
    visited = [[False]*m for _ in range(n)]
    id_map = [[-1]*m for _ in range(n)]
    regions = []
    
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]
    
    # Step 1: Flood fill to find all zero-regions
    region_id = 0
    for i in range(n):
        for j in range(m):
            if mat[i][j] == 0 and not visited[i][j]:
                q = deque()
                q.append((i, j))
                visited[i][j] = True
                id_map[i][j] = region_id
                size = 1
                border = in_border(i, j, n, m)
                cells = [(i, j)]
                
                while q:
                    x, y = q.popleft()
                    for d in range(4):
                        nx, ny = x + dx[d], y + dy[d]
                        if 0 <= nx < n and 0 <= ny < m:
                            if mat[nx][ny] == 0 and not visited[nx][ny]:
                                visited[nx][ny] = True
                                id_map[nx][ny] = region_id
                                q.append((nx, ny))
                                size += 1
                                border |= in_border(nx, ny, n, m)
                                cells.append((nx, ny))
                regions.append({
                    'size': size,
                    'border': border,
                    'cells': cells
                })
                region_id += 1

    # Step 2: Find the unique border-connected region (gốc)
    for rid, region in enumerate(regions):
        if region['border']:
            border_id = rid
            break
    
    max_ones = 0
    current_ones = sum(mat[i][j] for i in range(n) for j in range(m))

    # Step 3: Try choosing each cell in the border region to flip
    for x, y in regions[border_id]['cells']:
        connected = set()
        for d in range(4):
            nx, ny = x + dx[d], y + dy[d]
            if 0 <= nx < n and 0 <= ny < m and mat[nx][ny] == 0:
                nid = id_map[nx][ny]
                if nid != border_id and not regions[nid]['border']:
                    connected.add(nid)
        total = regions[border_id]['size'] + sum(regions[rid]['size'] for rid in connected)
        max_ones = max(max_ones, total)

    return current_ones + max_ones

n, m, mat = read_input("binmat.inp")
res = solve(n, m, mat)
write_output("BINMAT.OUT", res)
