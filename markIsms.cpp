#include "graph.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>
#include <set>


void processText(std::string filepath){
    std::ifstream file;
    file.open(filepath);
    if (!file){
        std::cout<<"problem opening";
        return false;
    }
    
    //read txt and place words that start with -- in a set
    std::string line;
    std::set ism;
    while (std::getline(file, line)) {
        if (line.find("--")==0){
            ism.insert(line.substr(1));
        }
    }
    file.close();

    //write new file with labeled --
    file.open(filepath);
    std::ofstream newFile;
    newFile.open("new file");
    while (std::getline(file, line)) {
        if (line.find("-"==0 && !ism.count(line))){
            newFile<<"##"<<line;
        }
        else{
            newFile<<line;
        }
    }
    file.close();
    newFile.close();
}