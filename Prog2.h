#ifndef Prog2_H
#define Prog2_H
struct Ragged_Array
{
	int **a;
	int *m;
	int n;
};
void input(Ragged_Array arr);
void output(Ragged_Array arr);
void del(Ragged_Array arr, int l, int k);
void func_arr(Ragged_Array arr);
void third();
#endif 
