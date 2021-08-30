#include "lab34.h"
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>
void init(ListT &l)
{
	l.Head = NULL;
	l.Tail = NULL;
	l.N = 0;
}
int Empty(ListT l) 
{
	if(l.N == 0)
		return 1;
	return 0;
}
void Push(ListT &l, int s) 
{
	Lst* p = (Lst*)malloc(sizeof(Lst));
	p->data = s;
	if (l.Head == NULL)
	{
		l.Head = p;
		l.Tail = p;
	}
	else 
	{
		l.Tail->next = p;
		l.Tail = l.Tail->next;
		l.Tail->next = l.Head;
	}
}
int Print(ListT l)
{
	if (l.Head == NULL)
		return -1;
	Lst* p = l.Head;
	for (int i = 0; i < l.N; i++) 
	{
		printf("%d ",p->data);
		p = p->next;
	}
	return 1;
}

void Del(ListT &l, Lst *t) 
{
	Lst* p = t->next;
	p->next = p->next->next;
	free(p);
	l.N--;
}
void Free(ListT &l) 
{
	Lst* t;
	Lst* tmp;
	if (!Empty(l))
	{
		t=tmp = l.Head;
		for (int i = 0; i < l.N; i++)
		{
			tmp = tmp->next;
			free(t);
			t = tmp;
		}
		l.Head = NULL;
		l.Tail = NULL;
		l.N = 0;
	}
}
int length(ListT l)
{
	if (Empty(l)) 
	{
		return 0;
	}
	int k = 0;
	Lst* temp = l.Head;
	Lst* tmp = temp->next;
	int N = 1;
	while (temp != tmp) 
	{
		tmp = tmp->next;
		N++;
	}
	return N;
}
Lst* poisk(ListT l,int a)
{
	Lst* tmp = l.Head;
	if (Empty(l)) return 0;
	for (int i = 0; i < l.N; i++)
	{
		if (tmp->data == a)
			return tmp;
	}
	return 0;
}
void fives()
{
	srand(time(NULL));
	ListT s;
	int n;
	init(s);
	do {
		printf("¬ведите кол-во элементов в кольце:\n");
		scanf_s("%d", &n);
	}while(n <= 0);
	s.N = n;
	for (int i = 0; i < n; i++) 
	{
		Push(s, rand() % 100+1);
	}
	Lst* t= s.Head;
	printf("»сходное кольцо:\n");
	Print(s);
	int x = rand() % 10+1;
	for (int i = 0; i < x; i++) 
	{
		for (int j = 0; j < n; j++)
		{
			if (t->data % 5 == 0) 
			{
				t->data = rand() % 100+1;
			}
			if(n!=1)
			t = t->next;
		}
	}
	printf("\n„ерез %d операций.\n",n);
	Print(s);
	printf("\n");
	Free(s);
}