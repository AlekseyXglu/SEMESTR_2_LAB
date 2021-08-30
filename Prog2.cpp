#include "Prog2.h"
#include <stdio.h>
#include <malloc.h>

void input(Ragged_Array arr)
{
	printf("\n");
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m[i];j++)
		{
			printf_s("Введите элемент строки %d и столбца %d: ",i+1,j+1);
			scanf_s("%d",&arr.a[i][j]);
		}
	}
	printf("\n");
}

void output(Ragged_Array arr)
{
	printf_s("\n");
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m[i];j++)
		{
			printf_s("%5d ",arr.a[i][j]);
		}
		printf_s("\n");
	}
	printf_s("\n");
}

void del(Ragged_Array arr, int l,int k)
{
	for (int i = k;i < arr.m[l] - 1;i++)
		arr.a[l][i] = arr.a[l][i+1];
	arr.a[l] = (int*)realloc(arr.a[l], (arr.m[l] - 1) * sizeof(int));
	arr.m[l]--;
}

void func_arr(Ragged_Array arr)
{
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m[i];j++)
		{
			for (int c = 0;c < arr.n;c++)
			{
				for (int d = 0;d < arr.m[c];d++)
				{
					if (arr.a[c][d] == arr.a[i][j] && !(c==i && d==j))
					{
						del(arr, c, d);
						d --;
					}
				}
			}
		}
	}		
}

void third()
{
	Ragged_Array arr;
	int col;
	do{
		printf_s("Введите кол-во строк:\n");
		scanf_s("%d",&arr.n);
	}while (arr.n <= 0);
	do {
		printf_s("Введите кол-во столбцов:\n");
		scanf_s("%d", &col);
	} while (col <= 0);

	arr.m = (int*)malloc(arr.n * sizeof(int));
	for (int i = 0;i < arr.n;i++)
		arr.m[i] = col;
	
	arr.a = (int**)malloc(arr.n*sizeof(int*));
	for (int i = 0;i < arr.n;i++)
		arr.a[i] = (int*)malloc(arr.m[i] * sizeof(int));

	input(arr);
	output(arr);
	func_arr(arr);
	
	for (int i = 0;i < arr.n;i++)
	{
		if (arr.a[i] == NULL)
		{
			for (int j = i;j < arr.n - 1;j++)
			{
				arr.a[j] = arr.a[j + 1];
				arr.m[j] = arr.m[j + 1];
			}
			arr.m = (int*)realloc(arr.m, (arr.n - 1) * sizeof(int));
			arr.a = (int**)realloc(arr.a, (arr.n - 1) * sizeof(int*));
			i--;
			arr.n--;
		}
	}

	output(arr);
	
	for (int i = 0;i < arr.n;i++)
		free(arr.a[i]);
	free(arr.m);
	free(arr.a);
}