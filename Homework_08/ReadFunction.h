#ifndef Function_h
#define Function_h

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#endif /* Function_h */

#define  MAX_VALUE  1024 /* 读取缓存行最大长度 */
#define  PRINT_ERRMSG(STR) fprintf(stderr,"line:%d,msg:%s,eMsg:%s\n", __LINE__, STR, strerror(errno))

#define TRIM_LIFT  1 /* 去除左边空白字符 */
#define TRIM_RIGHT 2 /* 去除右边空白字符 */
#define TRIM_SPACE 3 /* 去除两边空白字符 */

typedef struct _option {
    char    *key;           /* 对应键 */
    char    *value;         /* 对应值 */
    struct  _option *next;  /* 链表连接标识 */
}Option;

typedef struct _data {
    char    *section;    /* 保存section值 */
    Option  *option;     /* option链表头  */
    struct  _data *next; /* 链表连接标识  */
}Data;

typedef struct {
    char    separator;  /* 表示分隔符*/
    Data    *data;
}Config;


/*判断section是否存在，不存在返回空指针，存在则返回包含那个section的Data指针*/
Data *cnf_has_section(Config *cnf, const char *section)
{
    Data *p = cnf->data; /* 让变量p循环遍历data,找到对应section */
    while (NULL != p && 0 != strcmp(p->section, section)) {
        p = p->next;
    }
    if (NULL == p) { /* 没找到则不存在 */
        return NULL;
    }
    return p;
}
/*输出指定节的键-值对应的结果*/
void print_config_section(Config *cnf, const char *section)
{
    Data *p = cnf_has_section(cnf, section);
    if (p != NULL)
    {
        printf("[%s]\n",p->section);
        Option *q = p->option;
        while (q != NULL)
        {
            printf("%s%c%s\n", q->key, cnf->separator, q->value);
            q = q->next;
        }
    }
    if (p == NULL) {
        printf("The section you entered is invalid!\n");
    }
}


/*判断指定option是否存在，不存在返回空指针，存在则返回包含那个section下key的Option指针*/
Option *cnf_has_option(Config *cnf, const char *section, const char *key)
{
    Data *p = cnf_has_section(cnf, section);
    if (NULL == p) { /* 没找到则不存在 */
        return NULL;
    }

    Option *q = p->option;
    while (NULL != q && 0 != strcmp(q->key, key)) {
        q = q->next; /* 遍历option,检查key是否已经存在 */
    }
    if (NULL == q) { /* 没找到则不存在 */
        return NULL;
    }
    return q;
}
/*输出对指定节指定键的对应值*/
void print_config_option(Config *cnf, const char *section, const char *key)
{
    Data *p = cnf_has_section(cnf, section);
    if (p != NULL) {
        Option *q = cnf_has_option(cnf, section, key);
        if (q != NULL) {
            printf("%s%c%s\n", q->key, cnf->separator, q->value);
        }
        if (q == NULL) {
            printf("The option you entered is invalid!\n");
        }
    }
    if (p == NULL) {
        printf("The section you entered is invalid!\n");
    }
}


/*判断字符串是否为空，为空返回true,不为空返回false*/
bool str_empty(const char *string)
{
    return string == NULL;
}
/*将Config对象写入指定文件中*/
void cnf_write_file(Config *cnf, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        PRINT_ERRMSG("fopen");
        exit(errno); /* 读文件错误直接按照错误码退出 */
    }
    Option *q;
    Data   *p = cnf->data;
    while (p != NULL) {
        fprintf(fp, "[%s]\n", p->section);
        q = p->option;
        while (q != NULL) {
            fprintf(fp, "%s %c %s\n", q->key, cnf->separator, q->value);
            q = q->next;
        }
        p = p->next;
    }
    fclose(fp);
}
/*
 向链表添加section,key,value
 如果添加时不存在section则新增一个，如果section已存在则不会重复创建
 如果对应section的key不存在则新增一个，如果对应section的key已存在则只会覆盖key的值
*/
void cnf_add_option(Config *cnf, const char *section, const char *key, const char *value)
{
    if (cnf == NULL || str_empty(section) || str_empty(key) || str_empty(value)) {
        printf("The configure you entered is wrong!\n"); /* 提升用户参数输入不正确 */
    }
    
    Data *p = cnf_has_section(cnf, section);
    if (p == NULL) { /* 说明没有找到section,需要加一个 */
        Data *ps = (Data*)malloc(sizeof(Data));
        /* 动态申请section内存 */
        ps->section = (char*)malloc(sizeof(char) * (strlen(section)+1));
        strcpy(ps->section, section);
        ps->option = NULL;    /* 初始化option */
        ps->next = cnf->data;
        cnf->data = p = ps;
    }

    Option *q = cnf_has_option(cnf, section, key);
    if (q == NULL)
    { /* 不存在option,则新建一个 */
        q = (Option*)malloc(sizeof(Option));/* 动态申请key内存 */
        q->key = (char*)malloc(sizeof(char) * (strlen(key)+1));
        strcpy(q->key, key);
        q->next = p->option;
        p->option = q;
        /* 动态申请value内存 */
        q->value = (char*)malloc(sizeof(char) * (strlen(value)+1));
    }
    else if (strlen(q->value) < strlen(value))
    {
        /* 当新值长度小于旧值,重新申请内存 */
        q->value = (char*)realloc(q->value, sizeof(char) * (strlen(value)+1));
    }
    strcpy(q->value, value);
}

