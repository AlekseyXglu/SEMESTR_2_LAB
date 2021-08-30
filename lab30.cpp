#include <malloc.h>
#include <stdio.h>
#include <conio.h>
#include "lab30.h"
#pragma warning(disable : 4996)
void initStack(StackMas &s, int l)
{
	if (s.A = (int*)malloc(l * sizeof(int)))
	{		
		s.l = l;
	}
	else s.l = -1;
	s.top = -1;
}
void PrintStack(StackMas &s)
{
	for (int i = s.top; i >=0; i--)
		printf("%d ",(s.A)[i]);
	printf("\n");
}
void Destruct(StackMas &s)
{
	if (s.A) free(s.A);
	s.l = -1;
	s.top = -1;
}
int Push(StackMas &s,int a) //положить
{
	if (s.top >= s.l - 1) return 0;
	s.top++;
	s.A[s.top] = a;
	return 1;
}
int Pop(StackMas &s)	//достать
{
	if (s.top >= 0)
		return s.A[s.top--];
	else return 1e300;
}
int Peek(StackMas &s)	//посмотреть верхний элемент
{
	if (s.top >= 0)
		return s.A[s.top];
	else return 1e300;
}
void Clear(StackMas &s) 
{
	s.top = -1;
}
int IsEmptyStack(StackMas &s)
{
	if (s.top < 0) return 1;
	else return 0;
}
void FREE(StackMas &s)
{
	if (s.A != NULL)
		free(s.A);
	s.A = NULL;
	s.l = 0;
	s.top = -1;
}

void first()
{
	int flag=0,a,temp;
	long long sum = 0, pr = 1;
	char c;
	StackMas stack;
	initStack(stack, 100);
	while (c = getch())
	{
		printf("%c", c);
		if (flag == 0 && int(c) >= 49 && int(c) <= 57)
		{
			Push(stack, int(c) - 48);
			flag = 1;
			continue;
		}
		if (flag == 1 && int(c) >= 48 && int(c) <= 57)
		{
			Push(stack, int(c) - 48);
		}
		if (c == ' ') break;
	}
	if (flag == 0) Push(stack, 0);
		printf("\n");
		PrintStack(stack);
		while (stack.top >= 0)
		{
			temp = Pop(stack);
			sum += temp;
			pr *= temp;
		}
	
	printf("Сумма: %d, произведение: %d\n", sum, pr);
	FREE(stack);
} 