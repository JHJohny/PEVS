
#define FILE_PATH_INPUT "./Inventory.txt"
#define FILE_PATH_OUTPUT "./Output.txt"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "Queue.h"
#include "Inventory.h"
#include "StringUtils.h"
#include "InventoryRecord.h"

Inventory::Inventory() {
    queOne = new Queue<InventoryRecord>;
    queTwo = new Queue<InventoryRecord>;
    queThree = new Queue<InventoryRecord>;
}

[[noreturn]] void Inventory::Start() {
    char usersChoice;

    std::cout << "<i>nventar ..... vypíš inventár pre číslo položky\n"
                 "<k>up .......... nákup X kusov pre číslo položky\n"
                 "<p>redaj ....... predaj X kusov pre číslo položky\n"
                 "<n>acitaj ...... načítaj inventár zo súboru\n"
                 "<s>tatistika ... vypíš štatistiku zbožia\n"
                 "<w>rite ........ zapíš inventár do súboru\n"
                 "<e>exit ........ ukončiť program\n";
    std::cout.flush();

    while (true) {
        scanf("%c", &usersChoice);
        switch (usersChoice) {
            case 'i':
                if(wasInventoryAlreadyLoaded){
                    PrintInventoryUserInput();
                }else
                {
                    std::cout << "Najprv nacitaj inventar zo suboru!" << std::endl;
                }
                break;
            case 'k':
                Buy();
                break;
            case 'p':
                if(wasInventoryAlreadyLoaded){
                    Sell();
                }else
                {
                    std::cout << "Najprv nacitaj inventar zo suboru!" << std::endl;
                }
                break;
            case 'n':
                ConsumeInventoryFile(FILE_PATH_INPUT);
                break;
            case 's':
                if(wasInventoryAlreadyLoaded){
                    PrintGeneralStatistics();
                }else
                {
                    std::cout << "Najprv nacitaj inventar zo suboru!" << std::endl;
                }
                break;
            case 'w':
                if(wasInventoryAlreadyLoaded){
                    WriteInventoryToFile(FILE_PATH_OUTPUT);
                }else
                {
                    std::cout << "Najprv nacitaj inventar zo suboru!" << std::endl;
                }
                break;
            case 'e':
                exit(EXIT_SUCCESS);
        }
    }
}

void Inventory::PrintInventoryUserInput() {
    int polozka;
    std::cout << "Pre ktoru polozku: ";
    std::cin >> polozka;

    switch (polozka) {
        case 1:
            PrintInventoryStatistics(&queOne, false);
            break;
        case 2:
            PrintInventoryStatistics(&queTwo, false);
            break;
        case 3:
            PrintInventoryStatistics(&queThree, false);
            break;
    }
}

void Inventory::PrintInventoryStatistics(Queue<InventoryRecord> *que, bool printSummary) {
    auto tempHead = que->GetHead(); // Temp head is required so we can get back once we will loop trough everything
    double summary = 0;

    std::cout << "Item " << que->GetHead()->GetData()->GetItemType() << std::endl;

    // Looping trough all nodes
    while(que->GetHead() != nullptr) {
        summary += (que->GetHead()->GetData()->GetQuantity() * que->GetHead()->GetData()->GetPrice());
        std::cout << que->GetHead()->GetData()->GetQuantity() << " units - " << que->GetHead()->GetData()->GetPrice() << " EUR" << std::endl;
        que->SetHead(que->GetHead()->GetNext());
    }

    if(printSummary) {
        std::cout << "Sumar - " << summary << std::endl;
    }

    que->SetHead(tempHead); // Setting head back - so it will looks like it's been never looped torugh
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

        UpdateInventoryStatus(InventoryRecord(polozka, "K", pocetKs, cena));

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

    std::cout << "Nakup prebehol OK" << std::endl;
}

void Inventory::Sell() {
    bool wasPolozkaChoosenCorrectly = false;
    int polozka;
    int pocetKS;

    while (!wasPolozkaChoosenCorrectly) {
        std::cout << "Zadaj polozku, pocet ks:" << std::endl;
        std::cin >> polozka;
        std::cin >> pocetKS;

        if(polozka == 1 || polozka == 2 || polozka == 3) {
            wasPolozkaChoosenCorrectly = true;
            MakeSellForInventory(polozka, pocetKS);
        } else {
            std::cout << "Nespravna polozka, prosim zvol 1 / 2 / 3" << std::endl;
            polozka = 0;
        }
    }
}

