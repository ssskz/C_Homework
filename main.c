//
//  main.c
//  Homework_06
//
//  Created by 苏可铮  on 2021/11/8.
//
#include "Function.h"

int main()
{
    /*-----------整型数组排序测试------------*/
    int arr[] = {12,43,1212,34,89,564,783,2432};
    Max_Val(arr, Len(arr), sizeof(int), Cmp_int);
    printf("The biggest element is: %d\n",arr[Index]);
    
    /*-----------浮点数(float、double)型数组排序测试------------*/
    double drr[] = { 12.323,67.86,23.41,151.6 };
    Max_Val(drr, Len(drr), sizeof(double), Cmp_double);
    printf("The biggest element is: %g\n",drr[Index]);
    
    /*--------字符串型数组排序测试---------*/
    const char* srr[] = { "China","UK","americA","JapaN" };//按照尾字符ASCII码比较
    Max_Val(srr, Len(srr), sizeof(char*), Cmp_str);
    printf("The biggest element is: %s\n",srr[Index]);
    return 0;
}
