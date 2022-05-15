
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
    ConsumeInventoryFile(FILE_PATH);

}

void Inventory::PrintInventoryStatistics(Queue<InventoryRecord> *que, bool printSummary) {
    auto tempHead = que->GetHead(); // Temp head is required so we can get back once we will loop trough everything

    // Looping trough all nodes
    while(que->GetHead() != nullptr) {
        std::cout << que->GetHead()->GetData()->GetQuantity() << " units - " << que->GetHead()->GetData()->GetPrice() << " EUR" << std::endl;
        que->SetHead(que->GetHead()->GetNext());
    }

    que->SetHead(tempHead); // Setting head back - so it will looks like it's been never looped torugh

    // TODO - make summary feature
}

void Inventory::Buy() {
    bool wasPolozkaChoosenCorrectly = false;
    int polozka;
    int pocetKs;
    float cena;

    // Getting the users input
    while(!wasPolozkaChoosenCorrectly) {
        std::cout << "Zadaj polozku, pocet ks, cenu:" << std::endl;
        std::cin >> polozka;
        std::cin >> pocetKs;
        std::cin >> cena;
        auto *record = new InventoryRecord(polozka, "K", pocetKs, cena);

        // Because we have only 3 polozky
        switch (polozka) {
            case 1:
                wasPolozkaChoosenCorrectly = true;
                queOne.Enqueue(record);
                break;
            case 2:
                wasPolozkaChoosenCorrectly = true;
                queTwo.Enqueue(record);
                break;
            case 3:
                wasPolozkaChoosenCorrectly = true;
                queThree.Enqueue(record);
                break;
            default:
                std::cout << "Nespravna polozka, prosim zvol 1 / 2 / 3" << std::endl;
                polozka = 0;
                pocetKs = 0;
                cena = 0.0;
        }
    }

}

void Inventory::ConsumeInventoryFile(std::string filepath) {
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

        //std::cout << itemType << " " << purchaseType << " " << quantity << " " << price << std::endl;

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
