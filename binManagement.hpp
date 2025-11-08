#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct BinEntry {
    std::string filename;
    std::string firstTitle;
};

extern std::unordered_map<std::string, std::string> binLookup;
extern std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> binCache;

std::string findBinForArticle(const std::vector<BinEntry>& bins, const std::string& title);
std::vector<BinEntry> loadIndex(const std::string& path);
std::string findArticleLine(const std::string& binPath, const std::string& title);
std::vector<std::string> parseLinks(const std::string& line);

const std::vector<std::string>& getLinksCached(const std::string& binPath, const std::string& title);