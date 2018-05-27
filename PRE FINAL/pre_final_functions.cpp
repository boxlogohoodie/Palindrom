#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include "palindrom.h"


//******** 1 part ********//
void text_correct_all(wchar_t *str)
{
	for (int i = 0; i < wcslen(str); i++)
	{
		symbol_correct(str, i);
	}
}

void symbol_correct(wchar_t *str, size_t index)
{
	if (iswupper(str[index]))
		str[index] = str[index] + 0x020;
}

void palindrom_task1(wchar_t *str)
{
	unsigned int start, end, status = 1;
	end = wcslen(str) - 1;
	text_correct_all(str);
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
		printf("It is not palindrom\n");
}

void menu() {
	printf("Palindrom menu\n");
	printf("Choose function\n");
	printf("1.Check all text\n");
	printf("2.Check every sentence in text\n");
	printf("3.Search all subpalindromes\n");
	printf("Press 9 for call menu again or 0 for exit\n");
}

// ********** 2part ***********//

void symbol_check(wchar_t *str, size_t index) {
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

void symbol_check_all(wchar_t *str) {
	for (int i = 0; i < wcslen(str); i++)
	{
		symbol_check(str, i);
	}
}

void palindrom_task2(wchar_t *str) {
	unsigned int start = 0;
	bool eof_status = 1;
	while (eof_status) {
		int status = 1;
		unsigned int end = search_new_line(str, start) - 1;
		for (start; start < end; start++, end--)
		{
			if (str[start] != str[end]) {
				status = 0;
				continue;
			}
		}
		if (status) {
			printf("It is palindrom\n"); //++ надо распечатать то предложение которое он проверил
		}
		else
			printf("It is not palindrom\n");
		if (str[search_new_line(str, start)] == '\0') {
			eof_status = 0;
			continue;
		}
		start = search_new_line(str, start) + 1;
		while (str[start] == '\n') {
			start++;

		}
	}
}

int search_new_line(wchar_t *str, unsigned int start_line) {
	unsigned int new_line = start_line;
	while (str[new_line] != '\n' && str[new_line] != '\0') {
		new_line++;
	}
	return new_line;
}

// ********** 3part ***********//

void delete_all_other_symbols(wchar_t *str) {
	for (int i = 0; i < wcslen(str); i++) {
		delete_other_symbol(str, i);
	}
}

void delete_other_symbol(wchar_t *str, int index)
{
	if (str[index] >= RU_U_S && str[index] <= RU_L_E) {
		symbol_correct(str, index);
	}
	else if ((str[index] >= EN_U_S && str[index] <= EN_U_E)
		|| (str[index] >= EN_L_S && str[index] <= EN_L_E))
	{
		symbol_correct(str, index);
	}
	else {
		for (int i = index; str[i] != '\0'; i++) {
			str[i] = str[i + 1];
		}
		if (str[index] != '\0')
			delete_other_symbol(str, index);
	}
}

void palindrom_task3(wchar_t *str) {
	for (int i = 0; i < wcslen(str); i++) {
		int type = check_type_palindrom(str, i);
		int lp, rp;
		switch (type)
		{
		case ODD:
			lp = i - 1;
			rp = i + 1;
			search_subpalindrome(str, lp, rp);
			break;
		case EVEN:
			lp = i;
			rp = i + 1;
			search_subpalindrome(str, lp, rp);;
		default:
			break;
		}
	}

}

void search_subpalindrome(wchar_t *str, int lp, int rp) {
	while (str[rp] == str[lp]) {
		if (lp >= 0 && str[rp] != '\0') {
			lp--;
			rp++;
		}
	}
	lp++;
	rp--;
	wchar_t *p1 = (wchar_t*)malloc((rp - lp + 2) * sizeof(wchar_t)); //тут нужно сделать запись в файл
																	 // и если надо выделить правильно память
	for (int i = 0; lp <= rp; lp++, i++) {
		p1[i] = str[lp];
	}
	free(p1);
}

int check_type_palindrom(wchar_t *str, int mp) {
	int lp = mp--, rp = mp++;
	if (lp >= 0 && rp != '\0') {
		if (str[lp] == str[rp])
			return ODD;
		else if (str[mp] == str[rp])
			return EVEN;
		else return NOPE;
	}
	else
		return NOPE;
}