#ifndef lab30_H
#define lab30_H
struct StackMas
{
	int* A;
	int l;
	int top;
};

void initStack(StackMas &s, int l);
void PrintStack(StackMas& s);
void Destruct(StackMas &s);
int Push(StackMas &s, int a);
int Pop(StackMas &s);
int Peek(StackMas &s);
void Clear(StackMas &s);
int IsEmptyStack(StackMas &s);
void FREE(StackMas& s);
void first();

#endif