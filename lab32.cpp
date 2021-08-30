#include <stdio.h>
#include <malloc.h>
#include "lab32.h"
void initQuaue(Quaue& q)
{
	q.Head = NULL;
	q.Tail = NULL;
}
int isempty(Quaue& q)
{
	if (q.Head == NULL)
		return 1;
	else
		return 0;
}
void Print(Quaue& q)
{
	struct LstQ* h;
	if (isempty(q) == 1)
	{
		printf("\nОчередь пуста!\n");
		return;
	}
	for (h = q.Head; h != NULL; h = h->next)
		printf("%d ", h->data);
	return;
}
void Push(Quaue& q, int a)
{
	LstQ* p = (LstQ*)malloc(sizeof(LstQ));
	p->data = a;
	p->next = NULL;
	if (q.Head == NULL && q.Tail == NULL)
	{
		q.Tail = p;
		q.Head = q.Tail;
	}
	else 
	{
		q.Tail->next = p;
		q.Tail = p;
	}
}
int Pop(Quaue& q)
{
	if (q.Head == NULL)
		return 0;
	int a = q.Head->data;
	LstQ* p = q.Head;
	q.Head = q.Head->next;
	free(p);
	return a;
}
void sqrChet(Quaue& q)
{
	LstQ* p;
	p = q.Head;
	while (p != NULL)
	{
		if (p->data % 2 == 0)
			p->data *= p->data;
		p = p->next;
	}
}
void third()
{
	Quaue q;
	int n,a;
	initQuaue(q);
	do {
		printf("Введите кол-во элементов\n");
		scanf_s("%d", &n);
	} while (n < 0);
	for (int i = 0; i < n; i++)
	{
		printf("Введите элемент %d: ",i+1);
		scanf_s("%d", &a);
		Push(q, a);
	}
	Print(q);
	printf("\n");
	sqrChet(q);
	Print(q);
	printf("\n");
}

