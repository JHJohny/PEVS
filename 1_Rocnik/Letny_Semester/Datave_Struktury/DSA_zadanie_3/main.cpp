
#include "Inventory.h"

#define FILE_PATH "./Inventory.txt"

int main() {
    Inventory inventory = Inventory(FILE_PATH);
    inventory.Start();

    return 0;
}
