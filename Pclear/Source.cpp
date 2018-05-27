#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>


void palindrom_task1(wchar_t *str);
void print_array(wchar_t *str);
void text_correct_all(wchar_t *str);
void symbol_correct(wchar_t *str, size_t index);

int main(void)
{
	wchar_t str[] = L"хуесососеух";
	wchar_t str1[] = L"’уесососеух";
	wchar_t str2[] = L"’уесосос123еух";
	palindrom_task1(str);
	palindrom_task1(str1);
	palindrom_task1(str2);
	return 0;
}

void text_correct_all (wchar_t *str)
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
		print_array(str);
	}
	else
		printf("It is not palindrom\n");
}

void print_array(wchar_t *str) 
{
		wprintf(L"%ls", str);
	printf("\n");
}