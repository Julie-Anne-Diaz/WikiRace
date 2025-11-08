#include <bits/stdc++.h>

/*
 / Created By Bradley Cederholm on 11/4/2025.
 / Batch article storage into a preset number of bins which are alphabetically sorted.
 / Line format: Article||Link1||Link2||...
*/

std::string toLower(std::string s) {
    std::string output;
    for (auto x : s)
        output.push_back(std::tolower(static_cast<unsigned char>(x)));
    return output;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const std::string inputFilename = "output8.txt";
    const std::string outputDir = "C:/Users/Bradley Cederholm/CLionProjects/WikiRace/articles/";
    const int BIN_SIZE = 15000;

    std::ifstream infile(inputFilename);
    if (!infile.is_open()) {
        std::cerr << "Error: " << inputFilename << '\n';
        return 0;
    }

    //read entire file, store articles
    std::string line;
    std::string curArticle;
    std::vector<std::string> links;
    std::vector<std::pair<std::string, std::vector<std::string>>> articles;

    while (std::getline(infile, line)) {
        if (line.empty()) {
            if (!curArticle.empty()) {
                articles.emplace_back(curArticle, links);
                curArticle.clear();
                links.clear();
            }
            continue;
        }

        if (curArticle.empty()) {
            curArticle = line;
        }
        else {
            links.push_back(line);
        }
    }

    infile.close();

    // inline lambda comparator B)
    std::sort(articles.begin(), articles.end(), [](const auto &a, const auto &b) {
            return a.first < b.first;
    });

    //place articles into bins
    int totalArticles = articles.size();
    int binCount = (totalArticles + BIN_SIZE - 1) / BIN_SIZE;

    for (int i = 0; i < binCount; ++i) {
        int start = i * BIN_SIZE;
        int end = std::min(start + BIN_SIZE, totalArticles);

        std::ostringstream filename;
        // file format for output is bin001.txt, bin342.txt, etc.
        filename << outputDir << "bin" << std::setw(3) << std::setfill('0') << (i + 1) << ".txt";

        std::ofstream out(filename.str());
        if (!out.is_open()) {
            std::cerr << "Error creating " << filename.str() << '\n';
            continue;
        }

        for (int j = start; j < end; ++j) {
            out << articles[j].first; // title
            for (const auto &link : articles[j].second) {
                out << "||" << link;
            }
            out << '\n';
        }

        out.close();
        std::cout << "Wrote " << filename.str() << " (" << (end - start) << " articles)\n";
    }

    std::cout << "All articles successfully batched into " << binCount << " files.\n";
    return 0;
}