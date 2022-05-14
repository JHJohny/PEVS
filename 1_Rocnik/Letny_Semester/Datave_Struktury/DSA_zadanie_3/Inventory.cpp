
#define FILE_PATH "./Inventory.txt"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Queue.h"
#include "Inventory.h"
#include "StringUtils.h"
#include "InventoryRecord.h"

Inventory::Inventory() {
    queOne = new Queue<InventoryRecord>;
    queTwo = new Queue<InventoryRecord>;
    queThree = new Queue<InventoryRecord>;
}

void Inventory::Start() {
    ConsumeInventoryFile(FILE_PATH,
                         &queOne,
                         &queTwo,
                         &queThree);

    /*
    auto item = queOne.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;
    item = queOne.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;
    item = queOne.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;

    item = queTwo.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;
    item = queTwo.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;
    item = queTwo.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;

    item = queThree.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;
    item = queThree.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;
    item = queThree.Dequeue();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;
    */

}

void Inventory::ConsumeInventoryFile(std::string filepath,
                                     Queue<InventoryRecord> *queOne,
                                     Queue<InventoryRecord> *queTwo,
                                     Queue<InventoryRecord> *queThree) {
    // File reading stuff
    std::string line;
    std::ifstream myfile;
    myfile.open(filepath);

    // File check stuff
    if(!myfile.is_open()) {
        perror("Subor sa nepodarilo otvorit!");
        exit(EXIT_FAILURE);
    }

    // Actuall que filling
    while(getline(myfile, line)) {
        std::vector<std::string> splittedText = StringUtils::split(line, " ");

        int itemType = std::stoi(splittedText[0]);
        std::string purchaseType = splittedText[1];
        int quantity = std::stoi(splittedText[2]);
        double price = std::stod(splittedText[3]);
        auto *record = new InventoryRecord(itemType, purchaseType, quantity, price);

        std::cout << itemType << " " << purchaseType << " " << quantity << " " << price << std::endl;

        switch (itemType) {
            case 1:
                queOne->Enqueue(record);
                break;
            case 2:
                queTwo->Enqueue(record);
                break;
            case 3:
                queThree->Enqueue(record);
                break;
        }

    }

}
