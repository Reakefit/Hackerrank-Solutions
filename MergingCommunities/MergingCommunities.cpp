#include <iostream>
#include <vector>
using namespace std;

vector<int> parent, population;

int find(int i) {
    if (i != parent[i]) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

void Union(int i, int j) {
    int i_id = find(i);
    int j_id = find(j);
    if (i_id != j_id) {
        if (population[i_id] > population[j_id]) {
            parent[j_id] = i_id;
            population[i_id] += population[j_id];
        } else {
            parent[i_id] = j_id;
            population[j_id] += population[i_id];
        }
    }
}

int main() {
    int n, q;
    char type;
    cin >> n >> q;
    parent.resize(n+1);
    population.resize(n+1);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        population[i] = 1;
    }
    while (q--) {
        cin >> type;
        if (type == 'M') {
            int i, j;
            cin >> i >> j;
            Union(i, j);
        } else {
            int i;
            cin >> i;
            cout << population[find(i)] << endl;
        }
    }
    return 0;
}


