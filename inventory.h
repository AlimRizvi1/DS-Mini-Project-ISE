#ifndef INVENTORY_H
#define INVENTORY_H

#define TABLE_SIZE 10
#define NAME_SIZE 50
#define DATA_FILE "data.txt"

typedef struct Item
{
    int id;
    char name[NAME_SIZE];
    int quantity;
    float price;
    struct Item *next;
} Item;

typedef struct
{
    Item *table[TABLE_SIZE];
} HashTable;

HashTable *create_table();
int hash_function(int id);
Item *create_item(int id, const char *name, int quantity, float price);
void insert_item(HashTable *ht, int id, const char *name, int quantity, float price);
Item *search_item(HashTable *ht, int id);
void update_item(HashTable *ht, int id, int quantity, float price);
void delete_item(HashTable *ht, int id);
void display_items(HashTable *ht);
void free_table(HashTable *ht);

void save_to_file(HashTable *ht);
void load_from_file(HashTable *ht);

#endif
