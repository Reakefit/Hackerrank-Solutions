#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

bool isValid(int x, int y, int n, int m) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> maze(n);
    for(int i = 0; i < n; i++)
        cin >> maze[i];
    map<pair<int, int>, pair<int, int>> tunnel;
    for(int i = 0; i < k; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        tunnel[{x1-1, y1-1}] = {x2-1, y2-1};
        tunnel[{x2-1, y2-1}] = {x1-1, y1-1};
    }

    map<pair<int, int>, int> states;
    states[{-1, 1}] = 0;
    int state = 1, startState;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(maze[i][j] == 'A' || maze[i][j] == 'O' || maze[i][j] == '%') {
                states[{i, j}] = state++;
                if(maze[i][j] == 'A')
                    startState = state - 1;
            }
        }
    }

    vector<double> probabilities(state, 0.0);
    vector<vector<pair<int, double>>> t(state);
    t[0].push_back({0, 1.0});

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(maze[i][j] == '#' || maze[i][j] == '*')
                continue;
            if(maze[i][j] == '%') {
                probabilities[states[{i, j}]] = 1.0;
                t[states[{i, j}]].push_back({states[{i, j}], 1.0});
                continue;
            }
            int ni = i, nj = j;
            if(tunnel.count({i, j}))
                tie(ni, nj) = tunnel[{i, j}];
            vector<pair<int, int>> success;
            int fail = 0;
            for(auto [dx, dy] : vector<pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
                if(isValid(ni + dx, nj + dy, n, m)) {
                    if(maze[ni + dx][nj + dy] == 'A' || maze[ni + dx][nj + dy] == 'O' || maze[ni + dx][nj + dy] == '%')
                        success.push_back({ni + dx, nj + dy});
                    else if(maze[ni + dx][nj + dy] == '*')
                        fail++;
                }
            }
            if(success.empty())
                t[states[{i, j}]].push_back({0, 1.0});
            else {
                for(auto [x, y] : success)
                    t[states[{i, j}]].push_back({states[{x, y}], 1.0 / (success.size() + fail)});
                if(fail > 0)
                    t[states[{i, j}]].push_back({0, double(fail) / (success.size() + fail)});
            }
        }
    }

    double minDifference = 1e-10;
    bool minDifferenceReached = false;

    while(!minDifferenceReached) {
        vector<double> prob = probabilities;
        for(int s = 0; s < state; s++) {
            double probState = 0;
            for(auto [a, b] : t[s])
                probState += probabilities[a] * b;
            probabilities[s] = probState;
        }
        minDifferenceReached = true;
        for(int s = 0; s < state; s++) {
            if(abs(probabilities[s] - prob[s]) > minDifference) {
                minDifferenceReached = false;
                break;
            }
        }
    }

    cout << probabilities[startState] << endl;

    return 0;
}
