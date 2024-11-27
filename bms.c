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
  struct items itm[50];
};

// prototypes
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

// screen clear macro
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

struct items inventory[100];
int inventoryCount = 0; 

// Display available items menu
void displayItems()
{
  printf("\n========== JAB WE MET MENU ==========\n");
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
  printf("11. Pizza - $150\n");
  printf("12. Pasta - $150\n");
  printf("13. Mojito - $150\n");
  printf("14. Lassi - $150\n");
  printf("15. Jalebi - $150\n");
  printf("16. Gajar ka halwa - $150\n");
  printf("17. Aloo Parantha - $150\n");
  printf("18. Italian Maggie - $150\n");
  printf("19. Coffee - $150\n");
  printf("20. Exit\n");
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
void generateInvoice()
{
  int n, opt;
  struct orders ord;

  while (1)
  {
    system(CLEAR_SCREEN);
    printf("\n========== Generate Invoice ==========\n");
    printf("1. Create New Invoice\n");
    printf("2. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &opt);
    getchar();
    if (opt == 2)
      break; // 

    if (opt == 1)
    {
      printf("\nEnter the name of the customer: ");
      fgets(ord.customer, sizeof(ord.customer), stdin);
      ord.customer[strcspn(ord.customer, "\n")] = 0; 
      strcpy(ord.date, __DATE__);

      printf("\nEnter the number of items: ");
      scanf("%d", &n);
      getchar();

      ord.numOfItems = n; 

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
      saveInvoiceToFile(ord);

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
void showAllInvoices()
{
  FILE *fp = fopen("invoices.txt", "r");
  if (fp == NULL)
  {
    printf("\nNo invoices found.\n");
    return;
  }

  char buffer[256];
  printf("\n========= All Invoices =========\n");
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    printf("%s", buffer);
  }
  fclose(fp);
  printf("\n=================================\n");
}

// to search
void searchInvoice()
{
  char searchTerm[50];
  printf("\nEnter customer name or date to search: ");
  fgets(searchTerm, sizeof(searchTerm), stdin);
  searchTerm[strcspn(searchTerm, "\n")] = 0; 

  FILE *fp = fopen("invoices.txt", "r");
  if (fp == NULL)
  {
    printf("\nNo invoices found.\n");
    return;
  }

  char buffer[256];
  int found = 0;
  int displayInvoice = 0;

  printf("\n========= Search Results =========\n");
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    
    if (strstr(buffer, searchTerm) != NULL)
    {
      found = 1;
      displayInvoice = 1; // Start the invoice
    }

    
    if (displayInvoice)
    {
      printf("%s", buffer);
    }

    
    if (strstr(buffer, "------------------------------------") != NULL)
    {
      displayInvoice = 0;
    }
  }
  fclose(fp);

  if (!found)
  {
    printf("\nNo matching invoices found for '%s'.\n", searchTerm);
  }
  printf("\n===================================\n");
}

// Save invoice details to file
void saveInvoiceToFile(struct orders ord)
{
  FILE *fp = fopen("invoices.txt", "a");
  if (fp == NULL)
  {
    printf("\nError opening file for writing.\n");
    return;
  }

  fprintf(fp, "Customer: %s\nDate: %s\n", ord.customer, ord.date);
  for (int i = 0; i < ord.numOfItems; i++)
  {
    fprintf(fp, "Item: %s, Quantity: %d, Price: %.2f\n",
            ord.itm[i].name, ord.itm[i].qty, ord.itm[i].price);
  }
  fprintf(fp, "------------------------------------\n");
  fclose(fp);
}

// Initialize inventory
void initializeInventory()
{
  printf("\nEnter the number of items to add to the inventory: ");
  scanf("%d", &inventoryCount);
  getchar(); 

  for (int i = 0; i < inventoryCount; i++)
  {
    printf("\nEnter details for item %d:\n", i + 1);
    printf("Item Name: ");
    fgets(inventory[i].name, sizeof(inventory[i].name), stdin);
    inventory[i].name[strcspn(inventory[i].name, "\n")] = 0; 

    printf("Quantity: ");
    scanf("%d", &inventory[i].qty);

    printf("Price: ");
    scanf("%f", &inventory[i].price);
    getchar(); 
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
    getchar(); 

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
      getchar();
      break;
    case 3: // Show all invoices
      showAllInvoices();
      printf("\nPress Enter to continue...");
      getchar();
      break;
    case 4: // Search invoice
      searchInvoice();
      printf("\nPress Enter to continue...");
      getchar();
      break;
    case 5: // Inventory Management
    {
      int invOpt;
      printf("\n1. Initialize Inventory\n2. Display Inventory\n");
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

      default:
        printf("\nInvalid choice.\n");
        break;
      }
    }
    break;
    case 6:
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