void Inventory::MakeSellForInventory(int polozka, int units) {
    int unitsRemainingToSell = units;
    std::map<double, int> invent;

    Queue<InventoryRecord> que;
    switch (polozka) {
        case 1:
            invent = inventoryOneStatus;
            que = queOne;
            break;
        case 2:
            invent = inventoryTwoStatus;
            que = queTwo;
            break;
        case 3:
            invent = inventoryThreeStatus;
            que = queThree;
            break;
    }

    //Checking if there is enough supply
    int totalUnitAvailable = 0;
    for (auto const& x : invent)
    {
        totalUnitAvailable += x.second;
    }

    if(totalUnitAvailable < units) {
        std::cout << "Tolko polozok sa v inventary ani nenachadza na predaj";
        return;
    }

    auto tempHead = que.GetHead(); // Temp head is required so we can get back once we will loop trough everything

    // Looping trough all nodes
    while(que.GetHead() != nullptr && unitsRemainingToSell > 0) {
        auto record = que.GetHead()->GetData();
        if(record->GetPurchaseType() == "K") {
            int unitsLeftForThisPrice = invent[record->GetPrice()];
            int unitsCurrentlySelling = 0;

            if (unitsRemainingToSell == unitsLeftForThisPrice) {
                unitsCurrentlySelling = unitsRemainingToSell;
                unitsRemainingToSell = 0;
            } else if (unitsRemainingToSell > unitsLeftForThisPrice) {
                unitsCurrentlySelling = unitsLeftForThisPrice;
                unitsRemainingToSell -= unitsLeftForThisPrice;
            } else {
                unitsCurrentlySelling = unitsRemainingToSell;
                unitsRemainingToSell = 0;
            }

            std::cout << "Uspesne sa predala polozka " << polozka << " za cenu " << record->GetPrice() << " pocet kusov - " << unitsCurrentlySelling << std::endl;
            auto newSaleRecord = new InventoryRecord(polozka, "P", unitsCurrentlySelling, record->GetPrice());
            que.Enqueue(newSaleRecord);

            UpdateInventoryStatus(InventoryRecord(polozka, "P", unitsCurrentlySelling, record->GetPrice()));
        }

        que.SetHead(que.GetHead()->GetNext());
    }

    que.SetHead(tempHead); // Setting head back - so it will looks like it's been never looped torugh
}

void Inventory::UpdateInventoryStatus(InventoryRecord record) {
    switch (record.GetItemType()) {
        case 1:
            if(record.GetPurchaseType() == "K") {
                inventoryOneStatus[record.GetPrice()] += record.GetQuantity();
            } else {
                inventoryOneStatus[record.GetPrice()] -= record.GetQuantity();
            }
            break;
        case 2:
            if(record.GetPurchaseType() == "K") {
                inventoryTwoStatus[record.GetPrice()] += record.GetQuantity();
            } else {
                inventoryTwoStatus[record.GetPrice()] -= record.GetQuantity();
            }
            break;
        case 3:
            if(record.GetPurchaseType() == "K") {
                inventoryThreeStatus[record.GetPrice()] += record.GetQuantity();
            } else {
                inventoryThreeStatus[record.GetPrice()] -= record.GetQuantity();
            }
            break;
    }
}

void Inventory::PrintGeneralStatistics() {
    PrintInventoryStatistics(&queOne, true);
    std::cout << std::endl;
    PrintInventoryStatistics(&queTwo, true);
    std::cout << std::endl;
    PrintInventoryStatistics(&queThree, true);
    std::cout << std::endl;
}

void Inventory::ConsumeInventoryFile(std::string filepath) {
    // File reading stuff
    std::string line;
    std::ifstream myfile;
    myfile.open(filepath);

    // File check stuff
    if(!myfile.is_open()) {
        perror("Subor sa nepodarilo otvorit!");
        return;
    }

    // Actuall que filling
    while(getline(myfile, line)) {
        std::vector<std::string> splittedText = StringUtils::split(line, " ");

        int itemType = std::stoi(splittedText[0]);
        std::string purchaseType = splittedText[1];
        int quantity = std::stoi(splittedText[2]);
        double price = std::stod(splittedText[3]);
        auto *record = new InventoryRecord(itemType, purchaseType, quantity, price);

        UpdateInventoryStatus(InventoryRecord(itemType, purchaseType, quantity, price));

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

    std::cout << "Nacitanie prebehlo v poriadku" << std::endl;
    wasInventoryAlreadyLoaded = true;
}

void Inventory::WriteInventoryToFile(std::string outputFile) {
    std::string outputString;

    outputString += GetInventoryInString(queOne);
    outputString += GetInventoryInString(queTwo);
    outputString += GetInventoryInString(queThree);

    std::ofstream file;
    file.open(outputFile);

    if(!file.is_open()) {
        perror("Do suboru sa nezapisu bohuzial ziadne data");
    }

    file << outputString;
    file.close();

    std::cout << "Zapisanie prebehlo v poriadku" << std::endl;
}

std::string Inventory::GetInventoryInString(Queue<InventoryRecord> que) {

    std::string outputString;

    auto tempHeadOne = que.GetHead(); // Temp head is required so we can get back once we will loop trough everything
    while(que.GetHead() != nullptr) {
        outputString += std::to_string(que.GetHead()->GetData()->GetItemType());
        outputString += " ";
        outputString += que.GetHead()->GetData()->GetPurchaseType();
        outputString += " ";
        outputString += std::to_string(que.GetHead()->GetData()->GetQuantity());
        outputString += " ";
        outputString += std::to_string(que.GetHead()->GetData()->GetPrice());
        outputString += "\n";
        que.SetHead(que.GetHead()->GetNext());
    }
    que.SetHead(tempHeadOne); // Setting head back - so it will looks like it's been never looped torugh

    return outputString;
}
