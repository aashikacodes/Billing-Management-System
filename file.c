#include <stdio.h>

// Define a structure for Bill
typedef struct {
    char customerName[50];
    char date[20];
    int itemCount;
    struct {
        char name[50];
        int quantity;
        float price;
    } items[100];
    float totalAmount;
} Bill;

void saveBillToFile(const char *filename, Bill bill) {
    // Open file in append mode
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    // Calculate total amount
    bill.totalAmount = 0;
    for (int i = 0; i < bill.itemCount; i++) {
        bill.totalAmount += bill.items[i].quantity * bill.items[i].price;
    }

    // Write bill details to the file
    fprintf(file, "Customer Name: %s\n", bill.customerName);
    fprintf(file, "Date: %s\n", bill.date);
    fprintf(file, "Total Amount: %.2f\n", bill.totalAmount);
    fprintf(file, "Items Purchased:\n");
    for (int i = 0; i < bill.itemCount; i++) {
        fprintf(file, "  - %s: %d @ %.2f each\n", 
                bill.items[i].name, 
                bill.items[i].quantity, 
                bill.items[i].price);
    }
    fprintf(file, "----------------------------------\n");

    // Close the file
    fclose(file);

    printf("Bill saved successfully!\n");
}

// Define a structure for Inventory Item
typedef struct {
    char name[50];
    int quantity;
    float price;
} InventoryItem;

// Function to load inventory from file
int loadInventoryFromFile(const char *filename, InventoryItem inventory[], int *itemCount) {
    // Open file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open inventory file.\n");
        return 0; // Return 0 to indicate failure
    }

    // Read inventory data from file
    *itemCount = 0;
    while (fscanf(file, "%49s %d %f", 
                  inventory[*itemCount].name, 
                  &inventory[*itemCount].quantity, 
                  &inventory[*itemCount].price) == 3) {
        (*itemCount)++;
    }

    // Close the file
    fclose(file);

    printf("Inventory loaded successfully! Total items: %d\n", *itemCount);
    return 1; // Return 1 to indicate success
}

void saveInventoryToFile(const char *filename, InventoryItem inventory[], int itemCount) {
    FILE *file = fopen(filename, "w"); // Open file in write mode to overwrite
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    // Write inventory data to the file
    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%s %d %.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file); // Close the file after writing
    printf("Inventory successfully saved to file: %s\n", filename);
}

int main() {
    Bill testBill = {
        "John Doe", 
        "2024-11-26", 
        2, 
        { {"Laptop", 1, 50000.0}, {"Mouse", 2, 1500.0} }, 
        0.0  // Will be calculated in saveBillToFile
    };
    saveBillToFile("bills.txt", testBill);

    InventoryItem inventory[100];
    int itemCount = 0;

    if (loadInventoryFromFile("inventory.txt", inventory, &itemCount)) {
        printf("Loaded inventory:\n");
        for (int i = 0; i < itemCount; i++) {
            printf("%s: %d units @ %.2f each\n", 
                   inventory[i].name, 
                   inventory[i].quantity, 
                   inventory[i].price);
        }
    }

    // Optionally, save the inventory back to the file (after modifying, if needed)
    saveInventoryToFile("inventory.txt", inventory, itemCount);
    
    return 0;
}
