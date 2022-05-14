


#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

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

    void ConsumeInventoryFile();

};

#endif