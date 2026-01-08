#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 100
#define MAX_LEN 100
#define MAX_BUF 128

typedef struct entry{
	int value;
	char *key;
	struct entry *next;
} entry;

typedef struct Stack{
	entry *entries;
	int number;
	int size;
} Stack;

void print_menu(){
	printf("1 - push\n"
				 "2 - pop\n"
				 "3 - peek\n"
				 "4 - size\n"
				 "0 - exit\n");
}
Stack *create_stack(){
	Stack *p_stack = (Stack*)malloc(sizeof(Stack));
	p_stack->number = 0;
	p_stack->size = INIT_SIZE;
	p_stack->entries = NULL;
return p_stack;
}

int get_number(){
	char choice_str[MAX_LEN];
	fgets(choice_str, MAX_LEN, stdin);
	choice_str[strcspn(choice_str, "\n")] = 0;
	char *end_ptr = NULL;
	long choice = strtol(choice_str, &end_ptr, 10);
	if (end_ptr == choice_str || *end_ptr != '\0'){
		printf("error of enter\n");
		return -1;
	}
return (int)choice;
}

void get_key(char *key){
	fgets(key, MAX_BUF, stdin);
	key[strcspn(key, "\n")] = 0;
}

void push(Stack *p_stack, char *key, int value){
	entry *ent = (entry*)malloc(sizeof(entry));
	ent->key = strdup(key);
	ent->value = value;
	ent->next = p_stack->entries;
	p_stack->entries = ent;
	p_stack->number++;
}

void peek(Stack *p_stack){
	if(p_stack->entries == NULL){
		printf("there is nothing to look at\n");
		return;
	}
	printf("%s, - %d\n", p_stack->entries->key, p_stack->entries->value);
}

void pop(Stack *p_stack){
	peek(p_stack);
	if (p_stack->entries == NULL){
		printf("error, Stack is empty\n");
		return;
	}
	entry *current = p_stack->entries;
	p_stack->entries = current->next;
	free(current->key);
	free(current);
	p_stack->number--;
}

void size(Stack *p_stack){
	printf("size - %d\n", p_stack->number);
}

int main (){
	Stack *p_stack = create_stack();
	int choice, value;
	char key[MAX_BUF];
	do{
		print_menu();
		choice = get_number();
		switch (choice){
			case 1: printf("enter the value: ");
							value = get_number();                //push
							if (value == -1){
								break;
							}
							printf("enter the key: ");
							get_key(key);
							push(p_stack, key, value);
							break;
			case 2: pop(p_stack);                               //pop
							printf("watched and grabbed\n");
							break;
			case 3: peek(p_stack);
							printf("watched\n");
							break;
			case 4: size(p_stack);                               //size
							break;
			case 0: printf("Exiting...\n");
							break;
			default: printf("command not found\n");
		}
	}while(choice);
return 0;
}
