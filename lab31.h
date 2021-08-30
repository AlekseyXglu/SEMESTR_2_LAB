#ifndef lab31_H
#define lab31_H
struct LE
{
    int v;
    struct LE* next;
};
struct StackList 
{
	LE* top;
};
void initStackLIST(StackList& s);
int PushStackList(StackList& s, int a);
int PopStackList(StackList& s);
int Peek(StackList& s);
bool IsEmptyStack(StackList& s);
void Clear(StackList& s);
void PrintStack(StackList& s);
int FREE(StackList& l);
void second();

#endif