#include "graph.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <iostream>
#include <set>
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
            std::getline(file, cur);
        }
        else{
            adj[cur].push_back(line);
        }
    }
    file.close();
    return true;
}
std::vector<std::string> WikiGraph::BFS(std::string start, std::string end){
    std::unordered_map<std::string,std::string> visited;
    std::queue<std::string> q;
    q.push(start);
    visited[start]="#start()";
    std::string cur;
    while (!q.empty()){
        cur = q.front();
        q.pop();
        if (cur==end){
            break;
        }
        for (std::string s : adj[cur]){
            if (!visited.count(s)){
                visited[s]=cur;
                q.push(s);
            }
        }
    }
    std::vector<std::string> path;
    while(cur!="#start()"){
        path.insert(path.begin(),cur);
        cur=visited[cur];
    }
    return path;
}
std::vector<std::string> WikiGraph::DFS(std::string start, std::string end){
    std::vector<std::string> path;
    return path;
}