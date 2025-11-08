#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "traversals.hpp"
#include "binManagement.hpp"

std::vector<BinEntry> bindex = loadIndex("../bin_index.txt");

void newText(std::string& s, char uni) {
    s=s.substr(0, s.length()-1);
    if (uni == '\b') // Backspace
    {
        if (!s.empty())
        {
            s=s.substr(0, s.length()-1);
        }
    }
    else if (uni >= 32 && uni <= 126) // Printable ASCII characters
    {
        s += uni;
    }
    s+="|";
}

void makeWindow(std::string fontPath, std::string textPath) {
    sf::Font font;

    //EDIT THIS PATH @BMAN
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    //start input outline
    sf::RectangleShape outline1({225,25});
    outline1.setFillColor(sf::Color::Black);
    outline1.setPosition({25.f, 50.f});
    outline1.setOutlineColor(sf::Color::White);
    outline1.setOutlineThickness(5);

    //end input outline
    sf::RectangleShape outline2({225,25});
    outline2.setFillColor(sf::Color::Black);
    outline2.setPosition({350.f, 50.f});
    outline2.setOutlineColor(sf::Color::White);
    outline2.setOutlineThickness(5);

    //displays start input
    std::string s="";
    sf::Text start;
    start.setFont(font);
    start.setString(s);
    start.setPosition(30,52);
    start.setCharacterSize(15);

    //displays end input
    std::string e="";
    sf::Text end;
    end.setFont(font);
    end.setString(e);
    end.setPosition(355,52);
    end.setCharacterSize(15);

    //BFS path outline
    sf::RectangleShape path1({250,270});
    path1.setFillColor(sf::Color::Black);
    path1.setPosition({25,105});
    path1.setOutlineColor(sf::Color::White);
    path1.setOutlineThickness(5);

    //DFS path outline
    sf::RectangleShape path2({250,270});
    path2.setFillColor(sf::Color::Black);
    path2.setPosition({325,105});
    path2.setOutlineColor(sf::Color::White);
    path2.setOutlineThickness(5);

    //top bound
    sf::RectangleShape top({600,100});
    top.setFillColor(sf::Color::Black);
    top.setPosition({0,0});

    //bottom bound
    sf::RectangleShape bot({600,270});
    bot.setFillColor(sf::Color::Black);
    bot.setPosition({0,380});

    //BFS path text
    std::string p1="";
    sf::Text ptext1;
    ptext1.setFont(font);
    ptext1.setString(p1);
    ptext1.setPosition(30,105);
    ptext1.setCharacterSize(15);

    //DFS path text
    std::string p2="";
    sf::Text ptext2;
    ptext2.setFont(font);
    ptext2.setString(p2);
    ptext2.setPosition(330,105);
    ptext2.setCharacterSize(15);

    //arrow
    sf::CircleShape arrowtip(20.f, 3);
    arrowtip.setFillColor(sf::Color::White);
    arrowtip.setRotation(90);
    arrowtip.setPosition({330,45});
    sf::RectangleShape arrowbutt({30,20});
    arrowbutt.setFillColor(sf::Color::White);
    arrowbutt.setPosition({280.f, 55.f});
    sf::Text button;
    button.setFont(font);
    button.setString("");
    button.setCharacterSize(15);
    button.setPosition(283,55);
    button.setFillColor(sf::Color::Black);

    //Title
    std::string displayText = "WIKI RACE";
    sf::Text text;
    text.setFont(font);
    text.setString(displayText);
    text.setPosition(225,0);

    //mini start text
    sf::Text text1;
    text1.setFont(font);
    text1.setString("start");
    text1.setPosition(25,25);
    text1.setCharacterSize(15);

    //mini end text
    sf::Text text2;
    text2.setFont(font);
    text2.setString("end");
    text2.setPosition(550,25);
    text2.setCharacterSize(15);

    std::vector<std::string> BFSpath;
    std::vector<std::string> DFSpath;

    std::string* ptr;
    sf::RenderWindow window(sf::VideoMode(600, 400), "Wiki Race");
    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if (!s.empty() && s!="|" && !e.empty() && e!="|") {
                arrowtip.setFillColor(sf::Color::Green);
                arrowbutt.setFillColor(sf::Color::Green);
                button.setString("start");
            }
            else {
                arrowtip.setFillColor(sf::Color::White);
                arrowbutt.setFillColor(sf::Color::White);
                button.setString("");
            }
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (ptr) {
                    newText(*ptr,static_cast<char>(event.text.unicode));
                }
                start.setString(s);
                end.setString(e);
            }
            //25 50, 350 50 w=225 h=25
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (ptr == &s && !s.empty() && s.back() == '|') {
                    s.pop_back();
                    start.setString(s);
                }
                else if (ptr == &e && !e.empty() && e.back() == '|') {
                    e.pop_back();
                    end.setString(e);
                }

                if (event.mouseButton.x>25 && event.mouseButton.x<250 && event.mouseButton.y>50 && event.mouseButton.y<75) {
                    ptr = &s;
                    s+="|";
                    start.setString(s);
                }
                else if (event.mouseButton.x>350 && event.mouseButton.x<575 && event.mouseButton.y>50 && event.mouseButton.y<75) {
                    ptr = &e;
                    e+="|";
                    end.setString(e);
                }
                else if (button.getString()=="start" && event.mouseButton.x>280 && event.mouseButton.x<330 && event.mouseButton.y>50 && event.mouseButton.y<85) {
                    if (ptr==&s) {
                        s=s.substr(0, s.length()-1);
                        start.setString(s);
                    }
                    else if (ptr==&e) {
                        e=e.substr(0, e.length()-1);
                        end.setString(e);
                    }
                    ptr=nullptr;
                    ptext1.setString("Loading...");
                    ptext2.setString("Loading...");
                    button.setString("");
                    arrowtip.setFillColor(sf::Color::White);
                    arrowbutt.setFillColor(sf::Color::White);
                    window.clear();
                    window.draw(text);
                    window.draw(outline1);
                    window.draw(outline2);
                    window.draw(path1);
                    window.draw(path2);
                    window.draw(text1);
                    window.draw(text2);
                    window.draw(arrowtip);
                    window.draw(arrowbutt);
                    window.draw(button);
                    window.draw(start);
                    window.draw(end);
                    window.draw(ptext1);
                    window.draw(ptext2);
                    window.display();
                    //variable names are s and e
                    BFSpath = BFS(bindex, s, e); //change to BFS(s,e)
                    DFSpath = DFS(bindex, s, e); //change to DFS(s,e)
                    for (std::string i : BFSpath) {
                        p1+=i+"\n";
                    }
                    for (std::string i : DFSpath) {
                        p2+=i+"\n";
                    }
                    //15 total lines
                    ptext1.setString(p1);
                    ptext2.setString(p2);
                }
                else {
                    ptr=nullptr;
                }
            }
            if (event.type==sf::Event::MouseWheelScrolled ) {
                if (event.mouseWheelScroll.x>25 && event.mouseWheelScroll.x<275 && event.mouseWheelScroll.y>105 && event.mouseWheelScroll.y<375 ) {
                    if (ptext1.getGlobalBounds().top+ptext1.getGlobalBounds().height>372&&event.mouseWheelScroll.delta<0) {
                        ptext1.setPosition(ptext1.getPosition().x,ptext1.getPosition().y+event.mouseWheelScroll.delta);
                    }
                    if (ptext1.getGlobalBounds().top<112&&event.mouseWheelScroll.delta>0) {
                        ptext1.setPosition(ptext1.getPosition().x,ptext1.getPosition().y+event.mouseWheelScroll.delta);
                    }
                }
                else if (event.mouseWheelScroll.x>325 && event.mouseWheelScroll.x<575 && event.mouseWheelScroll.y>105 && event.mouseWheelScroll.y<375 ) {
                    if (ptext2.getGlobalBounds().top+ptext2.getGlobalBounds().height>372&&event.mouseWheelScroll.delta<0) {
                        ptext2.setPosition(ptext2.getPosition().x,ptext2.getPosition().y+event.mouseWheelScroll.delta);
                    }
                    if (ptext2.getGlobalBounds().top<112&&event.mouseWheelScroll.delta>0) {
                        ptext2.setPosition(ptext2.getPosition().x,ptext2.getPosition().y+event.mouseWheelScroll.delta);
                    }
                }
            }
        }

        window.clear();
        window.draw(path1);
        window.draw(path2);
        window.draw(ptext1);
        window.draw(ptext2);
        window.draw(top);
        window.draw(bot);
        window.draw(text);
        window.draw(outline1);
        window.draw(outline2);
        window.draw(text1);
        window.draw(text2);
        window.draw(arrowtip);
        window.draw(arrowbutt);
        window.draw(button);
        window.draw(start);
        window.draw(end);
        window.display();
    }
    return;
}