//
//  main.c
//  Homework_04
//
//  Created by 苏可铮  on 2021/10/20.
//
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
struct data
{
    char name[10];
    int num;
    int score;
};
int main()
{
    struct data a[10];
    struct data temp;
    int line=0;
    int i=0;
    char c;
    FILE *fp;
    
    while((fp= fopen("/Users/larrysu/Desktop/code/C/Homework_04/Homework_04/Student.csv", "r+")) != NULL)
    {
    
        while(1)
        {
            a[line].name[i]=fgetc(fp);
            if(a[line].name[i]==',')
            {
                a[line].name[i]='\0';
                i=0;
                break;
            }
            i++;
        }
        fscanf(fp,"%d",&a[line].num);
        c=fgetc(fp);
        fscanf(fp,"%d",&a[line].score);
        c=fgetc(fp);
        c=fgetc(fp);
        line++;
        if(line==10)
            break;
    }
    
    for(i = 0; i < line; i ++)
    {
    printf("%s %d %d\n", a[i].name, a[i].num, a[i].score);
    }
    
    for(int i=0;i<9;i++)
    {
        for(int j=i+1;j<10;j++)
        {
            if(a[j].num<a[i].num)
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
    printf("成绩降幂排序为：\n");
    for(i = 0; i < line; i ++)
    {
        printf("%s %d %d\n", a[i].name, a[i].num, a[i].score);
    }
    struct data *p=a;
    for(;p<a+10;p++)
    {
        fputs(p->name, fp);
        fputc(',', fp);
        fprintf(fp,"%d",p->num);
        fputc(',', fp);
        fprintf(fp, "%d",p->score);
        fputc('\n', fp);
    }
    
    fclose(fp);
    return 0;
}
