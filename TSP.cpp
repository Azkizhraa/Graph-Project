#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int tsp(int node, int mask, const vector<vector<int>>& dist, vector<vector<int>>& dp, int start, int n) {
    // Base case: if all nodes are visited, return distance to the start
    if (mask == (1 << n) - 1) {
        return dist[node][start]; // Return the cost to go back to the starting node
    }

    if (dp[node][mask] != -1) {
        return dp[node][mask]; // If already computed, return the stored result
    }

    int answer = INT_MAX;

    // Try to visit all other unvisited nodes
    for (int next = 0; next < n; ++next) {
        if ((mask & (1 << next)) == 0) { // If 'next' node is not visited
            int newAnswer = dist[node][next] + tsp(next, mask | (1 << next), dist, dp, start, n);
            answer = min(answer, newAnswer); // Choose the minimum path cost
        }
    }

    dp[node][mask] = answer; // Memoize the result
    return answer;
}

void findOptimalRoute(int start, const vector<vector<int>>& dist, vector<vector<int>>& dp, int n) {
    vector<int> path;
    int mask = 1 << start;
    int node = start;

    path.push_back(node);

    while (mask != (1 << n) - 1) {
        int bestNext = -1;
        for (int next = 0; next < n; ++next) {
            if ((mask & (1 << next)) == 0) {
                // Check if this is the best next node
                if (bestNext == -1 || 
                    dp[next][mask | (1 << next)] + dist[node][next] < 
                    dp[bestNext][mask | (1 << bestNext)] + dist[node][bestNext]) {
                    bestNext = next;
                }
            }
        }
        node = bestNext;
        path.push_back(node);
        mask |= (1 << node);
    }

    // Print the optimal route
    cout << "Route: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    // Read edges
    for (int i = 0; i < e; ++i) {
        int edgeName, u, v, cost;
        cin >> edgeName >> u >> v >> cost;
        dist[u - 1][v - 1] = cost;
        dist[v - 1][u - 1] = cost; // Assuming it's a bidirectional graph
    }

    // Starting point
    int start;
    cin >> start;
    start--;

    // Initialize dp table
    vector<vector<int>> dp(n, vector<int>(1 << n, -1));

    // Solve TSP
    int result = tsp(start, 1 << start, dist, dp, start, n);

    // Output the result
    cout << "Cost: " << result << endl;
    
    // Find and print the optimal route
    findOptimalRoute(start, dist, dp, n);

    return 0;
}
