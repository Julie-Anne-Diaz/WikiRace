#include <iostream>
#include "graph.hpp"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

int main() {
    WikiGraph wiki = WikiGraph("sampleText.txt");
    std::string displayText;
    
    size_t b = wiki.BFS("John Horton Conway", "John von Neumann").size();
    size_t d = wiki.DFS("John Horton Conway", "John von Neumann").size();
    if (b > d){
        displayText = "BFS wins with only " + std::to_string(b) +" traversals compared to DFS's " + std::to_string(d);
    }
    else if (b<d){
        displayText = "DFS wins with only " + std::to_string(d) + " traversals compared to BFS's " + std::to_string(b);
    }
    else{
        displayText = "BFS and DFS tied with " + std::to_string(d) + " traversals";
    }

    sf::Font font;
    if (!font.loadFromFile("aovel-sans-rounded-font/AovelSansRounded-rdDL.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(displayText);

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
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