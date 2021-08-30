#ifndef lab33_H
#define lab33_H
struct El_List
{
	int data;
	El_List* next;
};
struct List
{
	El_List* head;
};

void InitList(List& l);
void AddBegin(List& l, int n);
void AddEnd(List& l, int n);
void Print(List l);
void delElem(List& l, El_List* s);
void vstavka(List& s);
void fours();


#endif