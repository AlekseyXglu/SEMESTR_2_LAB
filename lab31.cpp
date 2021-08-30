#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <ctype.h>
#include "lab31.h"
#pragma warning(disable : 4996)
void initStackLIST(StackList &s)
{
	LE* t = (LE*)malloc(sizeof(LE));
	t->next = NULL;
	t->v = 0;
	s.top = t;
}
int PushStackList(StackList &s, int a)
{
	LE* t = (LE*)malloc(sizeof(LE));
	if (s.top)
	{
		t->next = s.top->next;
		t->v = a;
		s.top->next = t;
		return 1;
	}
	return 0;
}
int PopStackList(StackList& s)
{
	LE* t;
	int x;
	if (s.top->next)
	{
		x = s.top->next->v;
		t = s.top->next;
		s.top->next = t->next;
		free(t);
		return x;
	}
	return 1e300;
}
int Peek(StackList& s)
{
	if (!s.top->next)
		return 1e300;
	else
	{
		return s.top->next->v;
	}
}
bool IsEmptyStack(StackList &s)
{
	return s.top->next == NULL;
}
void Clear(StackList &s)
{
	while (!IsEmptyStack(s))
	{
		PopStackList(s);
	}
}
void PrintStack(StackList &s)
{
	LE* t;
	if (s.top->next)
	{
		t = s.top->next;
		while (t != NULL)
		{
			printf("%d ",t->v);
			t = t->next;
		}
		printf("\n");
	}
}

int FREE(StackList &l) 
{
	if (IsEmptyStack(l)) 
	{
		return -1;
	}
	LE* tmp = l.top;
	while (tmp->next != NULL)
	{
		LE* t = tmp;
		tmp = tmp->next;
		free(t);
	}
	l.top = NULL;
	return 1;
}
void second()
{
	int flag=0, temp,a;
	long long sum = 0, pr = 1;
	char c;
	StackList stack;
	initStackLIST(stack);
	while(c = getch())
	{
		printf("%c",c);
		if (flag == 0 && int(c) >= 49 && int(c) <= 57)
		{
			PushStackList(stack, int(c) - 48);
			flag = 1;
			continue;
		}
		if (flag == 1 && int(c) >= 48 && int(c) <= 57)
		{
			PushStackList(stack, int(c) - 48);
		}
		if (c == ' ') break;
	}
	if (flag == 0) PushStackList(stack, 0);
	printf("\n");
		PrintStack(stack);
		while (stack.top->next != NULL)
		{
			temp = PopStackList(stack);
			sum += temp;
			pr *= temp;
		}
	printf("Сумма: %d, произведение: %d\n", sum, pr);
	FREE(stack);
}