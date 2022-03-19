//  main.c
//  Homework_02
//  Created by 苏可铮  on 2021/10/11.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXDAY 31
#define MAX_Size 30

int main() {
    
/*This is the first question*/
    int Date,year,m,d,w,y,c,i,j,k;
    int Day[MAXDAY];
    int month[] = {20210801,20211001,20210901};
    char Week_Day[20];
    FILE *fp;
    fp = fopen("/Users/larrysu/Desktop/code/C/Homework_02/calendar.txt", "w+");
    //If you want to run on your PC, don't forget to change the path.
    if (!fp) // 判断是否打开成功
        return -1;
        
        for (j = 0; j < 2; j++) {
            
            k = 8 + 2*j;
            
            for (i = 0; i < MAXDAY; i++) {
                
                Day[i] = i + 1;
                Date = month[j] + i;
                year=Date/10000;
                m=Date%10000/100;
                d=Date%100;
                y=year%100;
                c=year/100;
            
                if(m==1||m==2){
                    m+=12;
                    y--;
                }
                    
                w=(y+y/4+c/4-2*c+26*(m+1)/10+d-1)%7;//We use Zeller formula to calculate the weekday.
                    
                switch(w){
                //To use strcpy() we should add <string.h>
                case 0:strcpy(Week_Day,"星期日");break;
                
                case 1:strcpy(Week_Day,"星期一");break;

                case 2:strcpy(Week_Day,"星期二");break;

                case 3:strcpy(Week_Day,"星期三");break;

                case 4:strcpy(Week_Day,"星期四");break;

                case 5:strcpy(Week_Day,"星期五");break;

                case 6:strcpy(Week_Day,"星期六");break;
                }
                fprintf(fp,"2021年%02d月%02d日\t%s",k,Day[i],Week_Day);
                if (j != 1 || i != MAXDAY-1) {
                    fprintf(fp,"\n");
                }
            }
    }
    fclose(fp);
    
/*This is the second question*/
    
    fp = fopen("/Users/larrysu/Desktop/code/C/Homework_02/calendar.txt", "r"); // 打开文件
    char buf[1000];
    int lineCnt = 0;
    long int Size;
    if (!fp) // 判断是否打开成功
        return -1;
    while (fgets(buf, 1000, fp) != NULL){
        lineCnt++;
        printf("%s", buf);
        if (lineCnt%20 == 0) {
            printf("Press enter to continue.\n");
            getchar();
        }
    }
    
    fseek(fp, 0, SEEK_END);
    Size = ftell(fp);
    
    fclose(fp);
    printf("\nfile line count = %d\nThe number of bytes is %ld\n", lineCnt, Size);
    
/*This is the third question*/
    fp = fopen("/Users/larrysu/Desktop/code/C/Homework_02/calendar.txt", "r+"); // 追加方式打开文件且可读可写
    fseek(fp,0,SEEK_SET);
    int line;
    long int offset;
    char ch;
    line = 0;
    while(line!=31)
    {
        ch=fgetc(fp);
        if(ch=='\n')
        {
            line++;
        }
    }
    offset = ftell(fp);
    fseek(fp,offset,SEEK_SET);
    for (j = 2 ; j > 0 ; j--) {
        k = 11 - j;
        for (i = 0; i < (MAXDAY-j+1); i++) {
            Day[i] = i + 1;
            Date = month[j] + i;
            year=Date/10000;
            m=Date%10000/100;
            d=Date%100;
            y=year%100;
            c=year/100;

            if(m==1||m==2){
                m+=12;
                y--;
            }

            w=(y+y/4+c/4-2*c+26*(m+1)/10+d-1)%7;//We use Zeller formula to calculate the weekday.

            switch(w){
            //To use strcpy() we should add <string.h>
            case 0:strcpy(Week_Day,"星期日");break;

            case 1:strcpy(Week_Day,"星期一");break;

            case 2:strcpy(Week_Day,"星期二");break;

            case 3:strcpy(Week_Day,"星期三");break;

            case 4:strcpy(Week_Day,"星期四");break;

            case 5:strcpy(Week_Day,"星期五");break;

            case 6:strcpy(Week_Day,"星期六");break;
            }
            if (j != 2 || i != 0) {
                fprintf(fp,"\n");
            }//解决多余\n问题
            fprintf(fp,"2021年%02d月%02d日\t%s",k,Day[i],Week_Day);
        }
    }
    fclose(fp);
    
    return 0;
}
