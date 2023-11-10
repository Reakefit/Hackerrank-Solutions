def find(i, parent):
    if i != parent[i]:
        parent[i] = find(parent[i], parent)
    return parent[i]

def union(i, j, parent, size):
    i_id = find(i, parent)
    j_id = find(j, parent)
    if i_id != j_id:
        if size[i_id] > size[j_id]:
            parent[j_id] = i_id
            size[i_id] += size[j_id]
        else:
            parent[i_id] = j_id
            size[j_id] += size[i_id]

n, q = map(int, input().split())
parent = list(range(n+1))
size = [1]*(n+1)
for _ in range(q):
    query = input().split()
    if query[0] == 'M':
        union(int(query[1]), int(query[2]), parent, size)
    else:
        print(size[find(int(query[1]), parent)])
            
