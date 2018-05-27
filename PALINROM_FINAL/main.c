#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "palindrom.h"

int main(int argc, char *argv[]) {
	const char * in_file_name = NULL;
	if (argc != 2) {
		printf("Incorrect input, try again. (Example: ./prog *.txt\n");
		return 0;
	}
	in_file_name = argv[1];
	setlocale(LC_ALL, "RUS");
	f = fopen(in_file_name, "r");
	if (f == NULL) {
		printf("Error open file");
		return 0;
	}
	fseek(f, 0, SEEK_END);
	unsigned int text_size = ftell(f);
	rewind(f);
	unsigned int i = 0;
	wchar_t *str = (wchar_t*)malloc(sizeof(wchar_t)* text_size);
	while (!feof(f)) {
		str[i] = fgetwc(f);
		i++;
	}
	str[i] = '\0';
	menu();
	int m = 1;
	while (m != 0) {
		scanf("%d", &m);
		switch (m) {
		case 1:
			printf("***** CHECK ALL TEXT *****\n");
			palindrom_task1(str);
			break;
		case 2:
			printf("***** EVERY SENTENCE *****\n");
			palindrom_task2(str);
			break;
		case 3:
			printf("***** SEARCH ALL SUBPALINDROMES *****\n");
			palindrom_task3(str);
			break;
		case 9:
			menu();
			break;
		case 0:
			return 0;
		default:
			printf("Incorrect input, try again\n");
			break;
		}
	}
	fclose(f);
	return 0;
}
