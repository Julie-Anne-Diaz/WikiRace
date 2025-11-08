#include "binManagement.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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