#include <iostream>
#include <SFML/Graphics.hpp>
#incude "graph.hpp"

int main() {
    WikiGraph("filepath");
    int b = WikiGraph.BFS();
    int d = WikiGraph.DFS();
    if (b>d){
        std::cout<<"BFS wins with only "<<b<<" traversals compared to DFS's "<<d;
    }
    else if (b>d){
        std::cout<<"DFS wins with only "<<d<<" traversals compared to BFS's "<<b;
    }
    else{
        std::cout<<"BFS and DFS tied with "<<d<<" traversals";
    }
    return 0;
}