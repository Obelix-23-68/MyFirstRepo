#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define INIT_CAP 100
#define MAX_LINE 100

int fstrcmpfromback(const char *first, const char *second);
int compare_str_re (const void *a, const void *b);
int compare_str (const void *a, const void *b);
int fstrcmp(const char *first, const char *second);

int main(int argc, char *argv[]){
	setlocale(LC_ALL, "");
// нахождение кол-ва и содержимого строк, выделение нужной памяти
	if (argc < 2){
		printf("so few argc");
		return 0;
	}
	FILE *fsource = fopen(argv[1], "r");
	if (fsource == NULL){
		printf("error or opening file");
		return 0;
	}
	char **strings = (char **)malloc(INIT_CAP * sizeof(char*));
	int cap = INIT_CAP, strcount = 0;
	char Buf[MAX_LINE];
	while (fgets(Buf, sizeof(Buf), fsource)){
		Buf[strcspn(Buf, "\n")] = '\0';
		if (strcount >= cap){
			cap *= 2;
			strings = (char **)realloc(strings, cap * sizeof(char*));
		}
		strings[strcount] = (char*)malloc(strlen(Buf) + 1);
		strcpy(strings[strcount], Buf);
		strcount++;
	}
	strings = (char **)realloc(strings, strcount * sizeof(char*));
	fclose(fsource);
//копия для вставки в конец файла изначального варианта строк
	char **stringscopy = (char**)malloc(strcount * sizeof(char*));
	for (int i = 0; i < strcount; i++)
		stringscopy[i] = strings[i];
// сортировка с начала
	FILE *fdestination = fopen("outfile.txt", "w");
	qsort(strings, strcount, sizeof(char*), compare_str);
//запись сортировки с начала
	for(int i = 0; i < strcount; i++){
		fputs(strings[i], fdestination);
		fputc('\n', fdestination);
	}
//сортировка с конца
/*	for (int i = 0; i < strcount - 1;){
		int value = fstrcmp(strings[i], strings[i + 1]);
		if (value == 1){
			char *tmp = strings[i];
			strings[i] = strings[i + 1];
			strings[i + 1] = tmp;
			if (i > 0)
				i--;
		}
		else if (value == -1 || value == 0;)
			i++;
	}*/
	qsort(strings, strcount, sizeof(char*), compare_str_re);
//запись сортировки с конца
	for (int i = 0; i < strcount; i++){
		fputs(strings[i], fdestination);
		fputc('\n', fdestination);
	}
//запись в файл оригинала
	for (int i = 0; i < strcount; i++){
		fputs(stringscopy[i], fdestination);
		fputc('\n', fdestination);
	}
	fclose(fdestination);
	for (int i = 0; i < strcount; i++)
		free(strings[i]);
	free(strings);
	return 0;
}

int fstrcmpfromback(const char *first, const char *second){
	int i = 0, j = 0;
	while(first[i] != '\0')
		i++;
	while(second[j] != '\0')
		j++;
	while(i >= 0 && j >= 0){
		if (!isalpha(first[i])){
			i--;
			continue;
		}
		if (!isalpha(second[j])){
			j--;
			continue;
		}
		int a = tolower(first[i]);
		int b = tolower(second[j]);
		if (a < b)
			return -1;
		else if (a > b)
			return 1;
		else {
			i--;
			j--;
			continue;
		}
	}
	if (i >= 0)
		return -1;
	else if (j >= 0)
		return 1;
	return 0;
}

int compare_str_re (const void *a, const void *b){
	const char **str1 = (const char **)a;
	const char **str2 = (const char **)b;
	return fstrcmpfromback(*str1, *str2);
}
int compare_str(const void *a, const void *b){
	const char **str1 = (const char **)a;
	const char **str2 = (const char **)b;
	return fstrcmp(*str1, *str2);
}

int fstrcmp(const char *first, const char *second){
	int i = 0, j = 0;
	while(first[i] != '\0' && second[j] != '\0'){
		if (!isalpha(first[i])){
			i++;
			continue;
		}
		if (!isalpha(second[j])){
			j++;
			continue;
		}
		int a = tolower(first[i]);
		int b = tolower(second[j]);
		if (a < b)
			return -1;
		else if (a > b)
			return 1;
		else {
			i++;
			j++;
			continue;
		}
	}
	if (first[i] == '\0' && second[j] == '\0')
		return 0;
	else if (first[i] == '\0')
		return -1;
	return 1;
}
