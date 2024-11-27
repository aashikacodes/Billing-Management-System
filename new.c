#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures for items and orders
struct items
{
  char name[20];
  float price;
  int qty;
};

struct orders
{
  char customer[50];
  char date[50];
  int numOfItems;
  struct items itm[50]; // Correct struct member usage
};

// Function prototypes
void displayItems();
void operationsMenu();
void initializeInventory();
void displayInventory();
void updateInventory();
int findItemInInventory(char itemName[20]);
void reduceInventory(char itemName[20], int quantity);
void generateBillHeader(char name[50], char date[30]);
void generateBillBody(char item[30], int qty, float price);
void generateBillFooter(float total);
void generateInvoice();

// Platform-specific screen clear macro
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// Global variables
struct items inventory[100];
int inventoryCount = 0; // Number of items in inventory
void generateInvoice()
{
  int n, opt;        // Local variables
  struct orders ord; // Declare the `ord` variable to store invoice details

  while (1)
  {
    system(CLEAR_SCREEN);
    printf("\n========== Generate Invoice ==========\n");
    printf("1. Create New Invoice\n");
    printf("2. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &opt);
    getchar(); // Consume newline

    if (opt == 2)
      break; // Exit the loop and return to main menu

    if (opt == 1)
    {
      printf("\nEnter the name of the customer: ");
      fgets(ord.customer, sizeof(ord.customer), stdin);
      ord.customer[strcspn(ord.customer, "\n")] = 0; // Remove newline
      strcpy(ord.date, __DATE__);

      printf("\nEnter the number of items: ");
      scanf("%d", &n);
      getchar();

      ord.numOfItems = n; // Set the number of items

      for (int i = 0; i < n; i++)
      {
        printf("\nEnter details for item %d:\n", i + 1);

        // Item name
        printf("Item Name: ");
        fgets(ord.itm[i].name, sizeof(ord.itm[i].name), stdin);
        ord.itm[i].name[strcspn(ord.itm[i].name, "\n")] = 0;

        // Quantity
        printf("Quantity: ");
        scanf("%d", &ord.itm[i].qty);

        // Unit price
        printf("Unit Price: ");
        scanf("%f", &ord.itm[i].price);
        getchar();

        // Reduce inventory
        reduceInventory(ord.itm[i].name, ord.itm[i].qty);
      }

      // Generate and display the bill
      float total = 0;
      generateBillHeader(ord.customer, ord.date);
      for (int i = 0; i < n; i++)
      {
        generateBillBody(ord.itm[i].name, ord.itm[i].qty, ord.itm[i].price);
        total += ord.itm[i].qty * ord.itm[i].price;
      }
      generateBillFooter(total);

      printf("\nPress Enter to return to menu...");
      getchar();
    }
    else
    {
      printf("\nInvalid choice! Please try again.\n");
    }
  }
}
void generateBillHeader(char name[50], char date[30])
{
  printf("\n\n");
  printf("##########################################\n");
  printf("############# JAB FOOD MET US ############\n");
  printf("##########################################\n");
  printf("Customer Name: %s\n", name);
  printf("Date: %s\n", date);
  printf("------------------------------------------\n");
  printf("Item\t\tQty\t\tPrice\n");
  printf("------------------------------------------\n");
}
void generateBillBody(char item[30], int qty, float price)
{
  printf("%-15s\t%-10d\t%.2f\n", item, qty, qty * price);
}
void generateBillFooter(float total)
{
  printf("------------------------------------------\n");
  printf("Sub Total:\t\t\t%.2f\n", total);
  printf("GST @18%%:\t\t\t%.2f\n", 0.18 * total);
  printf("------------------------------------------\n");
  printf("Grand Total:\t\t\t%.2f\n", total + (0.18 * total));
  printf("------------------------------------------\n");
  printf("########### Thank You! Visit Again ###########\n");
}

// Display available items menu
void displayItems()
{
  printf("\n========== ITEMS MENU ==========\n");
  printf("1. Aglio e Olio - $800\n");
  printf("2. Margherita Pizza - $500\n");
  printf("3. Chole Bhature  - $100\n");
  printf("4. Vegetable Spring Rolls - $150\n");
  printf("5. Tomato Basil Soup - $150\n");
  printf("6. Burrito Bowl - $150\n");
  printf("7. Loaded Nachos - $150\n");
  printf("8. Hot and Sour Soup - $150\n");
  printf("9. Pumpkin Soup - $150\n");
  printf("10. Lasagna - $150\n");
  printf("11. Exit\n");
  printf("================================\n");
  printf("Enter your choice: ");
}

// Operations menu
void operationsMenu()
{
  printf("     ================= JAB FOOD MET US ================\n");
  printf("\nPlease select your preferred operation:\n");
  printf("     1. Menu\n");
  printf("     2. Generate Invoice\n");
  printf("     3. Show All Invoices\n");
  printf("     4. Search Invoice\n");
  printf("     5. Inventory Management\n");
  printf("     6. EXIT\n");
  printf("\nEnter your choice: ");
}

// Initialize inventory
void initializeInventory()
{
  printf("\nEnter the number of items to add to the inventory: ");
  scanf("%d", &inventoryCount);
  getchar(); // Consume newline

  for (int i = 0; i < inventoryCount; i++)
  {
    printf("\nEnter details for item %d:\n", i + 1);
    printf("Item Name: ");
    fgets(inventory[i].name, sizeof(inventory[i].name), stdin);
    inventory[i].name[strcspn(inventory[i].name, "\n")] = 0; // Remove newline

    printf("Quantity: ");
    scanf("%d", &inventory[i].qty);

    printf("Price: ");
    scanf("%f", &inventory[i].price);
    getchar(); // Consume newline
  }
  printf("\nInventory initialized successfully!\n");
}

// Display inventory
void displayInventory()
{
  printf("\n========= INVENTORY =========\n");
  printf("Item Name\tQuantity\tPrice\n");
  printf("------------------------------------\n");

  for (int i = 0; i < inventoryCount; i++)
  {
    printf("%-20s\t%-10d\t%.2f\n", inventory[i].name, inventory[i].qty, inventory[i].price);
  }
  printf("------------------------------------\n");
}

// Update inventory
void updateInventory()
{
  char itemName[20];
  printf("\nEnter the name of the item to update: ");
  fgets(itemName, sizeof(itemName), stdin);
  itemName[strcspn(itemName, "\n")] = 0; // Remove newline

  int index = findItemInInventory(itemName);
  if (index != -1)
  {
    printf("\nItem found! Enter new details:\n");

    printf("New Quantity: ");
    scanf("%d", &inventory[index].qty);

    printf("New Price: ");
    scanf("%f", &inventory[index].price);
    getchar(); // Consume newline

    printf("\nItem updated successfully!\n");
  }
  else
  {
    printf("\nItem not found in inventory.\n");
  }
}

// Find item in inventory
int findItemInInventory(char itemName[20])
{
  for (int i = 0; i < inventoryCount; i++)
  {
    if (strcmp(inventory[i].name, itemName) == 0)
    {
      return i;
    }
  }
  return -1; // Not found
}

// Reduce inventory
void reduceInventory(char itemName[20], int quantity)
{
  int index = findItemInInventory(itemName);
  if (index != -1)
  {
    if (inventory[index].qty >= quantity)
    {
      inventory[index].qty -= quantity;
    }
    else
    {
      printf("\nError: Insufficient quantity for %s.\n", itemName);
    }
  }
  else
  {
    printf("\nError: Item %s not found in inventory.\n", itemName);
  }
}

// Main function
int main()
{
  int opt;
  while (1)
  {
    system(CLEAR_SCREEN);
    operationsMenu();

    scanf("%d", &opt);
    getchar(); // Consume newline

    switch (opt)
    {
    case 1:
      displayItems();
      printf("\nPress Enter to continue...");
      getchar();
      break;
    case 2:
      generateInvoice();
      printf("\nPress Enter to continue...\n");
      break;
    case 3:
      printf("\nFeature under construction.\n");
      break;
    case 4:
    {
      int invOpt;
      printf("\n1. Initialize Inventory\n2. Display Inventory\n3. Update Inventory\n");
      printf("Enter your choice: ");
      scanf("%d", &invOpt);
      getchar();

      switch (invOpt)
      {
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
    }
    break;
    case 5:
      printf("\nThank you for using the system. Goodbye!\n");
      exit(0);
    default:
      printf("\nInvalid choice! Please try again.\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
  }

  return 0;
}
