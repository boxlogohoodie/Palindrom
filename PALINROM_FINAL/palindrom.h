#pragma

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define _CRT_SECURE_NO_WARNINGS
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

FILE *f;

void symbol_correct(wchar_t *str, size_t index);
int search_new_line(wchar_t *str, unsigned int start_line);
int check_type_palindrom(wchar_t *str, int mp);
void delete_other_symbol(wchar_t *str, int index);
void delete_all_other_symbols(wchar_t *str);
void symbol_check_all(wchar_t *str);
void symbol_check(wchar_t *str, size_t index);
void search_subpalindrome(wchar_t *str, int lp, int rp);
void palindrom_task1(wchar_t *str);
void palindrom_task2(wchar_t *str);
void palindrom_task3(wchar_t *str);
void text_correct_all(wchar_t *str);
void print_line(int start, int end, wchar_t *str);
void menu(void); 
