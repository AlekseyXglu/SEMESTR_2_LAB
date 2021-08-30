#include <malloc.h>
#include <stdio.h>
#include "lab33.h"
#pragma warning(disable : 4996)
void InitList(List& l)
{
	El_List* t = (El_List*)malloc(sizeof(El_List));
	t->next = NULL;
	t->data = 0;
	l.head = t;
}
void AddBegin(List& l, int n)
{
	El_List* t = (El_List*)malloc(sizeof(El_List));
	t->next = l.head->next;
	t->data = n;
	l.head->next = t;
}
void AddEnd(List& l, int n)
{
	El_List* t = (El_List*)malloc(sizeof(El_List));
	El_List* tmp;	
	if (l.head)
	{
		t->next = NULL;
		t->data = n;
		tmp = l.head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = t;
	}
}
void Print(List l)
{
	El_List* t;
	t = l.head;
	while (t->next != NULL)
	{
		printf("%d ", t->next->data);
		t = t->next;
	}
	printf("\n");
}

void delElem(List &l,El_List*s)
{
	El_List* p,*t;
	p = l.head->next;
	while (p->next != s)
		p = p->next;
	t = p->next;
	p->next = p->next->next;
	free(t);
}

void vstavka(List &l,int a)
{
	int k = 1,q;
	El_List *t;
	El_List* p = (El_List*)malloc(sizeof(El_List));
	t = l.head->next;
	while(k)
	{
		if (t->data >= a)
		{
			p->data = a;
			l.head->next = p;
			p->next = t;
			k = 0;
		}
		else
		if(t->next==NULL)
		{
			p->data = a;
			p->next = NULL;
			t->next = p;
			k = 0;
		}
		else
		if (t->data <= a && t->next->data>=a)
		{
			{
				p->data = a;
				p->next = t->next;
				t->next = p;
				k = 0;
			}
		}
		t = t->next;		
	}

	t = l.head->next;
	q = l.head->next->data;
	while(t->next!=NULL)
	{
		if (t->next->data == q)
		{
			delElem(l, t->next);
		}
		else q = t->next->data;
		if(t->next!=NULL)
		t = t->next;
	}

}

void fours()
{
	List s;
	int n,x1,x2,p,l;
	int i = 0;
	char c;
	InitList(s);
	do {
		do {
			printf("Введите 1, чтобы ввести с клавиатуры, 2-из файла\n");
			scanf("%d", &l);
		} while (l != 1 && l != 2);
		if (l == 1)
		{
			do {
				printf("Введите кол-во элементов в списке:\n");
				scanf("%d", &n);
			} while (n <= 0);

			printf("Введите элемент %d:\n", i + 1);
			scanf("%d", &x1);
			AddEnd(s, x1);

			for (i = 1; i < n; i++)
			{
				do {
					printf("Введите элемент %d:\n", i + 1);
					scanf("%d", &x2);
					if (x1 <= x2) AddEnd(s, x2);
				} while (x1 > x2);
				x1 = x2;
			}
		}
		else
		{
			if (l == 2)
			{
				FILE* f = fopen("text33.txt", "r");
				while (!feof(f))
				{
					fscanf(f, "%d", &p);
					AddEnd(s, p);
				}
				fclose(f);
			}
		}
	} while (l != 1 && l != 2);
	printf("Начальный список\n");
	Print(s);
	do {
		printf("Введите Y, чтобы добавить элемент, иначе N:\n");
		getchar();
		c = getchar();
		if (c == 'Y')
		{
			printf("Введите элемент:\n");
			scanf_s("%d", &p);
			vstavka(s, p);
		}
	} while (c != 'N');
	printf("Конечный список\n");
	Print(s);

}