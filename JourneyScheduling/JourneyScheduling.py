from collections import defaultdict
import os

def dfs(node, graph, visited, dist, distances):
    visited[node] = True
    distances[node] = dist
    maxDistance = dist
    maxNode = node
    for neighbour in graph[node]:
        if not visited[neighbour]:
            newDist, newNode = dfs(neighbour, graph, visited, dist + 1, distances)
            if newDist > maxDistance:
                maxDistance = newDist
                maxNode = newNode
    return maxDistance, maxNode

def treeDiameterAndNodes(n, graph):
    visited = [False] * (n + 1)
    distances = [0] * (n + 1)
    _, farthestNode = dfs(1, graph, visited, 0, distances)

    visited = [False] * (n + 1)
    diameter, diameterNode = dfs(farthestNode, graph, visited, 0, distances)
    return diameter, farthestNode, diameterNode

def findDistanceToDiameterNodes(n, graph, diameterNode1, diameterNode2):
    visited = [False] * (n + 1)
    dist1 = [0] * (n + 1)
    dfs(diameterNode1, graph, visited, 0, dist1)

    visited = [False] * (n + 1)
    dist2 = [0] * (n + 1)
    dfs(diameterNode2, graph, visited, 0, dist2)

    return dist1, dist2

def journeyScheduling(n, graph, queries):
    diameter, diameterNode1, diameterNode2 = treeDiameterAndNodes(n, graph)
    dist1, dist2 = findDistanceToDiameterNodes(n, graph, diameterNode1, diameterNode2)
    answer = []
    for (start, k) in queries:
        if k == 1:
            answer.append(max(dist1[start], dist2[start]))
        else:
            answer.append(max(dist1[start], dist2[start]) + (k - 1) * diameter)
    return answer

if __name__ == "__main__":
    n, m = 8, 2

    graph = defaultdict(list)
    for u, v in [(1, 2), (2, 3), (2, 4), (1, 5), (1, 6), (1, 7), (7, 8)]:
        graph[u].append(v)
        graph[v].append(u)
    queries = [(4, 6), (6, 3), (7, 6), (4, 6), (7, 1), (2, 6)]
    print(journeyScheduling(n, graph, queries))