#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
        int id;
        void *node;
        struct node *next;
} NODE;

typedef struct linklist{
        NODE *header;
        int (*get_id)(void *);
        void (*display)(void *);
        void (*destructor)(void *);
} linklist;

linklist* linklist_init(int (*get_id)(void *), void (*display)(void *), void (*destructor)(void *)){
    linklist *l;
    l = (linklist *)malloc(sizeof(linklist));
    l->header = NULL;
    l->get_id = get_id;
    l->display = display;
    l->destructor = destructor;
    return l;
}

void linklist_des(linklist *list){
    struct node *p = list->header;
    while(p!=NULL){
        struct node *pNext = p->next;
        list->destructor(p->node);
        free(p);
        p = pNext;
    }
    free(list);
}

void linklist_insert(linklist *l,void *data){
    int id = l->get_id(data);
    struct node *newNode = (node *)malloc(sizeof(node));
    newNode->id = id;
    newNode->node = data;
    newNode->next = NULL;
    struct node **p = &l->header;
    while((*p)!=NULL){
        p = &(*p)->next;
    }
    newNode->next = *p;
    *p = newNode;
}
void linklist_insert_id(linklist *l,void *data,int id_0){
    int id = l->get_id(data);
    struct node *newNode = (node *)malloc(sizeof(node));
    newNode->id = id;
    newNode->node = data;
    newNode->next = NULL;
    struct node **p = &l->header;
    while((*p)!=NULL && (*p)->id==id_0){
        p = &(*p)->next;
    }
    newNode->next = *p;
    *p = newNode;
}

void linklist_delete(linklist *l, int id){
    if(l->header==NULL) return;
    struct node **p = &l->header;
    while((*p)!=NULL && (*p)->id!=id){
        p = &(*p)->next;
    }
    struct node *del = *p;
    if(del==NULL) return;
    free(del);
    *p = (*p)->next;
}

void* linklist_search(linklist *l, int id){
    struct node *p = l->header;
    while(p!=NULL){
        if(p->id==id){
            return p->node;
            break;
        }
        p = p->next;
    }
    return NULL;
}

void linklist_output(linklist *l){
    struct node *p = l->header;
    while(p!=NULL){
        l->display(p->node);
        p = p->next;
    }
}

typedef struct{
    int no;
    char *name;
    char *sex;
    int age;
} STUDENT;

int get_id_stu(void *p){
    STUDENT *stu = (STUDENT *)p;
    return stu->no;
}
void display_stu(void *p)
{
    STUDENT *h = (STUDENT *) p;
    printf("%d  %s  %s  %d\n", h->no, h->name, h->sex, h->age);
}
void destructor_stu(void *p){
    STUDENT *stu = (STUDENT *)p;
    free(stu->name);
    free(stu);
}


int main(){
    linklist *link_stu = linklist_init(&get_id_stu,&display_stu,&destructor_stu);
    
/*1.插入学生信息*/
    STUDENT *stu_0 = (STUDENT *)malloc(sizeof(STUDENT));
    stu_0->no = 20200121;
    stu_0->name = (char *)malloc(20);
    memcpy(stu_0->name,"Tomsen",20);
    stu_0->sex = "Male";
    stu_0->age = 22;
    linklist_insert(link_stu,stu_0);

    STUDENT *stu_1 = (STUDENT *)malloc(sizeof(STUDENT));
    stu_1->no = 20200182;
    stu_1->name = (char *)malloc(20);
    memcpy(stu_1->name,"Jerry",20);
    stu_1->sex = "Male";
    stu_1->age = 21;
    linklist_insert(link_stu,stu_1);

    STUDENT *stu_2 = (STUDENT *)malloc(sizeof(STUDENT));
    stu_2->no = 20200112;
    stu_2->name = (char *)malloc(20);
    memcpy(stu_2->name,"Lily",20);
    stu_2->sex = "Female";
    stu_2->age = 20;
    linklist_insert(link_stu,stu_2);
    
/*2.查找学生信息*/
    display_stu(linklist_search(link_stu,20200182));
    printf("%s","\n");

/*3.删除学生信息*/
    linklist_delete(link_stu, 20200182);
    
/*4.指定位置插入学生信息*/
    STUDENT *stu_3 = (STUDENT *)malloc(sizeof(STUDENT));
    stu_3->no = 20200223;
    stu_3->name = (char *)malloc(20);
    memcpy(stu_3->name,"Wellean",20);
    stu_3->sex = "Male";
    stu_3->age = 20;
    linklist_insert_id(link_stu,stu_3,20200121);

/*5.输出学生信息*/
    linklist_output(link_stu);
    return 0;
}
