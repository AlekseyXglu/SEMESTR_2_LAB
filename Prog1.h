#ifndef Prog1_H
#define Prog1_H
struct Array
{
	int *a;
	int n,m;
};

struct Array1
{
	int **a;
	int n,m;
};

void input_arr(Array arr);
void output_arr(Array arr);
double sred_arifm(Array arr, int& k);
void first();

void input_arr1(Array1 arr);
void output_arr1(Array1 arr);
double sred_arifm1(Array1 arr, int& k);
void second();
#endif 

