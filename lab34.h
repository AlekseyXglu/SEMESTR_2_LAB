#ifndef lab34_H
#define lab34_H
struct Lst 
{
	Lst* next;
	int data;
};
struct ListT 
{
	Lst* Tail;
	Lst* Head;
	int N = 0;
};
void init(ListT &l);
int Empty(ListT l);
void Push(ListT &l, int s);
int Print(ListT l);
void Del(ListT &l, Lst* t);
void Free(ListT &l);
int length(ListT l);
Lst* poisk(ListT l, int a);
void fives();

#endif