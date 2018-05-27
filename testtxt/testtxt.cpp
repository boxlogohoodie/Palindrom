#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include<locale.h>  
	

int main() {
	setlocale(LC_ALL, "RUS");
	FILE* f = fopen("Text.txt", "r"); //qwerty‡·‚
	wchar_t **str = (wchar_t**)malloc(sizeof(wchar_t*));
	int n = 0;
	while (!feof(f))
	{
		str[n] = (wchar_t*)malloc(sizeof(wchar_t) * 256);
		fgetws(str[n], 256, f);
		n++;
		str = (wchar_t**)realloc(str, sizeof(wchar_t*)*(n + 1));
	}
	fclose(f);
	return 0;
}