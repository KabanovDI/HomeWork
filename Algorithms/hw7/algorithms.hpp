#pragma once

#include <vector>
#include <unordered_set>
#include <functional>
#include <queue>
#include <climits>


bool hasCycle(const std::vector<std::vector<int>>& graph);

bool isTree(const std::vector<std::vector<int>>& graph);

std::pair<std::vector<int>, std::vector<int>> dijkstra(const std::vector<std::vector<std::pair<int, int>>>& graph, int start);

bool isBipartite(const std::vector<std::vector<int>>& graph);
