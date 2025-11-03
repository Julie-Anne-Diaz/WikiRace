#include "graph.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>
#include <stack>
#include <queue>

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
        if (line==""){
            std::getline(file, cur)
        }
        else{
            adj[cur].push_back(line);
        }
    }
    file.close();
    return true;
}
int WikiGraph::BFS(std::string start, std::string end){
    int count = 0;
    std::stack<std::string> visited;
    std::queue q;
    q.push(start);
    while (!q.empty()){
        std::string cur = q.front();
        q.pop();
        count++;
        if (cur==end){
            break;
        }
        for (std::string s : adj[cur]){
            if (!visited.count(s)){
                visited.insert(s);
                q.push(s);
            }
        }
    }
    return count;
}
int WikiGraph::DFS(std::string start, std::string end){
    return 0;
}