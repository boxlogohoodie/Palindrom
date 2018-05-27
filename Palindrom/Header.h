#include <wchar.h>

#define RU_U_S 0x0410
#define RU_U_E 0x042f
#define RU_L_S 0x0430
#define RU_L_E 0x044f
#define EN_U_S 0x0041
#define EN_U_E 0x005A
#define EN_L_S 0x0061
#define EN_L_E 0x007A

void menu(void);
void palindrom_task1(wchar_t *); //проверяет является ли весь текст файла палиндромом (имеется приведение к нижнему регистру)
