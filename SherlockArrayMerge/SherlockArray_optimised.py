from collections import deque
import time
MOD = 10**9 + 7

def arrayMerging(m):
    mod = 10**9 + 7
    q = deque()
    q.append((m[0], 1, -1, 1))

    for x in m[1:]:
        nextQ = deque()
        while q:
            subseqMax, subseqLen, prevSubseqL, ways = q.popleft()

            if x >= subseqMax:
                if prevSubseqL > subseqLen:
                    nextQ.append((x, subseqLen + 1, prevSubseqL, ways * (prevSubseqL - subseqLen) % mod))
                if prevSubseqL == -1:
                    nextQ.append((x, subseqLen + 1, -1, 1))
            nextQ.append((x, 1, subseqLen, (subseqLen * ways) % mod))

        condensedNextQ = deque()
        condensed = {}
        for item in nextQ:
            key = item[:3]
            if key in condensed:
                condensed[key] = (condensed[key] + item[3]) % mod
            else:
                condensed[key] = item[3]

        for key, combinedWays in condensed.items():
            condensedNextQ.append((*key, combinedWays))
        q = condensedNextQ
        print(q)
    return sum(ways for _, _, _, ways in q) % mod


if __name__ == '__main__':
    m = [i for i in range(1, 101)]
    
    startTime = time.time()
    print(arrayMerging(m))
    print(time.time() - startTime)

    m = [1, 3, 2, 4]
    m3 = [1, 2, 3]
    m2 = [2, 1]
    m4 = [1,2,5,3,4]
    print(arrayMerging(m))
    print(arrayMerging(m3))
    print(arrayMerging(m4))
    print(arrayMerging(m2))