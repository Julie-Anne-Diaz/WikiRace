#include "traversals.hpp"
#include "binManagement.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

std::vector<std::string> BFS(const std::vector<BinEntry>& bins, const std::string& start, const std::string& end){

    std::queue<std::string> q;
    std::unordered_map<std::string, std::string> visited;

    q.push(start);
    visited[start] = "";
    std::string cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        if (cur == end) {
            break;
        }

        std::string bin = findBinForArticle(bins, cur);
        const auto& neighbors = getLinksCached("../" + bin, cur);

        for (std::string next : neighbors) {
            if (!visited.count(next)) {
                visited[next] = cur;
                q.push(next);
            }
        }
    }
    //check if no valid path for disconnected articles
    if (!visited.count(end)) {
        return {};
    }
    std::vector<std::string> path;
    std::cout << "bfs done" << std::endl;
    for (cur = end; cur != ""; cur = visited[cur]) {
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::string> DFS(const std::vector<BinEntry>& bins, const std::string& start, const std::string& end){

    std::unordered_map<std::string,std::string> visited;
    std::stack<std::string> stk;

    stk.push(start);
    visited[start] = "";
    std::string cur;
    while (!stk.empty()) {
        cur = stk.top();
        stk.pop();
        if (cur == end) {
            break;
        }

        std::string bin = findBinForArticle(bins, cur);
        const auto& neighbors = getLinksCached("../" + bin, cur);

        for (std::string next : neighbors) {
            if (!visited.count(next)) {
                visited[next] = cur;
                stk.push(next);
            }
        }
    }
    //check if no valid path for disconnected articles
    if (!visited.count(end)) {
        return {};
    }
    std::vector<std::string> path;
    for (cur = end; cur != ""; cur = visited[cur]) {
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());
    return path;
}