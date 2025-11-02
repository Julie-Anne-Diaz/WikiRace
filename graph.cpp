#include "graph.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>

WikiGraph::WikiGraph(){}
WikiGraph::WikiGraph(std::string filepath){makeGraph(filepath);}

bool WikiGraph::makeGraph(std::string filepath){
    //open file and check if successful
    std::ifstream file;
    file.open(filepath);
    if (!file){
        std::cout<<"problem opening";
        return false;
    }
    
    //read txt
    std::string line;
    std::string cur;
    while (std::getline(file, line)) {
        if (line.find("##-")==0){
            cur=line.substr(3);
        }
        else{
            adj[cur].push_back(line);
        }
    }
    file.close();
    return true;
}
int WikiGraph::BFS(std::string start, std::string end){
    return 0;
}
int WikiGraph::DFS(std::string start, std::string end){
    return 0;
}