#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

struct BinRange {
    std::string filename;
    std::string firstTitle;
};

int main() {
    const int NUM_BINS = 467;
    std::vector<BinRange> bins;
    bins.reserve(NUM_BINS);

    for (int i = 1; i <= NUM_BINS; i++) {
        std::ostringstream filename;
        filename << "articles/bin" << std::setw(3) << std::setfill('0') << i << ".txt";
        std::ifstream fin(filename.str());
        if (!fin.is_open()) {
            std::cerr << "Warning: could not open " << filename.str() << '\n';
            continue;
        }

        std::string firstLine;
        if (std::getline(fin, firstLine)) {
            // trim everything after the first "||"
            size_t pos = firstLine.find("||");
            if (pos != std::string::npos) {
                firstLine = firstLine.substr(0, pos);
            }

            // trim whitespace
            while (!firstLine.empty() && (firstLine.back() == '\r' || firstLine.back() == '\n')) {
                firstLine.pop_back();
            }
            while (!firstLine.empty() && std::isspace(firstLine.front())) {
                firstLine.erase(firstLine.begin());
            }

            bins.push_back({filename.str(), firstLine});
        }
        else {
            std::cerr << "Warning: " << filename.str() << " is empty.\n";
        }
    }

    std::ofstream fout("./bin_index.txt");
    if (!fout.is_open()) {
        std::cerr << "Could not create bin_index.txt\n";
        return 1;
    }

    for (const auto& bin : bins) {
        fout << bin.filename << '|' << bin.firstTitle << '\n';
    }

    std::cout << "Index file created successfully\n";
    return 0;
}
