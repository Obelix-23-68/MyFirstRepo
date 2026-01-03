#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_CAP 100
#define NOT_FOUND -1
#define MAX_BUFF 256

typedef struct HashEntry{
	char *key;
	int value;
	struct HashEntry *next;
	}HashEntry;

typedef struct{
	HashEntry **entries;
	int size;
	int fullness;
} HashTable;

HashTable *create_table(){
	HashTable *table = (HashTable*)malloc(sizeof(HashTable));
	table -> size = INIT_CAP;
	table -> fullness = 0;
	table -> entries = (HashEntry**)calloc(INIT_CAP, sizeof(HashEntry*));
return table;
}

void print_menu(){
	printf("\n   ---Интерактивная таблица---\n"
				 "1 - add the element (push)\n"
				 "2 - search the element (peek)\n"
				 "3 - delete the element (like a pop, but NOT)\n"
				 "4 - size\n"
				 "0 - Quit\n"
				 "Enter: ");
}

int hash(char *key, int size){
	unsigned int hash = 5381;
	int c;
		while((c = *key++))
			hash = ((hash << 5) + hash) + c;
return hash % size;
}

int resize_up(HashTable *table){
	int new_size = (table->size) * 2;
	HashEntry **new_entries = (HashEntry**)calloc(new_size,sizeof(HashEntry*));
	for (int i = 0; i < table->size; i++){
		HashEntry *entry = table->entries[i];
		while(entry){
			HashEntry *next = entry->next;
			int new_index = hash(entry->key, new_size);
			entry->next = new_entries[new_index];
			new_entries[new_index] = entry;
			entry = next;
		}
	}
	table->size = new_size;
	free(table->entries);
	table->entries = new_entries;
return 0;
}

int insert(HashTable *table, char *key, int value){
	int index = hash(key, table->size);
	HashEntry *current = table->entries[index];
	while(current != NULL){
		if (strcmp(key,current->key) == 0){
			current->value = value;
			puts("value has been refreshed!");
		return 0;
		}
		current = current->next;
	}
	HashEntry *entry = (HashEntry*)malloc(sizeof(HashEntry));
	if (entry == NULL){ puts("ptr memory error!"); return 0; }
	entry->key = (strdup(key));
	entry->value = value;
	entry->next = table->entries[index];
	table->entries[index] = entry;
	table->fullness++;
	printf("%s - added", key);
	if (table->fullness > table->size * 0.7)
		resize_up(table);
return 0;
}

int search(HashTable *table, char *key){
	int index = hash(key, table->size);
	HashEntry *entry = table->entries[index];
	while(entry){
		if (strcmp(entry->key,key) == 0)
			return entry->value;
		entry = entry->next;
	}
	return NOT_FOUND;
}

int del(HashTable *table, char *key){
	int index = hash(key, table->size);
	HashEntry *entry = table->entries[index];
	HashEntry *prev = NULL;
	int counter = 0;
	while(entry){
		if (strcmp(entry->key, key) == 0){
			if (prev == NULL){
				table->entries[index] = entry->next;
			}
			else {
				prev->next = entry->next;
			}
			free(entry->key);
			free(entry);
			table->fullness--;
			return 0;
		}
			prev = entry;
			entry = entry->next;
			counter++;
	}
return NOT_FOUND;
}

int del_table(HashTable *table){
	for(int i = 0; i < table->size; i++){
		HashEntry *entry = table->entries[i];
		while(entry){
			HashEntry *next = entry->next;
			free(entry->key);
			free(entry);
			entry = next;
		}
	}
	free(table->entries);
	free(table);
return 0;
}

int sizef(HashTable *table) {
	if (table != NULL)
		return table->fullness;
return NOT_FOUND;
}

int main(){
	HashTable *table1 = create_table();
	if (table1 == NULL){
		puts("error creating table!");
	return 0;
	}
	int choice;
	do{
		print_menu();
		char choice_str[MAX_BUFF];
		fgets(choice_str, MAX_BUFF, stdin);
		choice_str[strcspn (choice_str, "\n")] = 0;
		char *endptr = NULL;
		long choice_long = strtol(choice_str, &endptr, 10);
		if (endptr == choice_str || *endptr != '\0'){
			printf("enter number error");
			continue;
		}
		choice = (int)choice_long;
		char key[MAX_BUFF];
		int check, size;
		switch(choice){
			case 1: printf("enter the key: ");											//insert
							fgets(key, MAX_BUFF, stdin);
							key[strcspn (key,"\n")] = 0;
							printf("\nenter the value: ");
							char value[MAX_BUFF];
							fgets(value, MAX_BUFF, stdin);
							value[strcspn (value, "\n")] = 0;
							char *endptr2 = NULL;
							long choice_value = strtol(value, &endptr2, 10);
							if (value == endptr2 || *endptr2 != '\0'){
								printf("error of enter of value!\n");
								break;
							}
							insert(table1, key, (int)choice_value);
							printf("%s, %d - added", key, (int)choice_value);
							break;
			case 2: printf("enter the key: ");											//search
							fgets(key, MAX_BUFF, stdin);
							key[strcspn (key, "\n")] = 0;
							check = search(table1, key);
							if (check == -1){
								printf("KEY NOT FOUND");
								break;
							}
							printf("%s - conteins:\n"
										 "%d.\n", key, check);
							break;
			case 3: printf("enter the key: ");											//del
							fgets(key, MAX_BUFF, stdin);
							key[strcspn (key, "\n")] = 0;
							int check_value = search(table1, key);
							check = del(table1, key);
							if (check == NOT_FOUND){
								printf("element not found");
								break;
							}
							printf("the element %s, with value %d - has been deleted", key, check_value);
							break;
			case 4: size = sizef(table1);
							if (size == NOT_FOUND){
								printf ("error of size: таблицы нема");
								break;
							}
						  printf("current size of table - %d", size);
							break;
			case 0: printf("quiting");
							break;
			default: printf("error! enter the number 0-3!");
		}
	} while (choice != 0);
	del_table(table1);
return 0;
}
