#include "Prog1.h"
#include <stdio.h>
#include <malloc.h>

void input_arr(Array arr)
{
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m;j++)
		{
			printf_s("Введите элемент строки %d и столбца %d: ", i+1, j+1);
			scanf_s("%d", arr.a + i * arr.m + j);
		}
	}
	printf("\n");
}

void output_arr(Array arr)
{
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m;j++)
		{
			printf_s("%5d", *(arr.a + i * arr.m + j));
		}
		printf_s("\n");
	}
}

double sred_arifm(Array arr,int &k)
{
	int max=*arr.a,sum=0;
	k = 0;
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m;j++)
		{
			if (*(arr.a + i * arr.m + j) > max)
			{
				max = *(arr.a + i * arr.m + j);
				k = j;
			}
		}
	}

	for (int i = 0;i < arr.n;i++)
		sum += *(arr.a + i * arr.m + k);

return double(sum)/arr.n;
}

void first()
{
	int k;
	double arifm;
	Array arr;
	do {
		printf_s("Введите кол-во строк:\n");
		scanf_s("%d",&arr.n);
	} while (arr.n <= 0);
	do {
		printf_s("Введите кол-во столбцов:\n");
		scanf_s("%d", &arr.m);
	} while (arr.m <= 0);

	arr.a = (int*)malloc(arr.n*arr.m*sizeof(int));
	
	input_arr(arr);
	output_arr(arr);
	
	arifm = sred_arifm(arr,k);
	printf("Среднее арифметическое столбца %d: %5.3lf\n",k+1,arifm);

	free(arr.a);
}


void input_arr1(Array1 arr)
{
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m;j++)
		{
			printf_s("Введите элемент строки %d и столбца %d: ", i + 1, j + 1);
			scanf_s("%d", &arr.a[i][j]);
		}
	}
	printf_s("\n");
}

void output_arr1(Array1 arr)
{
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m;j++)
		{
			printf_s("%5d", arr.a[i][j]);
		}
		printf_s("\n");
	}
}

double sred_arifm1(Array1 arr, int& k)
{
	int max = arr.a[0][0], sum = 0;
	k = 0;
	for (int i = 0;i < arr.n;i++)
	{
		for (int j = 0;j < arr.m;j++)
		{
			if (arr.a[i][j] > max)
			{
				max = arr.a[i][j];
				k = j;
			}
		}
	}

	for (int i = 0;i < arr.n;i++)
		sum += arr.a[i][k];
return double(sum) / arr.n;
}

void second()
{
	int k;
	double arifm;
	Array1 arr;
	do {
		printf_s("Введите кол-во строк:\n");
		scanf_s("%d", &arr.n);
	} while (arr.n <= 0);
	do {
		printf_s("Введите кол-во столбцов:\n");
		scanf_s("%d", &arr.m);
	} while (arr.m <= 0);

	arr.a = (int**)malloc(arr.n*sizeof(int*));
	for (int i = 0;i < arr.n;i++)
		arr.a[i] = (int*)malloc(arr.m*sizeof(int));
	input_arr1(arr);
	output_arr1(arr);
	arifm = sred_arifm1(arr,k);
	
	printf_s("Среднее арифметическое столбца %d: %5.3lf\n", k + 1, arifm);

	for (int i = 0;i < arr.n;i++)
		free(arr.a[i]);
	free(arr.a);
}