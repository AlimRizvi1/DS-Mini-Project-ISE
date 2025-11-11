#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>

void menu()
{
    printf("\n===== Inventory Management System =====\n");
    printf("1. Add Item\n");
    printf("2. Search Item\n");
    printf("3. Update Item\n");
    printf("4. Delete Item\n");
    printf("5. Display All Items\n");
    printf("6. Save & Exit\n");
    printf("=======================================\n");
    printf("Enter your choice: ");
}

int main()
{
    HashTable *ht = create_table();
    load_from_file(ht);

    int choice, id, qty;
    float price;
    char name[NAME_SIZE];

    while (1)
    {
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Quantity: ");
                scanf("%d", &qty);
                printf("Enter Price: ");
                scanf("%f", &price);
                insert_item(ht, id, name, qty, price);
                break;

            case 2:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                {
                    Item *found = search_item(ht, id);
                    if (found)
                        printf("✅ Found: %d | %s | Qty: %d | Price: %.2f\n", found->id,
                               found->name, found->quantity, found->price);
                    else
                        printf("❌ Item not found!\n");
                }
                break;

            case 3:
                printf("Enter ID to update: ");
                scanf("%d", &id);
                printf("Enter new Quantity: ");
                scanf("%d", &qty);
                printf("Enter new Price: ");
                scanf("%f", &price);
                update_item(ht, id, qty, price);
                break;

            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                delete_item(ht, id);
                break;

            case 5:
                display_items(ht);
                break;

            case 6:
                save_to_file(ht);
                free_table(ht);
                printf("👋 Exiting Inventory System. Goodbye!\n");
                exit(0);

            default:
                printf("❌ Invalid choice! Try again.\n");
        }
    }
}
