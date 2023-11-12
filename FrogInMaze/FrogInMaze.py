from collections import defaultdict

def isValid(x, y):
    return 0 <= x < n and 0 <= y < m

n, m, k = map(int, input().split())
maze = [list(input()) for _ in range(n)]
tunnel = {}
for _ in range(k):
    x1, y1, x2, y2 = map(int, input().split())
    tunnel[(x1-1, y1-1)] = (x2-1, y2-1)
    tunnel[(x2-1, y2-1)] = (x1-1, y1-1)

# MDP Variables
states = defaultdict()
states[0] = (-1, 1)
state = 1

for i, x in enumerate(maze):
    for j, y in enumerate(x):
        if y in '%AO':
            states[(i, j)] = state
            state += 1
            if y == 'A':
                startState = state - 1

probabilities = [0.0]
t = [[(0, 1.0)]]

for i, x in enumerate(maze):
    for j, y in enumerate(x):
        if y in '#*':
            continue
        elif y == '%':
            probabilities.append(1.0)
            t.append([(states[(i, j)], 1.0)])
        else:
            probabilities.append(0.0)
            if (i, j) in tunnel:
                ni, nj = tunnel[(i, j)]
            else:
                ni, nj = i, j
            success, fail = [], 0
            for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                if isValid(ni + dx, nj + dy):
                    if maze[ni + dx][nj + dy] in 'AO%':
                        success.append((ni + dx, nj + dy))
                    elif maze[ni + dx][nj + dy] == '*': fail += 1
            if not success:
                t.append([(0, 1.0)])
            else:
                temp = []
                for s in success:
                    temp.append((states[s], 1/(len(success) + fail)))
                if fail > 0:
                    temp.append((0, fail/(len(success) + fail)))
                t.append(temp)

minDifference = 10**-10
minDifferenceReached = False

while not minDifferenceReached:
    prob = probabilities.copy()
    for s in range(state):
        probState = 0
        for a, b in t[s]:
            probState += probabilities[a] * b
        probabilities[s] = probState
    minDifferenceReached = True
    for s in range(state):
        if abs(probabilities[s] - prob[s]) > minDifference:
            minDifferenceReached = False
            break

print(probabilities[startState])   

'''
3 6 1
###*OO
O#OA%O
###*OO
2 3 2 1
'''

'''
3 7 0
##OOO##
%OOAOO*
##OOO##
'''

'''
3 5 0
OO#OO
AO#O%
OO#OO
'''
