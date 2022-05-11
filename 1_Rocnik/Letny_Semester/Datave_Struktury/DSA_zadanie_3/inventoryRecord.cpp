
#include <string>

#include "InventoryRecord.h"

InventoryRecord::InventoryRecord(int _itemType, int _quantity, float _price, purchaseTypes _purchaseType) {
    itemType = _itemType;
    quantity = _quantity;
    price = _price;
    purchaseType = _purchaseType;
}

int InventoryRecord::GetItemType() {
    return itemType;
}

void InventoryRecord::SetItemType(int _ItemType) {
    itemType = _ItemType;
}

int InventoryRecord::GetQuantity() {
    return quantity;
}

void InventoryRecord::SetQuantity(int _quantity) {
    quantity = _quantity;
}

float InventoryRecord::GetPrice() {
    return price;
}

void InventoryRecord::SetPrice(float _price) {
    price = _price;
}

InventoryRecord::purchaseTypes InventoryRecord::GetPurchaseType() {
    return purchaseType;
}

void InventoryRecord::SetPurchaseType(InventoryRecord::purchaseTypes _purchaseType) {
    purchaseType = _purchaseType;
}
