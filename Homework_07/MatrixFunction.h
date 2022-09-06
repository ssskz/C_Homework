//
//  Function.h
//  Homework_07
//
//  Created by 苏可铮  on 2021/11/9.
//

#ifndef Function_h
#define Function_h
#include <stdio.h>

#endif /* Function_h */
#define  BOOL(x,y) ( ((x) == (y)) ? 1 : 0 )

void IniMatrix(int x,int y,int matrix[x][y])
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            matrix[i][j] = (i + 1)*(j + 1);
        }
    }
}

void TraMatrix(int x,int y,int matrix[x][y],int MATRIX[y][x])
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            MATRIX[i][j] = matrix[j][i];
        }
    }
}

void LogMatrix(int x,int y,int matrix[x][y])
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
}
