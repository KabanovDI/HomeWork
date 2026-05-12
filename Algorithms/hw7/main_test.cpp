#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "algorithms.hpp"

using namespace std;


TEST_CASE("hasCycle - graph without cycles", "[task1]") {
    SECTION("Empty graph") {
        vector<vector<int>> graph;
        REQUIRE(hasCycle(graph) == false);
    }
    
    SECTION("One vertex") {
        vector<vector<int>> graph(1);
        REQUIRE(hasCycle(graph) == false);
    }
    
    SECTION("Two vertices with one edge") {
        vector<vector<int>> graph(2);
        graph[0] = {1};
        graph[1] = {0};
        REQUIRE(hasCycle(graph) == false);
    }
    
    SECTION("Chain of three vertices") {
        vector<vector<int>> graph(3);
        graph[0] = {1};
        graph[1] = {0, 2};
        graph[2] = {1};
        REQUIRE(hasCycle(graph) == false);
    }
    
    SECTION("Star") {
        vector<vector<int>> graph(4);
        graph[0] = {1, 2, 3};
        graph[1] = {0};
        graph[2] = {0};
        graph[3] = {0};
        REQUIRE(hasCycle(graph) == false);
    }
}

TEST_CASE("hasCycle - graph with cycle", "[task1]") {
    SECTION("Triangle") {
        vector<vector<int>> graph(3);
        graph[0] = {1, 2};
        graph[1] = {0, 2};
        graph[2] = {0, 1};
        REQUIRE(hasCycle(graph) == true);
    }
    
    SECTION("Square") {
        vector<vector<int>> graph(4);
        graph[0] = {1, 3};
        graph[1] = {0, 2};
        graph[2] = {1, 3};
        graph[3] = {0, 2};
        REQUIRE(hasCycle(graph) == true);
    }
    
    SECTION("Graph with loop") {
        vector<vector<int>> graph(1);
        graph[0] = {0};  // Петля
        REQUIRE(hasCycle(graph) == true);
    }
    
    SECTION("Disconnected graph") {
        vector<vector<int>> graph(5);
        graph[0] = {1, 2};
        graph[1] = {0, 2};
        graph[2] = {0, 1};
        graph[3] = {4};
        graph[4] = {3};
        REQUIRE(hasCycle(graph) == true);
    }
}

TEST_CASE("hasCycle - difficult cases", "[task1]") {
    SECTION("Complete graph K4") {
        vector<vector<int>> graph(4);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i != j) graph[i].push_back(j);
            }
        }
        REQUIRE(hasCycle(graph) == true);
    }
    
    SECTION("Bipartite graph") {
        vector<vector<int>> graph(6);
        graph[0] = {3, 4};
        graph[1] = {3, 5};
        graph[2] = {4, 5};
        graph[3] = {0, 1};
        graph[4] = {0, 2};
        graph[5] = {1, 2};
        REQUIRE(hasCycle(graph) == true);
    }
}


TEST_CASE("isTree - correct trees", "[task2]") {
    SECTION("One vertex") {
        vector<vector<int>> graph(1);
        REQUIRE(isTree(graph) == true);
    }
    
    SECTION("Two vertices with one edge") {
        vector<vector<int>> graph(2);
        graph[0] = {1};
        graph[1] = {0};
        REQUIRE(isTree(graph) == true);
    }
    
    SECTION("Chain of three vertices") {
        vector<vector<int>> graph(3);
        graph[0] = {1};
        graph[1] = {0, 2};
        graph[2] = {1};
        REQUIRE(isTree(graph) == true);
    }
    
    SECTION("Star") {
        vector<vector<int>> graph(5);
        graph[0] = {1, 2, 3, 4};
        graph[1] = {0};
        graph[2] = {0};
        graph[3] = {0};
        graph[4] = {0};
        REQUIRE(isTree(graph) == true);
    }
    
    SECTION("Binary tree") {
        vector<vector<int>> graph(7);
        graph[0] = {1, 2};
        graph[1] = {0, 3, 4};
        graph[2] = {0, 5, 6};
        graph[3] = {1};
        graph[4] = {1};
        graph[5] = {2};
        graph[6] = {2};
        REQUIRE(isTree(graph) == true);
    }
}

TEST_CASE("isTree - incorrect trees (forest)", "[task2]") {
    SECTION("Two isolated vertices") {
        vector<vector<int>> graph(2);
        REQUIRE(isTree(graph) == false);
    }
    
    SECTION("Two components of two vertices") {
        vector<vector<int>> graph(4);
        graph[0] = {1};
        graph[1] = {0};
        graph[2] = {3};
        graph[3] = {2};
        REQUIRE(isTree(graph) == false);
    }
    
    SECTION("One component and one isolated vertex") {
        vector<vector<int>> graph(3);
        graph[0] = {1};
        graph[1] = {0};
        REQUIRE(isTree(graph) == false);
    }
}

