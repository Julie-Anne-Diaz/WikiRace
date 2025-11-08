#include "binManagement.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::unordered_map<std::string, std::string> binLookup;
std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> binCache;

std::string findBinForArticle(const std::vector<BinEntry>& bins, const std::string& title) {
    int low = 0, high = bins.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (title >= bins[mid].firstTitle) {
            if (mid + 1 == bins.size() || title < bins[mid + 1].firstTitle) {
                return bins[mid].filename;
            }
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return bins.front().filename;
}

std::vector<BinEntry> loadIndex(const std::string& path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Failed to open file " << path << std::endl;
    }
    std::vector<BinEntry> bins;
    std::string line;

    while (std::getline(fin, line)) {
        size_t separate = line.find('|');
        if (separate == std::string::npos) continue;
        bins.push_back({line.substr(0, separate), line.substr(separate + 1)});
    }

    return bins;
}

std::string findArticleLine(const std::string& binPath, const std::string& title) {
    std::ifstream fileInput(binPath);
    std::string line;

    while (std::getline(fileInput, line)) {
        size_t separate = line.find("||");
        std::string name = (separate == std::string::npos) ? line : line.substr(0, separate);
        if (name == title) {
            return line;
        }
    }

    return "";
}

std::vector<std::string> parseLinks(const std::string& line) {
    std::vector<std::string> links;
    size_t start = line.find("||");
    if (start == std::string::npos) return links;

    // skip first "||"
    start += 2;

    size_t end;
    while ((end = line.find("||", start)) != std::string::npos) {
        links.push_back(line.substr(start, end - start));
        start = end + 2;
    }

    // add the last link if any
    if (start < line.size()) {
        links.push_back(line.substr(start));
    }
    return links;
}

const std::vector<std::string>& getLinksCached(const std::string& binPath, const std::string& title) {
    // if bin not loaded yet, load entire file
    if (!binCache.count(binPath)) {
        std::ifstream fin(binPath);
        if (!fin.is_open()) {
            std::cerr << "Failed to open " << binPath << std::endl;
            static std::vector<std::string> empty;
            return empty;
        }
        std::string line;
        std::unordered_map<std::string, std::vector<std::string>> articleMap;
        while (std::getline(fin, line)) {
            size_t sep = line.find("||");
            std::string name = (sep == std::string::npos) ? line : line.substr(0, sep);
            articleMap[name] = parseLinks(line);
        }
        binCache[binPath] = std::move(articleMap);
    }

    // Lookup requested article
    auto& articleMap = binCache[binPath];
    auto it = articleMap.find(title);
    if (it != articleMap.end()) {
        return it->second;
    }

    static std::vector<std::string> empty;
    return empty;
}