#include "Function.h"

int main(int argc, char *argv[])
{
    Config *cnf = cnf_read_config("/Users/larrysu/Desktop/code/C/Homework_08/cnf.ini",'=');
    if (NULL == cnf) {
        return -1; /* 创建对象失败 */
    }
    int choice;
    while ((choice=init()) && choice!=5)
    {
        switch (choice)
        {
            case 1:
            {
                char section[MAX_VALUE];
                printf("Please enter the section you want to print:");
                fgets(section, MAX_VALUE, stdin);
                section[strlen(section) - 1] = '\0';
                print_config_section(cnf, section); // 打印cnf对象
            }
                printf("\nPlease press Enter to return the menu.");
                getchar();
                break;
                
            case 2:
            {
                char section[MAX_VALUE];
                printf("Please enter the section you want to print:");
                fgets(section, MAX_VALUE, stdin);
                section[strlen(section) - 1] = '\0';
                char option[MAX_VALUE];
                printf("Please enter the option you want to print:");
                fgets(option, MAX_VALUE, stdin);
                option[strlen(option) - 1] = '\0';
                print_config_option(cnf,section,option);
            }
                printf("\nPlease press Enter to return the menu.");
                getchar();
                break;
                
            case 3:
            {
                char section[MAX_VALUE];
                char key[MAX_VALUE];
                char value[MAX_VALUE];
                printf("Please enter the section you want to add:");
                fgets(section, MAX_VALUE, stdin);
                section[strlen(section) - 1] = '\0';
                printf("Please enter the key you want to add:");
                fgets(key, MAX_VALUE, stdin);
                key[strlen(key) - 1] = '\0';
                printf("Please enter the value you want to add:");
                fgets(value, MAX_VALUE, stdin);
                value[strlen(value) - 1] = '\0';
                cnf_add_option(cnf, section, key, value);
                cnf_write_file(cnf, "/Users/larrysu/Desktop/code/C/Homework_08/cnf.ini");
            }
                printf("\nPlease press Enter to return the menu.");
                getchar();
                break;
            
            case 4:
            {
                char section[MAX_VALUE];
                char key[MAX_VALUE];
                char value[MAX_VALUE];
                printf("Please enter the section you want to add:");
                fgets(section, MAX_VALUE, stdin);
                section[strlen(section) - 1] = '\0';
                printf("Please enter the key you want to add:");
                fgets(key, MAX_VALUE, stdin);
                key[strlen(key) - 1] = '\0';
                printf("Please enter the value you want to add:");
                fgets(value, MAX_VALUE, stdin);
                value[strlen(value) - 1] = '\0';
                cnf_add_option(cnf, section, key, value);
                cnf_write_file(cnf, "/Users/larrysu/Desktop/code/C/Homework_08/cnf.ini");;
            }
                printf("\nPlease press Enter to return the menu.");
                getchar();
                break;
        }
    }
    printf("The program is ended, thanks for your using!\n");
    destroy_config(&cnf);//释放动态分配的config内存
    return 0;
}
