#include <vector>
#include <iostream>
#include <string>
using namespace std;

const int MOD = 1000000007;
const int SIZE = 1001;
vector<int> primeList;
vector<int> mobius(SIZE, 0);

void primeSieve() {
    mobius[1] = 1;
    vector<bool> isPrime(SIZE, false);
    for (int i = 2; i < SIZE; i++) {
        if (!isPrime[i]) {
            primeList.push_back(i);
            mobius[i] = -1;
        }
        for (int j : primeList) {
            if (i * j >= SIZE) {
                break;
            }
            isPrime[i * j] = true;
            if (i % j == 0) {
                mobius[i * j] = 0;
                break;
            }
            mobius[i * j] = -mobius[i];
        }
    }
}

vector<vector<int>> combination(SIZE, vector<int>(SIZE, 0));
void computeCombination() {
    for (int i = 0; i < SIZE; ++i) {
        combination[i][0] = combination[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            combination[i][j] = (combination[i - 1][j - 1] + combination[i - 1][j]) % MOD;
        }
    }
}

int solveProblem(int n, int k, string &a) {
    primeSieve();
    computeCombination();
    long long result = 0;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0 && mobius[i]) {
            int m = n / i;
            vector<int> dp(k + 1, 0);
            dp[0] = 1;
            for (int j = 0; j < m; j++) {
                int x = 0;
                for (int g = j; g < n; g += m) {
                    if (a[g] == '1') {
                        x++;
                    }
                }
                int y = i - x;
                for (int g = k; g >= 0; g--) {
                    dp[g] = ((g >= x ? dp[g - x] : 0) + (g >= y ? dp[g - y] : 0)) % MOD;
                }
            }
            int sumDp = 0;
            for (int j = 0; j <= k; j++) {
                sumDp = (sumDp + dp[j]) % MOD;
            }
            result = (result + sumDp * mobius[i]) % MOD;
        }
    }
    for (int i = 0; i <= k; ++i) {
        result = (result + combination[n][i]) % MOD;
    }
    return (result + MOD) % MOD;
}
