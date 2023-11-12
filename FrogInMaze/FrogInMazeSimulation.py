import random
from functools import lru_cache
from multiprocessing import Pool
import sys

sys.setrecursionlimit(10**6)

@lru_cache(maxsize=400)
def isValid(x, y):
    return 0 <= x < n and 0 <= y < m and maze[x][y] != '#'

def simulate(start, maxSteps=100):
    steps = 0
    x, y = start
    while steps < maxSteps:
        if maze[x][y] == '%':
            return 1
        if maze[x][y] == '*':
            return 0
        if (x, y) in tunnel:
            x, y = tunnel[(x, y)]
        
        validMoves = [move for move in moves if isValid(x + move[0], y + move[1])]
        if not validMoves:
            return 0

        dx, dy = random.choice(validMoves)
        x, y = x + dx, y + dy
        steps += 1
    return None

def evaluateSimulations(start, numSimulations=1000000):
    success = 0
    total = 0
    while total < numSimulations:
        result = simulate(start)
        if result is not None:
            success += result
            total += 1
    return success / total

n, m, k = map(int, input().split())
maze = [list(input()) for _ in range(n)]
tunnel = {}
for _ in range(k):
    x1, y1, x2, y2 = map(int, input().split())
    tunnel[(x1-1, y1-1)] = (x2-1, y2-1)
    tunnel[(x2-1, y2-1)] = (x1-1, y1-1)
moves = [(1, 0), (-1, 0), (0, 1), (0, -1)]

for i, x in enumerate(maze):
    for j, y in enumerate(x):
        if y == 'A':
            start = (i, j)

print(evaluateSimulations(start))
