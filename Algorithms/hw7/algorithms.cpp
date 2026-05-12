#include "algorithms.hpp"

using namespace std;


bool hasCycle(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    
    function<bool(int, int)> dfs = [&](int vertex, int parent) -> bool {
        visited[vertex] = true;
        
        for (int neighbor : graph[vertex]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, vertex)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true; 
            }
        }
        return false;
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, -1)) {
                return true;
            }
        }
    }
    
    return false;
}

bool isTree(const vector<vector<int>>& graph) {
    int n = graph.size();
    
    if (n == 0) return false;
    
    vector<bool> visited(n, false);
    queue<int> q;
    
    q.push(0);
    visited[0] = true;
    int visitedCount = 1;
    
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        
        for (int neighbor : graph[vertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                visitedCount++;
                q.push(neighbor);
            }
        }
    }
    
    bool isConnected = (visitedCount == n);
    
    int edgeCount = 0;
    for (int i = 0; i < n; i++) {
        edgeCount += graph[i].size();
    }
    edgeCount = (edgeCount + 1) / 2; 
    
    bool hasCorrectEdges = (edgeCount == n - 1);
    
    return isConnected && hasCorrectEdges;
}

pair<vector<int>, vector<int>> dijkstra(const vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, INT_MAX);
    vector<int> prev(n, -1);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distances[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int currentDist = pq.top().first;
        if (currentDist < 0) throw "Better use Bellman-Ford algorithm";
        int currentVertex = pq.top().second;
        pq.pop();
        
        if (currentDist > distances[currentVertex]) {
            continue;
        }
        
        // Релаксация всех соседей
        for (const auto& edge : graph[currentVertex]) {
            int neighbor = edge.second;
            int weight = edge.first;
            int newDist = currentDist + weight;
            
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                prev[neighbor] = currentVertex;
                pq.push({newDist, neighbor});
            }
        }
    }
    
    return {distances, prev};
}

bool isBipartite(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);
    
    for (int start = 0; start < n; start++) {
        if (color[start] != -1) continue; 
        
        queue<int> q;
        q.push(start);
        color[start] = 0; 
        
        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            
            for (int neighbor : graph[vertex]) {
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[vertex];
                    q.push(neighbor);
                }
                else if (color[neighbor] == color[vertex]) {
                    return false;
                }
            }
        }
    }
    return true;
}