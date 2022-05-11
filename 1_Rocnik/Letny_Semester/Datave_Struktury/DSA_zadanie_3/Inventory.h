
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

class Inventory {
public:
    Inventory(std::string filePath);
    void Start();

private:
    std::string readedText;

    void printFile(std::string filePath);
};

#endif