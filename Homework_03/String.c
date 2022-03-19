#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXSIZE 100

void strupr(char *str)
{
    for ( ; *str != '\0'; str++)
        *str = toupper(*str);
}

void reverse(char *str)
{
    char* p = str + strlen(str) - 1;
    char temp;
    while(str < p)
    {
        temp = *p;
        *p-- = *str;
        *str++ = temp;
    }
}

char *Insert(char *a, char *b, int pos)
{
    long int len1,len2;
    int i;
    char buff[MAXSIZE];
    len1 = strlen(a);
    len2 = strlen(b);
    for (i = pos - 1; i < len1; i++)
    {
        buff[i] = a[i];
        a[i + len2] = buff[i];
    }
    for (i = pos - 1; i < pos - 1 + len2; i++)
    {
        a[i] = b[i - pos + 1];
    }
    return a;
}

int main()
{
    char str[MAXSIZE];
    char InsertStr[MAXSIZE];
    int pos;
    
    printf("Please enter a string:");
    scanf("%s",str);
    getchar();//使用getchar()吃掉回车
    printf("You entered:%s",str);
    
    printf("\nPlease enter the insert position:");
    scanf("%d",&pos);
    getchar();//使用getchar()吃掉回车
    printf("You entered:%d\n",pos);
    
    printf("Please enter the insert string:");
    scanf("%s",InsertStr);
    getchar();//使用getchar()吃掉回车
    strupr(InsertStr);
    reverse(InsertStr);
    Insert(str, InsertStr, pos);
    printf("The result is:%s\n",str);
    
    return 0;
}
