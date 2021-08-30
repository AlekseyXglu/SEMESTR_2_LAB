#include <stdio.h>
#include <locale.h>
#include "lab30.h"
#include "lab31.h"
#include "lab32.h"
#include "lab33.h"
#include "lab34.h"
int main()
{
	setlocale(0, "");
	int n;
	do{
		do{
			printf("¬ведите номер лабораторной(30-34) или 0 дл€ выхода:\n");
			scanf_s("%d", &n);
		}while ((n < 30 || n>34) && n != 0);
		switch (n)
		{
		case 30: first(); break;
		case 31: second(); break;
		case 32: third(); break;
		case 33: fours(); break;
		case 34: fives(); break;
		}		
	}while (n != 0);
	

	return 0;
}