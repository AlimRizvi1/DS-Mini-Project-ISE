#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashTable *create_table()
{
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++)
        ht->table[i] = NULL;
    return ht;
}

int hash_function(int id)
{
    return id % TABLE_SIZE;
}

Item *create_item(int id, const char *name, int quantity, float price)
{
    Item *new_item = (Item *) malloc(sizeof(Item));
    new_item->id = id;
    strcpy(new_item->name, name);
    new_item->quantity = quantity;
    new_item->price = price;
    new_item->next = NULL;
    return new_item;
}

void insert_item(HashTable *ht, int id, const char *name, int quantity, float price)
{
    int index = hash_function(id);
    Item *new_item = create_item(id, name, quantity, price);

    Item *temp = ht->table[index];
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("❌ Item with ID %d already exists!\n", id);
            free(new_item);
            return;
        }
        temp = temp->next;
    }

    new_item->next = ht->table[index];
    ht->table[index] = new_item;
    printf("✅ Item '%s' added successfully!\n", name);
}

Item *search_item(HashTable *ht, int id)
{
    int index = hash_function(id);
    Item *temp = ht->table[index];
    while (temp != NULL)
    {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void update_item(HashTable *ht, int id, int quantity, float price)
{
    Item *item = search_item(ht, id);
    if (item == NULL)
    {
        printf("❌ Item not found!\n");
        return;
    }
    item->quantity = quantity;
    item->price = price;
    printf("✅ Item updated successfully!\n");
}

void delete_item(HashTable *ht, int id)
{
    int index = hash_function(id);
    Item *temp = ht->table[index];
    Item *prev = NULL;

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("❌ Item not found!\n");
        return;
    }

    if (prev == NULL)
        ht->table[index] = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("✅ Item deleted successfully!\n");
}

void display_items(HashTable *ht)
{
    printf("\n📦 Inventory Items:\n");
    printf("----------------------------------------------------\n");
    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("----------------------------------------------------\n");

    int empty = 1;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Item *temp = ht->table[i];
        while (temp != NULL)
        {
            empty = 0;
            printf("%d\t%-15s\t%d\t\t%.2f\n", temp->id, temp->name, temp->quantity, temp->price);
            temp = temp->next;
        }
    }
    if (empty)
        printf("No items found.\n");
    printf("----------------------------------------------------\n");
}

void free_table(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Item *temp = ht->table[i];
        while (temp != NULL)
        {
            Item *to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }
    free(ht);
}

void save_to_file(HashTable *ht)
{
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp)
    {
        printf("⚠️ Unable to save data!\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Item *temp = ht->table[i];
        while (temp != NULL)
        {
            fprintf(fp, "%d,%s,%d,%.2f\n", temp->id, temp->name, temp->quantity, temp->price);
            temp = temp->next;
        }
    }

    fclose(fp);
    printf("💾 Data saved successfully to '%s'.\n", DATA_FILE);
}

void load_from_file(HashTable *ht)
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp)
        return;

    int id, qty;
    float price;
    char name[NAME_SIZE];
    while (fscanf(fp, "%d,%49[^,],%d,%f\n", &id, name, &qty, &price) == 4)
    {
        insert_item(ht, id, name, qty, price);
    }

    fclose(fp);
    printf("📂 Data loaded from '%s'.\n", DATA_FILE);
}