TEST_CASE("isTree - not trees", "[task2]") {
    SECTION("Triangle") {
        vector<vector<int>> graph(3);
        graph[0] = {1, 2};
        graph[1] = {0, 2};
        graph[2] = {0, 1};
        REQUIRE(isTree(graph) == false);
    }
    
    SECTION("Square") {
        vector<vector<int>> graph(4);
        graph[0] = {1, 3};
        graph[1] = {0, 2};
        graph[2] = {1, 3};
        graph[3] = {0, 2};
        REQUIRE(isTree(graph) == false);
    }
}

TEST_CASE("isTree - special cases", "[tree]") {
    SECTION("Empty graph") {
        vector<vector<int>> graph;
        REQUIRE(isTree(graph) == false);
    }
    
    SECTION("Loop") {
        vector<vector<int>> graph(1);
        graph[0] = {0};
        REQUIRE(isTree(graph) == false);
    }
    
    SECTION("Multigraph") {
        vector<vector<int>> graph(2);
        graph[0] = {1, 1};  
        graph[1] = {0, 0};
        REQUIRE(isTree(graph) == false);
    }
}


TEST_CASE("dijkstra - usual graphs", "[task3]") {
    SECTION("One vertex") {
        vector<vector<pair<int, int>>> graph(1);
        auto [dist, prev] = dijkstra(graph, 0);
        REQUIRE(dist.size() == 1);
        REQUIRE(dist[0] == 0);
        REQUIRE(prev[0] == -1);
    }
    
    SECTION("Two vertices") {
        vector<vector<pair<int, int>>> graph(2);
        graph[0] = {{5, 1}};
        graph[1] = {{5, 0}};
        
        auto [dist, prev] = dijkstra(graph, 0);
        REQUIRE(dist[0] == 0);
        REQUIRE(dist[1] == 5);
        REQUIRE(prev[1] == 0);
    }
    
    SECTION("Chain") {
        vector<vector<pair<int, int>>> graph(3);
        graph[0] = {{2, 1}};
        graph[1] = {{2, 0}, {3, 2}};
        graph[2] = {{3, 1}};
        
        auto [dist, prev] = dijkstra(graph, 0);
        REQUIRE(dist[0] == 0);
        REQUIRE(dist[1] == 2);
        REQUIRE(dist[2] == 5);  // 0->1->2: 2+3=5
        REQUIRE(prev[1] == 0);
        REQUIRE(prev[2] == 1);
    }
}

TEST_CASE("dijkstra - graph with several paths", "[task3]") {
    SECTION("Choosing the shortest path") {
        vector<vector<pair<int, int>>> graph(3);
        graph[0] = {{5, 1}, {1, 2}};
        graph[1] = {{5, 0}, {2, 2}};
        graph[2] = {{1, 0}, {2, 1}};
        
        auto [dist, prev] = dijkstra(graph, 0);
        REQUIRE(dist[0] == 0);
        REQUIRE(dist[1] == 3);  
        REQUIRE(dist[2] == 1);
        REQUIRE(prev[1] == 2);
        REQUIRE(prev[2] == 0);
    }
    
    SECTION("Several paths of the same lenght") {
        vector<vector<pair<int, int>>> graph(4);
        graph[0] = {{2, 1}, {2, 2}};
        graph[1] = {{2, 0}, {2, 3}};
        graph[2] = {{2, 0}, {2, 3}};
        graph[3] = {{2, 1}, {2, 2}};
        
        auto [dist, prev] = dijkstra(graph, 0);
        REQUIRE(dist[0] == 0);
        REQUIRE(dist[1] == 2);
        REQUIRE(dist[2] == 2);
        REQUIRE(dist[3] == 4);  
    }
}

TEST_CASE("dijkstra - unattainable vrtices", "[task3]") {
    SECTION("Isolated vertex") {
        vector<vector<pair<int, int>>> graph(3);
        graph[0] = {{1, 1}};
        graph[1] = {{1, 0}};
        
        auto [dist, prev] = dijkstra(graph, 0);
        REQUIRE(dist[0] == 0);
        REQUIRE(dist[1] == 1);
        REQUIRE(dist[2] == INT_MAX);
        REQUIRE(prev[2] == -1);
    }
    
    SECTION("Two components") {
        vector<vector<pair<int, int>>> graph(4);
        graph[0] = {{3, 1}};
        graph[1] = {{3, 0}};
        graph[2] = {{4, 3}};
        graph[3] = {{4, 2}};
        
        auto [dist, prev] = dijkstra(graph, 0);
        REQUIRE(dist[0] == 0);
        REQUIRE(dist[1] == 3);
        REQUIRE(dist[2] == INT_MAX);
        REQUIRE(dist[3] == INT_MAX);
    }
}

