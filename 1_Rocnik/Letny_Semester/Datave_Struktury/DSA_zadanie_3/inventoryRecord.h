
#ifndef INVENTORY_RECORD_H
#define INVENTORY_RECORD_H

#include <string>

class InventoryRecord{
private:
    int itemType;
    std::string purchaseType;
    int quantity;
    double price;

public:
    InventoryRecord(int _itemType, std::string _purchaseType, int _quantity, double _price); // Constructor

    // Getters and setters
    void SetItemType(int _itemType);
    int GetItemType();

    void SetQuantity(int _quantity);
    int GetQuantity();

    void SetPrice(double _price);
    double GetPrice();

    void SetPurchaseType(char _purchaseType);
    std::string GetPurchaseType();
};

#endif