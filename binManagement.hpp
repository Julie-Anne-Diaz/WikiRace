#pragma once

#include <string>
#include <vector>

struct BinEntry {
    std::string filename;
    std::string firstTitle;
};

std::string findBinForArticle(const std::vector<BinEntry>& bins, const std::string& title);
std::vector<BinEntry> loadIndex(const std::string& path);
std::string findArticleLine(const std::string& binPath, const std::string& title);
std::vector<std::string> parseLinks(const std::string& line);