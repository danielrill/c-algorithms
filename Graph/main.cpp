#include "adjacency_list_graph.cpp"

int main() {

    int n = 5;
    std::vector<Edge> edges = {  {0,1}, {1,2}, {2,1}, {3,2}, {4,5}  };

    Graph graph(edges, n);

    printGraph(graph, n);
}