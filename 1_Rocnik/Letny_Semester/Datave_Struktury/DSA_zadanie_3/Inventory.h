


#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

class Inventory {
public:
    Inventory();
    void Start();

    void ConsumeInventoryFile(std::string filePath);

private:
    std::string readedText;

    void printFile(std::string filePath);
};

#endif