


#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include <map>

#include "Queue.h"
#include "InventoryRecord.h"

class Inventory {
public:
    Inventory();
    void Start();

private:
    Queue<InventoryRecord> queOne;
    Queue<InventoryRecord> queTwo;
    Queue<InventoryRecord> queThree;

    // These inventory statuses represent current state of inventory for each unit - how many units is left for that price
    std::map<double, int> inventoryOneStatus;
    std::map<double, int> inventoryTwoStatus;
    std::map<double, int> inventoryThreeStatus;

    void Buy();
    void Sell();
    void ConsumeInventoryFile(std::string filepath);
    void PrintGeneralStatistics();
    void PrintInventoryStatistics(Queue<InventoryRecord> *queOne, bool printSummary= false);
    void MakeSellForInventory(int polozka, int units);
    void UpdateInventoryStatus(InventoryRecord record);
    void WriteInventoryToFile(std::string outputFile);
    std::string GetInventoryInString(Queue<InventoryRecord> que);
};

#endif