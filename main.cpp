#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "graph.hpp"

int main() {
    sf::Font font;

    if (!font.loadFromFile("..\\roboto\\Roboto-Black.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    std::string displayText = "press any button to begin loading the graph";
    sf::Text text;
    text.setFont(font);
    text.setString(displayText);

    //displays start input
    std::string s="";
    sf::Text start;
    start.setFont(font);
    start.setString(s);
    start.setPosition(0,100);

    //displays end input
    std::string e="";
    sf::Text end;
    end.setFont(font);
    end.setString(e);
    end.setPosition(0,100);

    //displays path at the end
    sf::Text path;
    path.setFont(font);
    path.setString("");
    path.setPosition(0,200);

    int count=0;
    std::vector<std::string> BFSpath;
    std::vector<std::string> DFSpath;
    int pos=0;

    sf::RenderWindow window(sf::VideoMode(600, 400), "Test Window");
    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                //first button press loads the map
                if (count==0) {
                    displayText="loading...";
                    text.setString(displayText);
                    window.clear();
                    window.draw(text);
                    window.display();
                    //EDIT THIS PATH BMAN
                    wiki = WikiGraph("../sampleText.txt");
                    displayText="input your starting wikipage";
                    text.setString(displayText);
                    count++;
                }
                //input starting wikipage
                else if (count==1) {
                    if (event.text.unicode == '\b') // Backspace
                    {
                        if (!s.empty())
                        {
                            s=s.substr(0, s.length()-1);
                        }
                    }
                    else if (event.text.unicode==13) {
                        displayText="input your ending wikipage";
                        text.setString(displayText);
                        start.setString("");
                        count++;
                        continue;
                    }
                    else if (event.text.unicode >= 32 && event.text.unicode <= 126) // Printable ASCII characters
                    {
                        s += static_cast<char>(event.text.unicode);
                    }
                    start.setString(s+"|");
                }
                //input ending wikipage
                else if (count==2) {
                    if (event.text.unicode == '\b') // Backspace
                    {
                        if (!e.empty())
                        {
                            e=e.substr(0, e.length()-1);
                        }
                    }
                    //once entered run BFS DFS
                    else if (event.text.unicode==13) {
                        displayText="Running BFS and DFS...";
                        text.setString(displayText);
                        end.setString("");
                        count++;

                        window.clear();
                        window.draw(text);
                        window.draw(end);
                        window.display();

                        BFSpath=wiki.BFS(s, e);
                        DFSpath=wiki.DFS(s, e);
                        size_t b = BFSpath.size();
                        size_t d = DFSpath.size();

                        if (b < d) {
                            displayText = "BFS wins with only " + std::to_string(b) +" traversals\ncompared to DFS's " + std::to_string(d);
                        }
                        else if (b > d) {
                            displayText = "DFS wins with only " + std::to_string(d) + " traversals\ncompared to BFS's " + std::to_string(b);
                        }
                        else {
                            displayText = "BFS and DFS tied with " + std::to_string(d) + " traversals";
                        }
                        displayText+="\n\nuse the arrow keys to navigate the path\n\n";
                        path.setString(s);
                        text.setString(displayText);
                        continue;
                    }
                    else if (event.text.unicode >= 32 && event.text.unicode <= 126) // Printable ASCII characters
                    {
                        e += static_cast<char>(event.text.unicode);
                    }
                    end.setString(e+"|");
                }
            }
            //Used at the end to navigate shortest path
            if (event.type == sf::Event::KeyPressed) {
                if (count==3) {
                    if (BFSpath.size() < DFSpath.size()) {
                        if(event.key.code == sf::Keyboard::Right && pos<BFSpath.size()-1) {
                            pos++;
                            path.setString(BFSpath[pos]);
                        }
                        if(event.key.code == sf::Keyboard::Left && pos>0) {
                            pos--;
                            path.setString(BFSpath[pos]);
                        }
                    }
                    else {
                        if(event.key.code == sf::Keyboard::Right && pos<DFSpath.size()-1) {
                            pos++;
                            path.setString(DFSpath[pos]);
                        }
                        if(event.key.code == sf::Keyboard::Left && pos>0) {
                            pos--;
                            path.setString(DFSpath[pos]);
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(text);
        window.draw(start);
        window.draw(path);
        window.draw(end);
        window.display();
    }






    return 0;
}