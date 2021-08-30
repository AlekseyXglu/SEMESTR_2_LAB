#ifndef lab32_H
#define lab32_H
struct LstQ
{
	LstQ* next;
	int data;
};
struct Quaue
{
	LstQ* Head;
	LstQ* Tail;
};
void initQuaue(Quaue& q);
int isempty(Quaue& q);
void Print(Quaue& q);
void Push(Quaue& q, int a);
int Pop(Quaue& q);
void sqrChet(Quaue& q);

void third();
#endif