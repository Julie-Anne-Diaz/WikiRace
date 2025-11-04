#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "graph.hpp"

int main() {
    WikiGraph wiki = WikiGraph("C:/Users/Bradley Cederholm/CLionProjects/WikiRace/sampleText.txt");
    std::string displayText;

    std::vector<std::string> BFSpath = wiki.BFS("Insurance", "Airbus A300");
    std::vector<std::string> DFSpath = wiki.DFS("Insurance", "Airbus A300");

    size_t b = BFSpath.size();
    size_t d = DFSpath.size();

    if (b < d) {
        displayText = "BFS wins with only " + std::to_string(b) +" traversals\ncompared to DFS's " + std::to_string(d);
        for (std::string s : BFSpath) {
            displayText += "\n" + s;
        }
    }
    else if (b > d) {
        displayText = "DFS wins with only " + std::to_string(d) + " traversals\ncompared to BFS's " + std::to_string(b);
        for (std::string s : DFSpath) {
            displayText += "\n" + s;
        }
    }
    else {
        displayText = "BFS and DFS tied with " + std::to_string(d) + " traversals";
        for (std::string s : BFSpath) {
            displayText += "\n" + s;
        }
    }

    sf::Font font;
    if (!font.loadFromFile("C:/Users/Bradley Cederholm/CLionProjects/WikiRace/roboto/Roboto-Black.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(displayText);

    sf::RenderWindow window(sf::VideoMode(600, 400), "Test Window");
    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }
    return 0;
}