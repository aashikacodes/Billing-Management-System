#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures for items and orders
struct items {
    char name[20];
    float price;
    int qty;
};

struct orders {
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

// Global variables
struct items inventory[100];
int inventoryCount = 0; // Track number of items in inventory

// Function prototypes
void initializeInventory();
void displayInventory();
void updateInventory();
int findItemInInventory(char itemName[20]);
void reduceInventory(char itemName[20], int quantity);
void operationsMenu();
void generateBillHeader(char name[50], char date[30]);
void generateBillBody(char item[30], int qty, float price);
void generateBillFooter(float total);

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

// Initialize inventory
void initializeInventory() {
    printf("\nEnter the number of items to add to the inventory: ");
    scanf("%d", &inventoryCount);
    getchar(); // Consume newline

    for (int i = 0; i < inventoryCount; i++) {
        printf("\nEnter details for item %d:\n", i + 1);
        printf("Item Name: ");
        fgets(inventory[i].name, sizeof(inventory[i].name), stdin);
        inventory[i].name[strcspn(inventory[i].name, "\n")] = 0;

        printf("Quantity: ");
        scanf("%d", &inventory[i].qty);

        printf("Price: ");
        scanf("%f", &inventory[i].price);
        getchar(); // Consume newline
    }
    printf("\nInventory initialized successfully!\n");
}

// Display inventory
void displayInventory() {
    printf("\n========= INVENTORY =========\n");
    printf("Item Name\tQuantity\tPrice\n");
    printf("------------------------------------\n");

    for (int i = 0; i < inventoryCount; i++) {
        printf("%s\t\t%d\t\t%.2f\n", inventory[i].name, inventory[i].qty, inventory[i].price);
    }
    printf("------------------------------------\n");
}

// Find item in inventory
int findItemInInventory(char itemName[20]) {
    for (int i = 0; i < inventoryCount; i++) {
        if (strcmp(inventory[i].name, itemName) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

// Update inventory
void updateInventory() {
    char itemName[20];
    printf("\nEnter the name of the item to update: ");
    fgets(itemName, sizeof(itemName), stdin);
    itemName[strcspn(itemName, "\n")] = 0;

    int index = findItemInInventory(itemName);
    if (index != -1) {
        printf("\nItem found! Enter new details:\n");

        printf("New Quantity: ");
        scanf("%d", &inventory[index].qty);

        printf("New Price: ");
        scanf("%f", &inventory[index].price);
        getchar(); // Consume newline

        printf("\nItem updated successfully!\n");
    } else {
        printf("\nItem not found in inventory.\n");
    }
}

// Reduce inventory
void reduceInventory(char itemName[20], int quantity) {
    int index = findItemInInventory(itemName);
    if (index != -1) {
        if (inventory[index].qty >= quantity) {
            inventory[index].qty -= quantity;
        } else {
            printf("\nError: Insufficient quantity for %s.\n", itemName);
        }
    } else {
        printf("\nError: Item %s not found in inventory.\n", itemName);
    }
}

// Generate bill header
void generateBillHeader(char name[50], char date[30]) {
    printf("\n\n");
    printf("\t     JAB FOOD MET US\n");
    printf("\t  ----------------------\n");
    printf("Date: %s\n", date);
    printf("Invoice To: %s\n", name);
    printf("-----------------------------------------------\n");
    printf("Items\t\tQty\t\tTotal\n");
    printf("--------------------------------------------------\n");
}

// Generate bill body
void generateBillBody(char item[30], int qty, float price) {
    printf("%s\t\t%d\t\t%.2f\n", item, qty, qty * price);
}

// Generate bill footer
void generateBillFooter(float total) {
    printf("\n");
    float discount = 0.1 * total;
    float netTotal = total - discount;
    float cgst = 0.09 * netTotal;
    float grandTotal = netTotal + 2 * cgst;

    printf("-----------------------------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f\n", total);
    printf("Discount @10%%\t\t\t%.2f\n", discount);
    printf("Net Total\t\t\t%.2f\n", netTotal);
    printf("CGST @9%%\t\t\t%.2f\n", cgst);
    printf("SGST @9%%\t\t\t%.2f\n", cgst);
    printf("-----------------------------------------------------------------\n");
    printf("Grand Total\t\t\t%.2f\n", grandTotal);
    printf("-----------------------------------------------------------------\n");
}

// Operations menu
void operationsMenu() {
    printf("\t================ JAB FOOD MET US ================\n");
    printf("\nPlease select your preferred operation:\n");
    printf("1. Generate Invoice\n");
    printf("2. Show All Invoices\n");
    printf("3. Search Invoice\n");
    printf("4. Inventory Management\n");
    printf("5. EXIT\n");
    printf("\nEnter your choice: ");
}

// Main function
int main() {
    int opt;
    char contFlag = 'y';

    while (contFlag == 'y') {
        system(CLEAR_SCREEN);
        operationsMenu();
        scanf("%d", &opt);
        getchar();

        switch (opt) {
        case 1:
            printf("\nFeature under construction.\n");
            break;
        case 2:
            printf("\nFeature under construction.\n");
            break;
        case 3:
            printf("\nFeature under construction.\n");
            break;
        case 4: {
            int invOpt;
            printf("\n1. Initialize Inventory\n2. Display Inventory\n3. Update Inventory\n");
            printf("Enter your choice: ");
            scanf("%d", &invOpt);
            getchar();

            switch (invOpt) {
            case 1:
                initializeInventory();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                updateInventory();
                break;
            default:
                printf("\nInvalid choice.\n");
                break;
            }
        } break;
        case 5:
            printf("\nThank you for using the system. Goodbye!\n");
            exit(0);
        default:
            printf("\nInvalid choice! Please try again.\n");
        }

        printf("\nDo you want to perform another operation? [y/n]: ");
        scanf(" %c", &contFlag);
    }

    return 0;
}
