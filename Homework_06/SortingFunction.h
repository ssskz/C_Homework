//
//  Function.h
//  Homework_06
//
//  Created by 苏可铮  on 2021/11/9.
//
#ifndef Function_h
#define Function_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif /* Function_h */

#define MAXSIZE 1000
#define Len(ARRAY) sizeof(ARRAY)/sizeof(ARRAY[0])

typedef int(*PFun)(void*, void*);//PFun函数指针数据类型
int Index;
int lower(int c)
{
    return ((c>='A')&&(c<='Z'))?(c+'a'-'A'):(c);
}

/*------------------比较传入的参数大小------------------------*/
int Cmp_int(void* vp1, void* vp2)
{
    return *(int*)vp1 - *(int*)vp2;
}

int Cmp_double(void* vp1, void* vp2)
{
#define EPS 0.0000001
    double tmp = *(double*)vp1 - *(double*)vp2;
    if (tmp >= EPS)
    {
        return 1;
    }
    else if (tmp <= -EPS)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int Cmp_str(void* vp1, void* vp2)
{
    char Buff1[MAXSIZE],Buff2[MAXSIZE];
    memcpy(Buff1, *(char**)vp1, MAXSIZE);
    memcpy(Buff2, *(char**)vp2, MAXSIZE);
    return lower(Buff1[strlen(Buff1)-1]) - lower(Buff2[strlen(Buff2)-1]);
}

/*--------------------寻找最大值函数------------------------*/
//arr:数组首地址;len:数组长度;elemsize:每个元素的字节数,pcmp对应类型的比较函数的指针
 void Max_Val(void* arr, int len, int elemsize, PFun pcmp)
 {
     void* base;
     void* base_next;
     Index = 0;
     base = (char*)arr;
     for (int i = 0; i < len - 1; i++)
     {
         base_next = (char*)arr + (i + 1) * elemsize;
         if (pcmp(base, base_next) < 0)
         {
             memcpy(base, base_next, elemsize);
             Index = i+1;
         }
     }
     printf("The position of the biggest element is: %d\n",Index);
}

