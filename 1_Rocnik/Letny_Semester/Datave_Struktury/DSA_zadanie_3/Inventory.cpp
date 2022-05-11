
#include <string>
#include <fstream>
#include <iostream>

#include "Inventory.h"

Inventory::Inventory(std::string filePath) {
    printFile(filePath);
}

void Inventory::Start() {

}

void Inventory::printFile(std::string filePath) {
    std::string line;
    std::ifstream myfile;
    myfile.open(filePath);

    if(!myfile.is_open()) {
        perror("Subor sa nepodarilo otvorit!");
        exit(EXIT_FAILURE);
    }
    while(getline(myfile, line)) {
        std::cout << line << std::endl;
    }
}
