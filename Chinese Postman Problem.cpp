#include <bits/stdc++.h>

using namespace std;

// Dijkstra's algorithm for finding shortest paths from the start node
vector<int> dijkstra(int start, const vector<vector<pair<int, pair<int, int>>>> &g) {
    int n = g.size();
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto &[vIndex, weightPair] : g[u]) {
            int weight = weightPair.first; // Get the cost of the edge
            if (dist[u] + weight < dist[vIndex]) {
                dist[vIndex] = dist[u] + weight;
                pq.push({dist[vIndex], vIndex});
            }
        }
    }
    return dist;
}

// Function to find the Eulerian circuit
void findEulerianCircuit(int u, vector<vector<pair<int, pair<int, int>>>> &g, vector<int> &route) {
    stack<int> s;
    s.push(u);

    while (!s.empty()) {
        int curr = s.top();
        if (!g[curr].empty()) {
            auto nextEdge = g[curr].back();
            s.push(nextEdge.first);
            g[curr].pop_back();

            // Remove the edge from the other end as well
            auto &nextNodeEdges = g[nextEdge.first];
            nextNodeEdges.erase(remove_if(nextNodeEdges.begin(), nextNodeEdges.end(),
                [curr](const auto &edge) { return edge.first == curr; }), nextNodeEdges.end());
        } else {
            route.push_back(curr);
            s.pop();
        }
    }
    reverse(route.begin(), route.end());
}

class Solution {
public:
    int chinesePostmanProblem(vector<vector<int>> &edges, int n, int start) {
        vector<vector<pair<int, pair<int, int>>>> g(n + 1); // Store edges with costs (1-based indexing)
        int totalCost = 0;

        // Building the graph and calculating the total cost
        for (const auto &edge : edges) {
            int edgeName = edge[0], node1 = edge[1], node2 = edge[2], cost = edge[3];
            totalCost += cost;
            g[node1].emplace_back(node2, make_pair(cost, edgeName)); // Store the cost and edge name
            g[node2].emplace_back(node1, make_pair(cost, edgeName)); // Store the reverse edge
        }

        vector<int> oddDegreeVertices, degree(n + 1, 0); // Adjust for 1-based indexing
        for (int i = 1; i <= n; i++) {
            degree[i] = g[i].size();
            if (degree[i] % 2) oddDegreeVertices.push_back(i);
        }

        // If there are no odd degree vertices, we can use the existing edges
        if (oddDegreeVertices.empty()) {
            cout << "Cost: " << totalCost << endl << "Route: ";
            return totalCost;
        }

        int oddCount = oddDegreeVertices.size();
        vector<vector<int>> shortestPaths(oddCount, vector<int>(oddCount));

        // Finding shortest paths between odd degree vertices
        for (int i = 0; i < oddCount; i++) {
            vector<int> dist = dijkstra(oddDegreeVertices[i], g);
            for (int j = 0; j < oddCount; j++) {
                shortestPaths[i][j] = dist[oddDegreeVertices[j]];
            }
        }

        // Find the minimum cost for pairing odd degree vertices
        int minAdditionalCost = INT_MAX;
        vector<int> pairing(oddCount);
        iota(pairing.begin(), pairing.end(), 0);

        do {
            int currentCost = 0;
            for (int i = 0; i < oddCount; i += 2) {
                currentCost += shortestPaths[pairing[i]][pairing[i + 1]];
            }
            minAdditionalCost = min(minAdditionalCost, currentCost);
        } while (next_permutation(pairing.begin(), pairing.end()));

        totalCost += minAdditionalCost;
        cout << "Cost: " << totalCost << endl;

        // Finding the Eulerian circuit and storing the edge names in the route
        vector<int> route;
        findEulerianCircuit(start, g, route);

        cout << "Route: ";
        for (size_t i = 0; i < route.size(); ++i) {
            cout << route[i];
            if (i < route.size() - 1) cout << ", ";
        }
        
        // Ensure the route returns to the start node
        cout << ", " << route[0] << endl; // Print the starting point at the end

        return totalCost;
    }
};

int main() {
    int n, e; 
    cin >> n >> e; 

    vector<vector<int>> edges(e, vector<int>(4)); 
    for (int i = 0; i < e; i++) {
        int edgeName, node1, node2, cost;
        cin >> edgeName >> node1 >> node2 >> cost; 
        edges[i] = {edgeName, node1, node2, cost}; 
    }

    int start;
    cin >> start; 

    Solution sol;
    sol.chinesePostmanProblem(edges, n, start); 

    return 0;
}
