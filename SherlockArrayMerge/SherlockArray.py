from collections import deque
MOD = 10**9 + 7

def arrayMerging(m):
    n, mod = len(m), 10**9+7
    q = deque()
    q.append((m[0], 1, -1, 1))

    for x in m[1:]:
        nextQ = deque([])
        while q:
            subseqMax, subseqLen, prevSubseqL, ways = q.popleft()
            if x >= subseqMax and prevSubseqL > subseqLen:
                # It can add to the subsequence only if length > prevSubsequence
                nextQ.append((x, subseqLen + 1, prevSubseqL, ways*(prevSubseqL - subseqLen)))
            if x >= subseqMax and prevSubseqL == -1:
                nextQ.append((x, subseqLen + 1, -1, 1))
            # regardless it can always make a new one:
            nextQ.append((x, 1, subseqLen, subseqLen*ways))
        q = nextQ
    
    print(q)
    return sum(ways for _, _, _, ways in q) % mod

if __name__ == '__main__':
    m = [1, 3, 2, 4]
    m3 = [1, 2, 3]
    m2 = [2, 1]
    m4 = [1,2,5,3,4]
    print(arrayMerging(m))
    print(arrayMerging(m3))
    print(arrayMerging(m4))
    print(arrayMerging(m2))