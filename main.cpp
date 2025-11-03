#include <iostream>
#include "graph.hpp"
#include <string>
#include <vector>

int main() {
    WikiGraph wiki = WikiGraph("filepath");
    
    int b = wiki.BFS("start page", "end page").size();
    int d = wiki.DFS("start page", "end page").size();
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