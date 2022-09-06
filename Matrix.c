//
//  main.c
//  Homework_07
//
//  Created by 苏可铮  on 2021/11/9.
//
#include "Function.h"

int main(int argc, const char * argv[])
{
    int m,n;
    printf("请输入矩阵行数m：\n");
    scanf("%d",&m);
    printf("请输入矩阵列数n：\n");
    scanf("%d",&n);
    
    if (BOOL(m, n)) {
        printf("Uncorrect input!\n");
        return 0;
    }
    
    int Matrix_A[m][n];
    IniMatrix(m, n, Matrix_A);
    int Matrix_B[n][m];
    TraMatrix(m, n, Matrix_A, Matrix_B);
    
    printf("The Matrix_A is:\n");
    LogMatrix(m, n, Matrix_A);
    
    printf("The Matrix_B is:\n");
    LogMatrix(n, m, Matrix_B);

    return 0;
}
