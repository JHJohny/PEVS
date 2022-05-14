
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
    ConsumeInventoryFile();

    std::cout << "Item " << queOne.GetHead()->GetData()->GetItemType() << " Pur " << queOne.GetHead()->GetData()->GetPurchaseType() << " Quan " << queOne.GetHead()->GetData()->GetQuantity() << std::endl;

    auto item = queOne.GetHead()->GetData();
    std::cout << "ItemType " << item->GetItemType() << " PurchaseType " << item->GetPurchaseType() << " Quantity " << item->GetQuantity() << " Price " << item->GetPrice() << std::endl;
    auto itemTwo = queTwo.GetHead()->GetData();
    std::cout << "ItemType " << itemTwo->GetItemType() << " PurchaseType " << itemTwo->GetPurchaseType() << " Quantity " << itemTwo->GetQuantity() << " Price " << itemTwo->GetPrice() << std::endl;

    /*
    Queue<InventoryRecord> inventory = new Queue<InventoryRecord>();

    InventoryRecord recordOne = InventoryRecord(1, 'K', 12, 33.50);
    InventoryRecord recordTwo = InventoryRecord(2, 'K', 4, 12.30);
    InventoryRecord recordThree = InventoryRecord(1, 'P', 6, 33.50);
    InventoryRecord recordFour = InventoryRecord(2, 'P', 2, 12.30);

    inventory.Enqueue(&recordOne);
    inventory.Enqueue(&recordTwo);
    inventory.Enqueue(&recordThree);
    inventory.Enqueue(&recordFour);

    auto head = inventory.Dequeue();
    std::cout << "Head: " << head->purchaseType << " price: " << head->GetPrice() << " quantity: " << head->GetQuantity() << std::endl;
    head = inventory.Dequeue();
    std::cout << "Head: " << head->purchaseType << " price: " << head->GetPrice() << " quantity: " << head->GetQuantity() << std::endl;
    */
}

void Inventory::ConsumeInventoryFile() {
    // File reading stuff
    std::string line;
    std::ifstream myfile;
    myfile.open(FILE_PATH);

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
        InventoryRecord record = InventoryRecord(itemType, purchaseType, quantity, price);

        std::cout << itemType << " " << purchaseType << " " << quantity << " " << price << std::endl;

        switch (itemType) {
            case 1:
                queOne.Enqueue(record);
                break;
            case 2:
                queTwo.Enqueue(record);
                break;
            case 3:
                queThree.Enqueue(record);
                break;
        }
    }

}
