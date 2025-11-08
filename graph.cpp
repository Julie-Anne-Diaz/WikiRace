#include "graph.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <iostream>
#include <set>
#include <queue>
#include <stack>

std::string toLower(std::string s) {
  std::string output;
    for(auto x:s){
        output.push_back(tolower(x));
    }
    return output;
}

std::vector<std::string> WikiGraph::BFS(std::string start, std::string end){
    std::unordered_map<std::string,std::string> visited;
    std::queue<std::string> q;
    q.push(start);
    visited[start] = "";
    std::string cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        if (toLower(cur)==toLower(end)) {
            break;
        }
        for (std::string s : adj[cur]) {
            if (!visited.count(s)){
                visited[s]=cur;
                q.push(s);
            }
        }
    }
    //check if no valid path for disconnected articles
    if (!visited.count(end)) {
        return {};
    }
    std::vector<std::string> path;
    cur = end;
    while (cur != "") {
        path.insert(path.begin(), cur);
        cur = visited[cur];
    }
    return path;
}

std::vector<std::string> WikiGraph::DFS(std::string start, std::string end){
    std::unordered_map<std::string,std::string> visited;
    std::stack<std::string> stk;
    stk.push(start);
    visited[start] = "";
    std::string cur;
    while (!stk.empty()) {
        cur = stk.top();
        stk.pop();
        if (toLower(cur)==toLower(end)) {
            break;
        }
        for (std::string s : adj[cur]) {
            if (!visited.count(s)){
                visited[s]=cur;
                stk.push(s);
            }
        }
    }
    //check if no valid path for disconnected articles
    if (!visited.count(end)) {
        return {};
    }
    std::vector<std::string> path;
    cur = end;
    while (cur != "") {
        path.insert(path.begin(), cur);
        cur = visited[cur];
    }
    return path;
}