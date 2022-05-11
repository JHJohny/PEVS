
#ifndef INVENTORY_RECORD_H
#define INVENTORY_RECORD_H

#include <string>

class InventoryRecord{
private:
    int itemType;
    int quantity;
    float price;

public:
    enum purchaseTypes {P, K};
    purchaseTypes purchaseType;

    InventoryRecord(int _itemType, int _quantity, float _price, purchaseTypes _purchaseType); // Constructor

    // Getters and setters
    void SetItemType(int _ItemType);
    int GetItemType();

    void SetQuantity(int _quantity);
    int GetQuantity();

    void SetPrice(float _price);
    float GetPrice();

    void SetPurchaseType(purchaseTypes _purchaseType);
    purchaseTypes GetPurchaseType();
};

#endif