#define _CRT_SECURE_NO_WARNINGS
//#include <stddef.h>
//#include <stdint.h>
//#include <conio.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "csv.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* entergoodid()
{
    //this func print to ented id and check if its could be a good id
    int tmp = 1;
    char id[50];

    printf("enter your ID : \n");
    while (tmp == 1)
    {
        scanf("%s", id);
        tmp = 0;
        if (strlen(id) != 9)
        {
            printf("enter 9 dig ID : \n");
            tmp++;
            continue;
        }
        for (int i = 0; i < strlen(id); i++)
        {
            if ((id[i] < '0' || id[i] > '9'))
            {
                tmp++;
                printf("enter 9 dig ID : \n");
                break;
            }
        }

    }
    /*char* retstr;
    strcpy(retstr, id);*/
    return id;
}
const char* getfield(char* line, int num)
{
    //this func get the csv file and the number of colm and return the data in this colmn
    const char* tok;
    for (tok = strtok(line, ",");
        tok && *tok;
        tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
void signupcandid()
{

    char string[50];
    char password[30];
    /*printf("enter your ID : \n");
    scanf("%s", string);
    while (strlen(string) != 9)
    {
        printf("enter 9 dig ID : \n");
        scanf("%s", string);
    }*/
    strcpy(string, entergoodid());
    int b = checkifidexist(string);
    if (b != 0)
    {
        printf("exist");
        return 0;
    }
    printf("valid id\n");
    printf("enter 8 digit password with 1 letter and 1 number : \n");
    scanf("%s", password);
    b = checkpassword(password);
    while ((strlen(password) < 8)||b==0)
    {
        printf("enter 8 digit password : \n");
        scanf("%s", password);
        b = checkpassword(password);
    }

}
int checkifidexist(char string[50])
{
    //this func get the id number and check if it exist and return the row his shown
    int row = 0;
    FILE* stream = fopen("candidate.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        row++;
        char* tmp = _strdup(line);
        if (strcmp(getfield(tmp, 1), string) == 0)
        {
            fclose(stream);
            return row;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    return 0;
}
int checkpassword(char string[30])
{
    //this func get password and check if its ok password return 1 if its ok 0 if not
    int tmp = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z'))
        {
            tmp++;
            break;
        }
    }
    for (int i = 0; i < strlen(string); i++)
    {
        if ((string[i] >= '0' && string[i] <= '9'))
        {
            tmp++;
            break;
        }
    }
    if (tmp == 2)
        return 1;
    else
        return 0;
}

int checkpasswordtoid(char id[10], char password[30])
{
    //this fun get the id and the password apper in the csv file and return 1 if its match 0 if not
    int row = checkifidexist(id);
    FILE* stream = fopen("candidate.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = _strdup(line);
        row--;
        if (row != 0)
            continue;
        if (strcmp(getfield(tmp, 2), password) == 0)
        {
            fclose(stream);
            return 1;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    fclose(stream);
    return 0;

}

void signincandid()
{
    char id[10];
    strcpy(id, entergoodid());
    int row = checkifidexist(id);
    if (row == 0)
    {
        printf("doesnt exist");
        return ;
    }
    char password[30];
    printf("enter password\n");
    scanf("%s", password);
    while (checkpasswordtoid(id, password) == 0)
    {
        printf("wrong!, enter password again\n");
        scanf("%s", password);
    }

}


int main()
{
    signincandid();
    //signupcandid();
    return 0;
    //for git example
    // sec change
    //FILE* stream = fopen("test1.csv", "r");

    //char line[1024];
    //while (fgets(line, 1024, stream))
    //{
    //    char* tmp = _strdup(line);
    //    printf("Field 3 would be %s\n", getfield(tmp, 2));
    //    // NOTE strtok clobbers tmp
    //    free(tmp);
    //}
}