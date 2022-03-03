#include <iostream>
#include <vector>

struct Edge {
    int source, destination;
};

class Graph {
    public:
        std::vector<std::vector<int>> adjList;

        Graph(std::vector<Edge> const &edges, int n){
            adjList.resize(n);

            for (auto &edge : edges) {
                adjList[edge.source].push_back(edge.destination);


            }
        }
};

void printGraph(Graph const &graph, int n) {

    for(int i = 0; i < n; i++) {
        std::cout << i << " --> ";

        for (int v : graph.adjList[i]) {
            std::cout << v << " ";
        }

        std::cout << std::endl;
    }
}
