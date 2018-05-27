#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include "Header.h"


#define RU_U_S 0x0410
#define RU_U_E 0x042f
#define RU_L_S 0x0430
#define RU_L_E 0x044f
#define EN_U_S 0x0041
#define EN_U_E 0x005A
#define EN_L_S 0x0061
#define EN_L_E 0x007A
#define COMMA 0x002C
#define POINT 0x002F
#define EXC 0x0021 // восклицательный знак
#define QUE 0x003F // вопросительный




void palimrom_task2(wchar_t *);		//удаляет все знаки препинания, проверяет каждое предложение на свойство палиндрома
void palindrom_task3(wchar_t *);	//удаляет все пробелы и знаки, проводит поиск всех подпалидромов.
void delete_other_symbols(wchar_t *str);
void symbol_check(wchar_t *str, size_t index);
void subpalindromes(wchar_t *str);

int main() {
	wchar_t i = 0x0410;
	for (int n = 0; n < 40; n++) {
		i++;
	}
	wchar_t rawn[] = L"Хуес135ососеух";
	//delete_other_symbols(rawn);
	//palindrom_task1(rawn);
	subpalindromes(rawn);
	char string[] = "nowwon";
	//palindrom_task1(string);
	/*int m;
	menu();
	while (m != 0) {
		scanf_s("%d", &m);
		switch (m)
		{
		case 1:
			palindrom_task1(string);
			break;
		case 2:
			palindrom_task2(string);
			break;
		case 3:
			palindrom_task3(string);
			break;
		case 9:
			menu();
			break;
		case 0:
			return 0;
		default:
			printf("Incorrect input, try again");
			break;
		}*/
	_getch();
	return 0;
}

void symbol_correct(wchar_t *str, size_t index)
{
		if (iswupper(str[index]))
			str[index] = str[index] + 0x020;
}

void symbol_check(wchar_t *str, size_t index) {
	/*if (str[index] >= RU_U_S && str[index] <= RU_L_E) {
		symbol_correct(str, index);
	}
	else if ((str[index] >= EN_U_S && str[index] <= EN_U_E) 
				|| (str[index] >= EN_L_S && str[index] <= EN_L_E)) {
		symbol_correct(str, index);}*/
	symbol_correct(str, index);
	
	if (str[index] == COMMA) {
		for (int i = index; str[i] != '\0'; i++) {
			str[i] = str[i + 1];	
		}
		if (str[index] != '\0')
			symbol_check(str, index);	
	}
	else if (str[index] == POINT || str[index] == EXC || str[index] == QUE) {
		str[index] = '\n';
	}
}

void subpalindromes(wchar_t *str) {
	delete_other_symbols(str);
	for (int mp = 0; str[mp] != '\0'; mp++) {
		int lp = mp-1;
		int rp = mp+1;
			while (lp >= 0 && str[rp] != '\0') 
				{
				if (lp == rp)
				{
					rp++;
					lp--;
				}
				else
					continue;
			}
			printf("\n");
	}
}







void delete_other_symbols(wchar_t *str) {
	for (int i = 0; i < wcslen(str); i++) {
		symbol_check(str, i);
	}
}

void palindrom_task1(wchar_t *str)
{
	
	unsigned int start, end, status = 1;
	end = wcslen(str);
	for (start = 0; start < end; start++, end--)

	{
	if (str[start] != str[end]) {
			status = 0;
			continue;
		}
	}
	if (status) {
		printf("It is palindrom\n");
	}
	else
		printf("No\n");
}

void menu() {
	printf("Palindrom menu\n");
	printf("Choose function\n");
	printf("1.Check all text\n");
	printf("2.Check every sentence in text\n");
	printf("3.Search all subpalindromes\n");
	printf("Press 9 for call menu again or 0 for exit\n");
}



