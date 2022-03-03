#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <map>

struct Edge {
    int source, destination;
};

struct Vertex {
    int value;
};

template<typename T>
class Directed_Graph {

    private:
        std::map<T, std::map<T,int>> *successor = new std::map<T, std::map<T,int>>(); 
        std::map<T, std::map<T,int>> *predecessor = new std::map<T, std::map<T,int>>();

        int edges = 0;

    public:

        Directed_Graph(Edge const &edges, int n) {

            
        }

};


#endif