/*销毁Config对象，释放申请的内存*/
void destroy_config(Config **cnf)
{
    if (*cnf == NULL)
      return;
    if ((*cnf)->data !=  NULL)
    {
        Data *pt, *p = (*cnf)->data;
        Option *qt, *q;
        while (p != NULL)
        {
            q = p->option;
            while (q != NULL)
            {
                free(q->key);
                free(q->value); /* 释放内存 */
                qt = q;
                q = q->next;
                free(qt);
            }
            free(p->section); /* 释放内存 */
            pt = p;
            p = p->next;
            free(pt);
        }
    }
    free(*cnf);
    *cnf = NULL;
}

/*交互式封装界面*/
int init(void)
{
    int choice, confirm;
    printf("|______________________________|\t\n"
        "|\t1:输出指定节的键值对应的结果    |\t\n"
        "|\t2:输出对指定节指定键的对应值    |\t\n"
        "|\t3:增加新节以及其下的新键与值    |\t\n"
        "|\t4:修改现有的节下的指定键的值    |\t\n"
        "|\t5:退出程序并且释放申请的内存    |\t\n"
        "|______________________________|\t\n\n");
    printf("请输入你想进行的操作：");
    scanf(" %d", &choice);
    while ((confirm = getchar()) != '\n')//用户再次输入空格键才表示其真正确认
        continue;
    while (choice != 5 && (choice < 1 || choice > 4))//检测合法输入
    {
        printf("您的输入: '%d' 有误!请重新输入：", choice);
        scanf(" %d", &choice);
    }
    return choice;
}

/*按照参数去除字符串左右空白*/
char *trim_string(char *string,int mode)
{
    char *left = string;
    if ((mode & TRIM_LIFT) != 0)
    { // 去除左边空白字符
        for (;*left != '\0'; left++)
        {
            
            if (0 == isspace(*left)) {
                break;
            }
        }
    }
    if ((mode & TRIM_RIGHT) != 0)
    { // 去除右边空白字符
        char *right = string - 1 + strlen(string);
        for (;right >= left; right--)
        {
            if (0 == isspace(*right))
            {
                *(right+1) = '\0';
                break;
            }
        }
    }
    return left;
}

/*读取ini文件：参数有文件路径,分隔符；返回Config结构体*/
Config *cnf_read_config(const char *filename, char separator)
{
    Config *cnf = (Config*)malloc(sizeof(Config));
    if (cnf == NULL) {
        exit(-1); /* 申请内存错误 */
    }
    cnf->separator = separator; /* 用来分隔Section 和 数据 */
    cnf->data = NULL; /* 初始数据为空 */
    if (str_empty(filename)) {
        printf("Invalid filename input!\n");
    }
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        PRINT_ERRMSG("fopen");
        exit(errno); /* 读文件错误直接按照错误码退出 */
    }
    
    char *s, *e, *pLine, sLine[MAX_VALUE];    /* 保存一行数据到字符串 */
    char section[MAX_VALUE], key[MAX_VALUE], value[MAX_VALUE]; /* 缓存section,key,value */
    while (fgets(sLine, MAX_VALUE, fp) != NULL)
    {
        pLine = trim_string(sLine, TRIM_SPACE); /* 去掉一行两边的空白字符 */
        if (*pLine == '\0') {
            continue; /* 空行跳过 */
        }

        s = strchr(pLine, '[');
        if (s != NULL) {
            e = strchr(++s, ']');
            if (e != NULL) {
                *e = '\0'; /* 找到section */
                strcpy(section, s);
            }
        }
        else {
            s = strchr(pLine, separator);
            if (s != NULL && *section != '\0')
            { /* 找到包含separator的行,且前面行已经找到section */
                *s = '\0'; /* 将分隔符前后分成2个字符串 */
                strcpy(key, trim_string(pLine, TRIM_RIGHT)); /* 赋值key */
                strcpy(value, trim_string(s+1, TRIM_LIFT));  /* 赋值value */
                cnf_add_option(cnf, section, key, value);    /* 添加section,key,value */
            }
        }
    }
    fclose(fp);
    return cnf;
}
