#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>
#pragma warning (disable:4996)

void first()
{
   int sum=0;
   char str[256];
   printf("Ввод строки:\n");
   gets_s(str);
   for(int i=0;i<strlen(str);i++)
		{
            switch (str[i])
            {
                 case '1': sum ++; break;
                 case '2': sum += 2; break;
                 case '3': sum += 3; break;
                 case '4': sum += 4; break;
                 case '5': sum += 5; break;
                 case '6': sum += 6; break;
                 case '7': sum += 7; break;
                 case '8': sum += 8; break;
                 case '9': sum += 9; break;
            }
		}
    printf("%d\n",sum);
}

int pallindrom(char* str,int lenWord)
{
    int k = 1;
    for (int i = 0; i < lenWord/2; i++)
        if (str[i] != str[lenWord - i-1]) k = 0;
    return k;
}

void delWord(char* arr,int k, int lenWord)
{
    int len = strlen(arr);
    for (int i = k; i < len-lenWord; i++)
    {
        arr[i] = arr[i + lenWord];
    }
    arr[len - lenWord] = '\0';
}

void dop_obrabotka(char* arr)
{
    int l = 0, j = 0;
    
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] == ' ')
        {
            j = i+1;
            while (arr[j] == ' ')
            {
                l++;
                j++;
            }
            for (int k = i+1; k < strlen(arr)-l; k++)
                arr[k] = arr[k + l];
            arr[strlen(arr) - l ] ='\0' ;
            l = 0;
        }
    }
    
    if (arr[0] == ' ')
        for (int k = 0; k < strlen(arr) - l; k++)
            arr[k] = arr[k + 1];
    if (strlen(arr) && arr[strlen(arr) - 1] == ' ') arr[strlen(arr) - 1] = '\0';
}


void second()
{
    char str[256];
    char word[256];
    int k = 0;
    int lenWord=0;
    printf("Ввод строки:\n");
    gets_s(str);
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ' && str[i] != '\0')
        {
            lenWord = 0;
            k = 0;
            while (str[i] != ' ' && str[i]!='\0')
            {
                lenWord++;
                word[k] = str[i];
                i++;
                k++;
            }
            word[k] = '\0';
            if (pallindrom(word, lenWord)) {
                delWord(str, i - lenWord, lenWord);
                i -= lenWord;
            }
        }
    }
    dop_obrabotka(str);
    
    if (strlen(str) == 0) printf("От строки ничего не осталось!\n");
    else puts(str);
}


void del_space(char* arr)
{
    int l=0,k=0;
    while (arr[k] == ' ')
    {
        l++;
        k++;
    }
    
    for (int i = 0; i < strlen(arr) - l; i++)
        arr[i] = arr[i + l];
    arr[strlen(arr) - l] = '\0';
   
    l = 0;
    k = strlen(arr) - 1;    
    while (arr[k] == ' ')
    {
        l++;
        k--;
    }
    arr[strlen(arr) - l+1] = '\0';

}

void third()
{
    FILE* file1 = fopen("input.txt", "r"); 
    char str[256][256];
    char prop[256][256];
    int l = 0;  //Кол-во строк в файле
    int i1 = 0, j1 = 0;
    int zn[256];
    int prob[256];
    int k = 0;  //Кол-во предложений
    int wordsText=0;
    if (file1==NULL) printf("Файл не обнаружен!\n");
    else
    {
        while (!feof(file1))
        {
            fgets(str[l], 256, file1);
            l++;
        }
    }
    fclose(file1);
    
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < strlen(str[i]); j++)
        {
            if (str[i][j] != '\n') {
                prop[i1][j1] = str[i][j];
                j1++;
            }
            if (str[i][j] == '.' || str[i][j] == '?' || str[i][j] == '!')
            {
                prop[i1][j1] = '\0';
                i1++;
                j1 = 0;
                k++;
            }
        }
    }
    for (int i = 0; i < k; i++)
    {
        del_space(prop[i]);
        zn[i] = 0;
        prob[i] = 0;
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < strlen(prop[i]); j++)
        {
            if (prop[i][j] == ';' || prop[i][j] == ',' || prop[i][j] == '!' || prop[i][j] == '?' ||
                prop[i][j] == '.' || prop[i][j] == ':' || prop[i][j] == '"')
                zn[i]++;
            if (prop[i][j] == ' ') prob[i]++;
        }
    }
    printf("Предложения и их сложность:\n");
    for (int i = 0; i < k; i++)
    {
        wordsText += prob[i] + 1;
        puts(prop[i]);
        printf("%d", prob[i] + 1);
        printf(" %d\n", zn[i]);
    }
    
    printf("\nСложность всего текста\n");
    printf("Кол-во слов в тексте: %d\n", wordsText);
    printf("Кол-во предложений: %d\n\n", k);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    int n;
    do {
        do {
            printf("Введите номер задания или 0 для выхода:\n");
            scanf("%d", &n);
            if (n < 0 || n>3)
                printf("Другое число!\n");
        } while (n < 0 || n>3);
        getchar();
		
        switch (n)
        {
        case 1:first(); break;
        case 2:second(); break;
        case 3:third(); break;
        }
        
    } while (n != 0);
    
    return 0;
}
