modulus = 1000000007
size = 1001
primeList = []
mobius = [0] * size

def primeSieve(): 
    mobius[1] = 1
    isPrime = [False] * size
    for i in range(2, size):
        if not isPrime[i]:
            primeList.append(i)
            mobius[i] = -1
        for j in primeList:
            if i * j >= size:
                break
            isPrime[i * j] = True
            if i % j == 0:
                mobius[i * j] = 0
                break
            mobius[i * j] = -mobius[i]

combination = [[0] * size for _ in range(size)]
def computeCombination():
    for i in range(size):
        combination[i][0] = combination[i][i] = 1
        for j in range(1, i):
            combination[i][j] = (combination[i - 1][j - 1] + combination[i - 1][j]) % modulus

def solveProblem(n, k, a):
    primeSieve()
    computeCombination()
    result = 0
    for i in range(2, n + 1):
        if n % i == 0 and mobius[i]:
            m = n // i
            dp = [0] * (k + 1)
            dp[0] = 1
            for j in range(m):
                x = sum(a[g] == '1' for g in range(j, n, m))
                y = i - x
                for g in range(k, -1, -1):
                    dp[g] = ((dp[g - x] if g >= x else 0) + (dp[g - y] if g >= y else 0)) % modulus
            sumDp = sum(dp[j] for j in range(k + 1)) % modulus
            result = (result + sumDp * mobius[i]) % modulus
    for i in range(k + 1):
        result = (result + combination[n][i]) % modulus
    return (result + modulus) % modulus