TEST_CASE("dijkstra - difficult graph", "[task3]") {
    SECTION("Graph") {
        //     (4)     (2)
        //   0 --- 1 --- 3
        //    \    |    /
        //    (2) (1) (8)
        //      \  |  /
        //        2
        vector<vector<pair<int, int>>> graph(4);
        graph[0] = {{4, 1}, {2, 2}};
        graph[1] = {{4, 0}, {1, 2}, {2, 3}};
        graph[2] = {{2, 0}, {1, 1}, {8, 3}};
        graph[3] = {{2, 1}, {8, 2}};
        
        auto [dist, prev] = dijkstra(graph, 0);
        REQUIRE(dist[0] == 0);
        REQUIRE(dist[1] == 3);  
        REQUIRE(dist[2] == 2);  
        REQUIRE(dist[3] == 5);  
        REQUIRE(prev[1] == 2);
        REQUIRE(prev[2] == 0);
        REQUIRE(prev[3] == 1);
    }
}

TEST_CASE("isBipartite - bipartite graph", "[task4]") {
    SECTION("Empty graph") {
        vector<vector<int>> graph;
        REQUIRE(isBipartite(graph) == true);
    }
    
    SECTION("One vertex") {
        vector<vector<int>> graph(1);
        REQUIRE(isBipartite(graph) == true);
    }
    
    SECTION("Two vertices") {
        vector<vector<int>> graph(2);
        graph[0] = {1};
        graph[1] = {0};
        REQUIRE(isBipartite(graph) == true);
    }
    
    SECTION("Chain") {
        vector<vector<int>> graph(4);
        graph[0] = {1};
        graph[1] = {0, 2};
        graph[2] = {1, 3};
        graph[3] = {2};
        REQUIRE(isBipartite(graph) == true);
    }
    
    SECTION("Square") {
        vector<vector<int>> graph(4);
        graph[0] = {1, 3};
        graph[1] = {0, 2};
        graph[2] = {1, 3};
        graph[3] = {0, 2};
        REQUIRE(isBipartite(graph) == true);
    }
    
    SECTION("Six vertices") {
        vector<vector<int>> graph(6);
        graph[0] = {3, 4};
        graph[1] = {3, 5};
        graph[2] = {4, 5};
        graph[3] = {0, 1};
        graph[4] = {0, 2};
        graph[5] = {1, 2};
        REQUIRE(isBipartite(graph) == true);
    }
    
    SECTION("Two components") {
        vector<vector<int>> graph(5);
        graph[0] = {1};
        graph[1] = {0, 2};
        graph[2] = {1};
        graph[3] = {4};
        graph[4] = {3};
        REQUIRE(isBipartite(graph) == true);
    }
}

TEST_CASE("isBipartite - not bipartite graphs", "[task4]") {
    SECTION("Triangle") {
        vector<vector<int>> graph(3);
        graph[0] = {1, 2};
        graph[1] = {0, 2};
        graph[2] = {0, 1};
        REQUIRE(isBipartite(graph) == false);
    }
    
    SECTION("Pentagon") {
        vector<vector<int>> graph(5);
        for (int i = 0; i < 5; i++) {
            graph[i].push_back((i + 1) % 5);
            graph[i].push_back((i - 1 + 5) % 5);
        }
        REQUIRE(isBipartite(graph) == false);
    }
    
    SECTION("Complete graph K3") {
        vector<vector<int>> graph(3);
        graph[0] = {1, 2};
        graph[1] = {0, 2};
        graph[2] = {0, 1};
        REQUIRE(isBipartite(graph) == false);
    }
}

TEST_CASE("isBipartite - difficult cases", "[bipartite]") {
    SECTION("Complete bipartite graph K_{3,3}") {
        vector<vector<int>> graph(6);
        for (int i = 0; i < 3; i++) {
            for (int j = 3; j < 6; j++) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
        REQUIRE(isBipartite(graph) == true);
    }
    
    SECTION("Loop") {
        vector<vector<int>> graph(1);
        graph[0] = {0};  
        REQUIRE(isBipartite(graph) == false);
    }
    
    SECTION("Tree") {
        vector<vector<int>> graph(7);
        graph[0] = {1, 2};
        graph[1] = {0, 3, 4};
        graph[2] = {0, 5, 6};
        graph[3] = {1};
        graph[4] = {1};
        graph[5] = {2};
        graph[6] = {2};
        REQUIRE(isBipartite(graph) == true);
    }
    
    SECTION("Two components, one of them is not bipartite") {
        vector<vector<int>> graph(5);
        graph[0] = {1, 2};
        graph[1] = {0, 2};
        graph[2] = {0, 1};
        graph[3] = {4};
        graph[4] = {3};
        REQUIRE(isBipartite(graph) == false);
    }
}