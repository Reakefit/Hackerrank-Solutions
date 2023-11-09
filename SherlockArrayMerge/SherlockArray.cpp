#include <iostream>
#include <deque>
#include <vector>
#include <map>

using namespace std;

const int MOD = 1e9 + 7;

int arrayMerging(vector<int> m) {
    const long n = m.size();
    deque<tuple<int, int, int, long long>> q;
    q.push_back(make_tuple(m[0], 1, -1, 1LL));

    for (size_t i = 1; i < n; i++) {
        deque<tuple<int, int, int, long long>> nextQ;
        while (!q.empty()) {
            auto [subseqMax, subseqLen, prevSubseqL, ways] = q.front();
            q.pop_front();

            if (m[i] >= subseqMax) {
                if (prevSubseqL > subseqLen) {
                    nextQ.push_back(make_tuple(m[i], subseqLen + 1, prevSubseqL, ways * (prevSubseqL - subseqLen) % MOD));
                }
                if (prevSubseqL == -1) {
                    nextQ.push_back(make_tuple(m[i], subseqLen + 1, -1, 1));
                }
            }
            nextQ.push_back(make_tuple(m[i], 1, subseqLen, (subseqLen * ways) % MOD));
        }

        deque<tuple<int, int, int, long long>> condensedNextQ;
        map<tuple<int, int, int>, long long> condensed;
        for (auto& item : nextQ) {
            auto key = make_tuple(get<0>(item), get<1>(item), get<2>(item));
            if (condensed.find(key) != condensed.end()) {
                condensed[key] = (condensed[key] + get<3>(item)) % MOD;
            } else {
                condensed[key] = get<3>(item);
            }
        }

        for (auto& [key, combinedWays] : condensed) {
            condensedNextQ.push_back(make_tuple(get<0>(key), get<1>(key), get<2>(key), combinedWays));
        }

        q = condensedNextQ;
    }

    long long result = 0;
    for (auto& item : q) {
        result = (result + get<3>(item)) % MOD;
    }
    return result;
}

int main() {
    vector<int> m(100);
    for (int i = 1; i < 101; i++) {
        m[i] = i;
    }
    cout<<arrayMerging(m);
}