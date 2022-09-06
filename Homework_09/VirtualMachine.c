#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node, *LinkList;

LinkList vir;
int r[4];

LinkList push(LinkList p, int n);
int pop(LinkList p);
LinkList load(LinkList p, int n);
void store(LinkList p, int n);
LinkList add(LinkList p);
LinkList sub(LinkList p);
LinkList mul(LinkList p);
LinkList _div(LinkList p);
void print(LinkList p);
void stop(LinkList p);

int main(int argc, char *argv[]) {
    vir = (LinkList)malloc(sizeof(LinkList));
    vir->next = NULL;
    FILE *fp;
    if (argc == 2) {
        if (feof(fp = fopen(argv[1], "r"))) {
            printf("Fail to open file.\n");
            return 0;
        }
        char str[32];
        while (fgets(str, 32, fp)) {
            int i, len = strlen(str);
            char str1[32] = "", str2[32] = "";
            for (i = 0; i < len; i++) {
                if (str[i] == ' ' || str[i] == '\n')
                    break;
                str1[i] = str[i];
            }
            while (str[i] == ' ' || str[i] == '\n')
                i++;
            int k = 0;
            for (int j = i; j < len; j++) {
                str2[k++] = str[j];
            }
            if (!strcmp(str1, "push")) {
                int a = atoi(str2);
                vir = push(vir, a);
            } else if (!strcmp(str1, "pop")) {
                int x = pop(vir);
            } else if (!strcmp(str1, "load")) {
                int a = atoi(str2);
                vir = load(vir, a);
            } else if (!strcmp(str1, "store")) {
                int a = atoi(str2);
                store(vir, a);
            } else if (!strcmp(str1, "add")) {
                vir = add(vir);
            } else if (!strcmp(str1, "sub")) {
                vir = sub(vir);
            } else if (!strcmp(str1, "mul")) {
                vir = mul(vir);
            } else if (!strcmp(str1, "div")) {
                vir = _div(vir);
            } else if (!strcmp(str1, "print")) {
                print(vir);
            } else if (!strcmp(str1, "stop")) {
                stop(vir);
            } else printf("ERROR\n");
        }
    } else {
        while (1) {
            printf("$ ");
            char str[32];
            fgets(str, 32, stdin);
            int i, len = strlen(str);
            char str1[32] = "", str2[32] = "";
            for (i = 0; i < len; i++) {
                if (str[i] == ' ' || str[i] == '\n')
                    break;
                str1[i] = str[i];
            }
            while (str[i] == ' ' || str[i] == '\n')
                i++;
            int k = 0;
            for (int j = i; j < len; j++) {
                str2[k++] = str[j];
            }
            if (!strcmp(str1, "push")) {
                int a = atoi(str2);
                printf("将%d压入栈\n", a);
                vir = push(vir, a);
            } else if (!strcmp(str1, "pop")) {
                printf("将栈顶数据移除\n");
                int x = pop(vir);
            } else if (!strcmp(str1, "load")) {
                int a = atoi(str2);
                printf("将寄存器%d的值压入栈\n", a);
                vir = load(vir, a);
            } else if (!strcmp(str1, "store")) {
                int a = atoi(str2);
                printf("将栈顶数据移除，并保存在寄存器%d中\n", a);
                store(vir, a);
            } else if (!strcmp(str1, "add")) {
                printf("将栈顶端的两个整数移出栈，并做加法，再将结果压入栈\n");
                vir = add(vir);
            } else if (!strcmp(str1, "sub")) {
                printf("将栈顶端的两个整数移出栈，并做减法，再将结果压入栈（ps:前一个入栈的数减去后一个入栈的数）\n");
                vir = sub(vir);
            } else if (!strcmp(str1, "mul")) {
                printf("将栈顶端的两个整数移出栈，并做乘法，再将结果压入栈\n");
                vir = mul(vir);
            } else if (!strcmp(str1, "div")) {
                printf("将栈顶端的两个整数移出栈，并做除法，再将结果压入栈（ps:前一个入栈的数除以后一个入栈的数）\n");
                vir = _div(vir);
            } else if (!strcmp(str1, "print")) {
                printf("打印栈顶数据\n");
                print(vir);
            } else if (!strcmp(str1, "stop")) {
                printf("退出虚拟机\n");
                stop(vir);
            } else printf("ERROR\n");
        }

    }
    return 0;
}

LinkList push(LinkList p, int n) {
    LinkList c = (LinkList)malloc(sizeof(LinkList));
    c->data = n;
    c->next = p->next;
    p->next = c;
    return p;
}

int pop(LinkList p) {
    if (p->next == NULL) {
        printf("ERROR\n");
        return 0;
    }
    LinkList c = p->next;
    int a = c->data;
    p->next = c->next;
    free(c);
    return a;
}

LinkList load(LinkList p, int n) {
    if (n > 3)
        printf("ERROR\n");
    else
        push(p, r[n]);
    return p;
}

void store(LinkList p, int n) {
    if (n > 3)
        printf("ERROR\n");
    else
        r[n] = pop(p);
}

LinkList add(LinkList p) {
    int a = pop(p), b = pop(p);
    p = push(p, a + b);
    return p;
}

LinkList sub(LinkList p) {
    int a = pop(p), b = pop(p);
    p = push(p, b - a);
    return p;
}

LinkList mul(LinkList p) {
    int a = pop(p), b = pop(p);
    p = push(p, a * b);
    return p;
}

LinkList _div(LinkList p) {
    int a = pop(p), b = pop(p);
    p = push(p, b / a);
    return p;
}

void print(LinkList p) {
    if (p->next == NULL) {
        printf("ERROR\n");
        return;
    }
    printf("%d\n", (p->next)->data);
}

void stop(LinkList p) {
    if (p->next != NULL) {
        while (p->next != NULL) {
            LinkList c = p->next;
            p->next = c->next;
            free(c);
        }
        free(p);
    }
    exit(0);
}
