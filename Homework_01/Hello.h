//
//  output.h
//  C_Hello world
//
//  Created by 苏可铮  on 2021/9/20.
//

#ifndef output_h
#define output_h

#include <stdio.h>

#endif /* output_h */

void output(void);

void output()
{
    int i;
    
    for (i = 1; i <= 10; i++)
    {
        printf("%4s%-2d %10s\n","line",i,"Hello,world");
    }
}
