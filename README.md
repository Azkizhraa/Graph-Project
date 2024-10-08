# Graph-Project Report

| Name           | NRP        | Kelas     |
| ---            | ---        | ----------|
| Azkiya Rusyda Z. | 5025231072 |  IUP |
| Kinar Naila F. | 5025231001 |  IUP |
| Safa Nadhira A. | 5025231086 |  IUP |
| Sinta Probondari W. | 5025231067 |  IUP |

## Travelling Salesman Problem
1. Introduction 
    TSP is a classic algorithmic problem with the goal is to discover the shortest path that visits each city precisely once and return to the starting city given a collection of cities and the distances between each pair of cities. 

2. Algorithm overview
    The code that we provided uses a greedy algorithm. The next edge with the least weight that joins the current node to an unvisited node is chosen iteratively using this approach. The algorithm won't stop until every node has been visited, at which point it adds the edge that circles back to the original node.

3. Code explanation
- Full Code
```c++
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int id, u, v, weight;
};

int findMinCost(int start, const vector<Edge>& edges, int n, vector<int>& route) {
    vector<bool> visited(n, false);
    visited[start] = true;
    int totalCost = 0;
    int currentNode = start;

    for (int i = 0; i < n - 1; ++i) {
        int minCost = numeric_limits<int>::max();
        Edge* nextEdge = nullptr;

        for (const auto& edge : edges) {
            if ((edge.u == currentNode && !visited[edge.v]) || 
                (edge.v == currentNode && !visited[edge.u])) {
                if (edge.weight < minCost) {
                    minCost = edge.weight;
                    nextEdge = const_cast<Edge*>(&edge);
                }
            }
        }
        if (!nextEdge) {
            break;
        }

        visited[nextEdge->u] = true;
        visited[nextEdge->v] = true;
        totalCost += nextEdge->weight;
        currentNode = (nextEdge->u == currentNode) ? nextEdge->v : nextEdge->u;

        route.push_back(nextEdge->id);
    }

    for (const auto& edge : edges) {
        if ((edge.u == currentNode && edge.v == start) || (edge.v == currentNode && edge.u == start)) {
            totalCost += edge.weight;
            route.push_back(edge.id);
            break;
        }
    }
    return totalCost;
}

int main() {
    int n, e;
    cin >> n >> e; 

    vector<Edge> edges(e);
    for (int i = 0; i < e; ++i) {
        cin >> edges[i].id >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    int start; cin >> start;
    vector<int> route;
    int totalCost = findMinCost(start, edges, n, route);
    
    cout << "Cost: " << totalCost << endl;
    cout << "Route: ";
    for (size_t i = 0; i < route.size(); ++i) {
        cout << route[i];
        if (i < route.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return 0;
}
```
In here, we made a struct for the edge, id for the edge name, u, v are the two end points of the edge, and weight is for the cost fo traversing that edge

```c++
int findMinCost(int start, const vector<Edge>& edges, int n, vector<int>& route) {
    vector<bool> visited(n, false);
    visited[start] = true;
    int totalCost = 0;
    int currentNode = start;
```
this function takes the starting node, a list of edges, total of nodes, and a vector to store the route that has been taken.
- `visited` is initialized to keep track of which node have been visited
- the route's total cost is calculated by initializing the `totalCost` variable to 0.

```c++
    for (int i = 0; i < n - 1; ++i) {
        int minCost = numeric_limits<int>::max();
        Edge* nextEdge = nullptr;

        for (const auto& edge : edges) {
            if ((edge.u == currentNode && !visited[edge.v]) || 
                (edge.v == currentNode && !visited[edge.u])) {
                if (edge.weight < minCost) {
                    minCost = edge.weight;
                    nextEdge = const_cast<Edge*>(&edge);
                }
            }
        }
```
the main loop iterates `n-1` times (-1 of total nodes) to find the minimum cost edges.
`minCost` variable is initialized to the max possible int value, while `nextEdge` is used to track the edge with the minimum weight.
inside the nested loop, for each edge it will check whether it connects to the `currentNode` to an unvisited one. if yes, and if its weight is less than `minCost`, it will update `minCost` and set `nextEdge` to point to the new edge.

```c++
        if (!nextEdge) {
            break;
        }

        visited[nextEdge->u] = true;
        visited[nextEdge->v] = true;
        totalCost += nextEdge->weight;
        currentNode = (nextEdge->u == currentNode) ? nextEdge->v : nextEdge->u;

        route.push_back(nextEdge->id);
    }
```
of no `nextEdge` is found, then just break the loop (all edges are visited)
the nodes connected by `nextEdge` are marked as visited, and the `totalCost` will be incremented by the weight of the `nextEdge`
`currentNode` will be updated to the newly visited node, and the edge id is added to the `route` vector.

```c++
    for (const auto& edge : edges) {
        if ((edge.u == currentNode && edge.v == start) || (edge.v == currentNode && edge.u == start)) {
            totalCost += edge.weight;
            route.push_back(edge.id);
            break;
        }
    }
    return totalCost;
}
```
after visiting all nodes, the algorithm will look for the edge that connects to the current node back to the starting node. the weight of the edge will be added to `totalCost` and its id will also be added to teh `route`

