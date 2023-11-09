#include <iostream>
#include <vector>
#include <map>

using namespace std;

pair<int, int> dfs(int node, vector<vector<int>>& graph, vector<bool>& visited, int dist, vector<int>& distances) {
    visited[node] = true;
    distances[node] = dist;
    int maxDistance = dist;
    int maxNode = node;
    for (int neighbour : graph[node]) {
        if (!visited[neighbour]) {
            auto [newDist, newNode] = dfs(neighbour, graph, visited, dist + 1, distances);
            if (newDist > maxDistance) {
                maxDistance = newDist;
                maxNode = newNode;
            }
        }
    }
    return {maxDistance, maxNode};
}

tuple<int, int, int> treeDiameterAndNodes(int n, vector<vector<int>>& graph) {
    vector<bool> visited(n + 1, false);
    vector<int> distances(n + 1, 0);
    auto [_, farthestNode] = dfs(1, graph, visited, 0, distances);

    fill(visited.begin(), visited.end(), false);
    auto [diameter, diameterNode] = dfs(farthestNode, graph, visited, 0, distances);
    return {diameter, farthestNode, diameterNode};
}

pair<vector<int>, vector<int>> findDistanceToDiameterNodes(int n, vector<vector<int>>& graph, int diameterNode1, int diameterNode2) {
    vector<bool> visited(n + 1, false);
    vector<int> dist1(n + 1, 0);
    dfs(diameterNode1, graph, visited, 0, dist1);

    fill(visited.begin(), visited.end(), false);
    vector<int> dist2(n + 1, 0);
    dfs(diameterNode2, graph, visited, 0, dist2);

    return {dist1, dist2};
}

vector<int> journeyScheduling(int n, vector<vector<int>>& graph, vector<pair<int, int>>& queries) {
    auto [diameter, diameterNode1, diameterNode2] = treeDiameterAndNodes(n, graph);
    auto [dist1, dist2] = findDistanceToDiameterNodes(n, graph, diameterNode1, diameterNode2);
    vector<int> answer;
    for (auto [start, k] : queries) {
        if (k == 1) {
            answer.push_back(max(dist1[start], dist2[start]));
        } else {
            answer.push_back(max(dist1[start], dist2[start]) + (k - 1) * diameter);
        }
    }
    return answer;
}

int main() {
    int n = 8, m = 2;

    vector<pair<int, int>> edges = {{1, 2}, {2, 3}, {2, 4}, {1, 5}, {1, 6}, {1, 7}, {7, 8}};
    vector<vector<int>> graph(n + 1);
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<pair<int, int>> queries = {{4, 6}, {6, 3}, {7, 6}, {4, 6}, {7, 1}, {2, 6}};
    vector<int> answer = journeyScheduling(n, graph, queries);

    for (int ans : answer) {
        cout << ans << endl;
    }

    return 0;
}

