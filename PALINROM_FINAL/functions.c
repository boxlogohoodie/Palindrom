#include "palindrom.h"
#define _CRT_SECURE_NO_WARNINGS
void symbol_correct(wchar_t *str, size_t index);
int search_new_line(wchar_t *str, unsigned int start_line);

//******** 1 part ********//
void print_line(int start, int end, wchar_t *str) {
	for (; start <= end; start++) {
		fputwc(str[start], stdout);
	}
}

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
	fseek(f, 0, SEEK_END);
	end = ftell(f) - 1;
	rewind(f);
	text_correct_all(str);
	for (start = 0; start < end; start++, end--)

	{
		while (str[start] == ' ')
			start++;
		while (str[end] == ' ')
			end--;
		if (str[start] != str[end]) {
			status = 0;
			continue;
		}
	}
	if (status) {
		printf("It is palindrom\n");
		fputws(str, stdout);
	}
	else {
		printf("It is not palindrom\n");
		fputws(str, stdout);
	}
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
	else if (str[index] == '.' || str[index] == EXC || str[index] == QUE) {
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
	symbol_check_all(str);
	int eof_status = 1;
	while (eof_status) {
		int status = 1;
		unsigned int end = search_new_line(str, start) - 1;
		int pst = start, pend = end;
		if (str[search_new_line(str, start)] == '\0') {
			eof_status = 0;
			continue;
		}
		for (start; start < end; start++, end--)
		{
			while (str[start] == ' ')
				start++;
			while (str[end] == ' ')
				end--;
			if (str[start] != str[end]) {
				status = 0;
				continue;
			}
		}
		if (status) {
			print_line(pst, pend, str);
			printf(" - It is palindrom\n");
		}
		else {
			print_line(pst, pend, str);
			printf(" - It is not palindrom\n");
		}
		start = search_new_line(str, start) + 1;
		while (str[start] == '\n') {
			start++;

		}
		while (str[start] == ' ')
			start++;
	}
}

int search_new_line(wchar_t *str, unsigned int start_line) {
	unsigned int new_line = start_line;
	while (str[new_line] != '\n' && str[new_line] != '\0') {
		new_line++;
	}
	return new_line;
}

// *********** part 3 **************//

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
	delete_all_other_symbols(str);
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

void print_in_file(int start, int end, wchar_t* str, FILE *o) {
	for (; start <= end; start++) {
		fseek(o, 0, SEEK_END);
		fputwc(str[start], o);
	}
	fputwc('\n', o);
	rewind(o);
}

void search_subpalindrome(wchar_t *str, int lp, int rp) {
	int n = 0;
	while (str[rp] == str[lp]) {
		if (lp >= 0 && str[rp] != '\0') {
			lp--;
			rp++;
			n++;
		}
	}
	lp++;
	rp--;
	if (n > 0) {
		print_in_file(lp, rp, str, stdout);
	}

}

int check_type_palindrom(wchar_t *str, int mp) {
	int lp = mp - 1, rp = mp + 1;
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