```c++
int main() {
    int n, e;
    cin >> n >> e; 

    vector<Edge> edges(e);
    for (int i = 0; i < e; ++i) {
        cin >> edges[i].id >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    int start; cin >> start;
    vector<int> route;
    int totalCost = findMinCost(start, edges, n, route);
    
    cout << "Cost: " << totalCost << endl;
    cout << "Route: ";
    for (size_t i = 0; i < route.size(); ++i) {
        cout << route[i];
        if (i < route.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return 0;
}
```
For the main function, it will read the number of nodes (variable n) and edges (variable e) followed with its details. Reading its starting (and ending) node, and call out the `findMinCost` function. 

## Chinese Postman Problem
1. Introduction
    CPP involves finding the shortest possible route that traverses every street exactly once. The problem is to find shortest path or circuity that visits every edge of the graph at least once.
    By solving this problem, we can optimize routes and minimize the resources required for various tasks.

2. Code Explanation
```c++
    #include <bits/stdc++.h>
    using namespace std; 
```
This includes all the standard libraries in C++.

```c++
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
```
This algorithm find the shortest path from a starting node to all the other nodes in a weighted graph. It uses a priority queue to explore the nearest node iteratively, updating the shortest paths to its neighbors and if a shorter path is found, it will update the distance and add the neighbour to the priority queue.

```c++
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
```
Constructs an Eulerian circuit using a stack to keep track of the current path. The algorithm begins by pushing the starting node onto a stack and iterates while there are nodes in the stack. It checks if the current node has unvisited edges; if so, it follows the last edge to the next node and removes that edge from both ends of the graph to prevent revisiting. If no edges are left for the current node, it adds the node to the route and pops it from the stack. Finally, the route is reversed to present it in the correct order.

```c++
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
```
This class contains the main logic in solving the Chinese Postman Problem. The algorithm constructs a graph using an adjacency list to represent edges, while also calculating the total cost of all edges, storing each edge with its cost and identifier. It then determines the degree of each vertex, collecting those with odd degrees, as these vertices must be paired to create an Eulerian circuit, which requires all vertices to have even degrees. If there are no odd degree vertices, the function outputs the total cost and route, indicating that an Eulerian circuit is already possible. For graphs with odd degree vertices, Dijkstra's algorithm computes the shortest paths between all pairs, and permutations are used to find the minimum cost of pairing these vertices to achieve even degrees. The minimum additional cost is added to the total cost, and the findEulerianCircuit function is called to retrieve and print the final path.

```c++
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
```
The main function handles the user inputs such as the nodes, edges, and the edges details. It stores these details in the edges vector and it then prompts for a starting node and calls the chinesePostmanProblem method to compute the solution.

## The Knight's Tour
1. Introduction
    The Knight's Tour problem is a classic computational puzzle that involves finding a sequence of moves for a knight on a chessboard so that it visits every street exactly once.

2. Code Explanation
```c++
    #include <iostream>
    #include <vector>

    #define N 5
    using namespace std;

    int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    bool isValid(int x, int y, vector<vector<int>> &    board) {
        return (x >= 0 && x < N && y >= 0 && y < N &&   board[x][y] == -1);
    }
```
    this function checks if a given move is valid by ensuring that the new square is within the bounds of the chessboard and has not been visited before. the size of the chessboard itself is 5, defined at the beginning of the code. we also defined 2 arrays where each store the possible x and y displacements for a knight's move on a chessboard. in the `isValid` function, there are 3 parameters: x and y which represents the coordinates of the new square to check, and board which refers to a 2D vector representing the chessboard. 

```c++
    bool solveKTUtil(int x, int y, int movei, vector<vector<int>> &board)   {
        if (movei == N * N) {
            return true; // All squares are visited
        }

        for (int i = 0; i < 8; i++) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if (isValid(nextX, nextY, board)) {
                board[nextX][nextY] = movei;
                if (solveKTUtil(nextX, nextY, movei + 1, board)) {
                    return true;
                } else {
                    board[nextX][nextY] = -1;
                }
            }
        }
        return false;
    }
```
    this function is the recursive function that explores all possible moves and backtracks if necessary. there are 4 parameters in this function: x and y which represents the current coordinates of the knight; movei which represents the current move number; and board which refers to the 2D vector representing the chessboard. `if(movei==N*N)` checks if all squares have been visited. and if all squares have been visited, the function will return true, indicating a soultion has been found. there is a loop in this function that checks if each move is valid, and recursively explores the consequences of each move to find a solution.

```c++
    bool solveKnightTour(int startX, int startY) {
        vector<vector<int>> board(N, vector<int>(N, -1));
        board[startX][startY] = 0;

        if (!solveKTUtil(startX, startY, 1, board)) {
            cout << "Solution does not exist" << endl;
            return false;
        } else {
        
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
        }
        return true;
    }
```
    this function is responsible for initializing the chessboard, placing the knight at the starting position, and calling the recursive function `solveKTUtil` to solve the knight's tour problem. first, it creates a 2D vector to represent the chessboard and initializes all elements to -1. then it places the knight at the specified starting position. next, it calls the `solveKTUtil`function, print the schessboard with the sequence of moves if the return message is true. this indicates a solution was found. otherwise it will print a message that shows no solution was found. 

```c++
        int main() {
        int startX = 2, startY = 2;

        solveKnightTour(startX, startY);
        return 0;
    }
```
    in the main function, we only declare the starting point which is 2,2. then we call the `solveKnightTour` to solve the problem. 
