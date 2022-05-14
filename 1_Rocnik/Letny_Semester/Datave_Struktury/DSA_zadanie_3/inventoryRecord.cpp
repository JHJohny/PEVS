
#include <string>

#include "InventoryRecord.h"

InventoryRecord::InventoryRecord(int _itemType, std::string _purchaseType, int _quantity, double _price) {
    itemType = _itemType;
    quantity = _quantity;
    price = _price;
    purchaseType = _purchaseType;
}

int InventoryRecord::GetItemType() {
    return itemType;
}

void InventoryRecord::SetItemType(int _itemType) {
    itemType = _itemType;
}

int InventoryRecord::GetQuantity() {
    return quantity;
}

void InventoryRecord::SetQuantity(int _quantity) {
    quantity = _quantity;
}

double InventoryRecord::GetPrice()  {
    return price;
}

void InventoryRecord::SetPrice(double _price) {
    price = _price;
}

std::string InventoryRecord::GetPurchaseType() {
    return purchaseType;
}

void InventoryRecord::SetPurchaseType(char _purchaseType) {
    purchaseType = _purchaseType;
}
