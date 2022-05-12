
#include <string>
#include <fstream>
#include <iostream>

#include "Queue.h"
#include "Inventory.h"
#include "StringUtils.h"
#include "InventoryRecord.h"

Inventory::Inventory(std::string filePath) {
    printFile(filePath);
}

void Inventory::Start() {
    Queue<InventoryRecord> inventory = new Queue<InventoryRecord>();

    InventoryRecord recordOne = InventoryRecord(1, 12, 33.50, InventoryRecord::K);
    InventoryRecord recordTwo = InventoryRecord(2, 4, 12.30, InventoryRecord::K);
    InventoryRecord recordThree = InventoryRecord(1, 6, 33.50, InventoryRecord::P);
    InventoryRecord recordFour = InventoryRecord(2, 2, 12.30, InventoryRecord::P);

    inventory.Enqueue(&recordOne);
    inventory.Enqueue(&recordTwo);
    inventory.Enqueue(&recordThree);
    inventory.Enqueue(&recordFour);

    auto head = inventory.Dequeue();
    std::cout << "Head: " << head->purchaseType << " price: " << head->GetPrice() << " quantity: " << head->GetQuantity() << std::endl;
    head = inventory.Dequeue();
    std::cout << "Head: " << head->purchaseType << " price: " << head->GetPrice() << " quantity: " << head->GetQuantity() << std::endl;
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
        std::cout << StringUtils::split(line, " ")[0] << std::endl;
        std::cout << line << std::endl;
    }
}
