#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#define INIT_CAP 100
#define MAX_LINE 256

int fstrcmpfromback(const wchar_t *first, const wchar_t *second);
int compare_str_re (const void *a, const void *b);
int compare_str (const void *a, const void *b);
int fstrcmp(const wchar_t *first, const wchar_t *second);

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
	wchar_t **strings = (wchar_t **)malloc(INIT_CAP * sizeof(wchar_t *));
	int cap = INIT_CAP, strcount = 0;
	wchar_t Buf[MAX_LINE];
	while (fgetws(Buf, sizeof(Buf), fsource)){
		Buf[wcslen(Buf) - 1] = L'\0';
		if (strcount >= cap){
			cap *= 2;
			strings = (wchar_t **)realloc(strings, cap * sizeof(wchar_t *));
		}
		strings[strcount] = (wchar_t *)malloc((wcslen(Buf) + 1) * sizeof(wchar_t));
		wcscpy(strings[strcount], Buf);
		strcount++;
	}
	strings = (wchar_t **)realloc(strings, strcount * sizeof(wchar_t *));
	fclose(fsource);
//копия для вставки в конец файла изначального варианта строк
	wchar_t **stringscopy = (wchar_t **)malloc(strcount * sizeof(wchar_t *));
	for (int i = 0; i < strcount; i++)
		stringscopy[i] = strings[i];
// сортировка с начала
	FILE *fdestination = fopen("outfile2.txt", "w");
	qsort(strings, strcount, sizeof(wchar_t*), compare_str);
//запись сортировки с начала
	for(int i = 0; i < strcount; i++){
		fputws(strings[i], fdestination);
		fputwc('\n', fdestination);
	}
//сортировка с конца
	qsort(strings, strcount, sizeof(wchar_t*), compare_str_re);
//запись сортировки с конца
	for (int i = 0; i < strcount; i++){
		fputws(strings[i], fdestination);
		fputwc('\n', fdestination);
	}
//запись в файл оригинала
	for (int i = 0; i < strcount; i++){
		fputws(stringscopy[i], fdestination);
		fputwc('\n', fdestination);
	}
	fclose(fdestination);
	for (int i = 0; i < strcount; i++)
		free(strings[i]);
	free(strings);
	return 0;
}

int fstrcmpfromback(const wchar_t *first, const wchar_t *second){
	int i = 0, j = 0;
	while(first[i] != '\0')
		i++;
	while(second[j] != '\0')
		j++;
	while(i >= 0 && j >= 0){
		if (!iswalpha(first[i])){
			i--;
			continue;
		}
		if (!iswalpha(second[j])){
			j--;
			continue;
		}
		int a = towlower(first[i]);
		int b = towlower(second[j]);
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
		return 1;
	else if (j >= 0)
		return -1;
	return 0;
}

int compare_str_re (const void *a, const void *b){
	const wchar_t **str1 = (const wchar_t **)a;
	const wchar_t **str2 = (const wchar_t **)b;
	return fstrcmpfromback(*str1, *str2);
}
int compare_str(const void *a, const void *b){
	const wchar_t **str1 = (const wchar_t **)a;
	const wchar_t **str2 = (const wchar_t **)b;
	return fstrcmp(*str1, *str2);
}

int fstrcmp(const wchar_t *first, const wchar_t *second){
	int i = 0, j = 0;
	while(first[i] != '\0' && second[j] != '\0'){
		if (!iswalpha(first[i])){
			i++;
			continue;
		}
		if (!iswalpha(second[j])){
			j++;
			continue;
		}
		int a = towlower(first[i]);
		int b = towlower(second[j]);
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
