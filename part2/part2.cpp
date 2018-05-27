#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>



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
#define ODD 1
#define EVEN 2
#define NOPE 0
void symbol_correct(wchar_t *str, size_t index);
int search_new_line(wchar_t *str, unsigned int start_line);
int check_type_palindrom(wchar_t *str, int mp);
void delete_other_symbol(wchar_t *str, int index);
void delete_all_other_symbols(wchar_t *str);
void search_subpalindrome(wchar_t *str, int lp, int rp);

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

void symbol_correct(wchar_t *str, size_t index)
{
	if (iswupper(str[index]))
		str[index] = str[index] + 0x020;
}

void symbol_check_all(wchar_t *str) {
	for (int i = 0; i < wcslen(str); i++)
	{
		symbol_check(str, i);
	}

}

void palindrom_task1(wchar_t *str)
{
	unsigned int start, end, status = 1;
	end = wcslen(str) - 1;
	symbol_check_all(str);
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
				printf("It is palindrom\n");
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
	else{
		for (int i = index; str[i] != '\0'; i++) {
				str[i] = str[i + 1];
			}
		if (str[index] != '\0')
			delete_other_symbol(str, index);
		}
}


void task3(wchar_t *str) {
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

/*void for_even(wchar_t *str,int mp) {
	int lp = mp, rp = mp + 1;
	while (str[rp] == str[lp]) {
		if (lp >= 0 && str[rp] != '\0') {
			lp--;
			rp++;
		}
	}
	lp++;
	rp--;
	//вывод в файл со счетчиком знаков
}*/


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


int main(void) {
	FILE* f = fopen("Text.txt", "r");
	unsigned int N = 10, delta = 1, i = 0;
	wchar_t* buf = (wchar_t*)malloc(sizeof(wchar_t)*N);
	while ((buf[i] = fgetwc(f)) != EOF) {
		if (++i > N) {
			N += delta;
			buf = (wchar_t*)realloc(buf, sizeof(wchar_t)*N);
		}
	}
	fclose(f);
	buf[i] = '\0';
	delete_all_other_symbols(buf);
	task3(buf);
	_putws(buf);
	//symbol_check_all(str);
	//palindrom_task2(str);
	return 0;
}

