#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

class WikiGraph{
    std::map<std::string,std::vector<std::string>> adj;
public:
    WikiGraph();
    WikiGraph(std::string filepath);
    bool makeGraph(std::string filepath);
    int BFS(std::string start, std::string end);
    int DFS(std::string start, std::string end);
};


