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
const char* getfield(char* line, int num)
{
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
    char string[9];
    printf("enter your ID : \n");
    scanf("%s", string);
    while (strlen(string) != 6)
    {
        printf("enter 6 dig ID : \n");
        scanf("%s", string);
    }
    int b = checkifidexist(string);
    if (b == 1)
        printf("exist");
    else
        printf("doest exist");


}
int checkifidexist(char string[9])
{
    FILE* stream = fopen("candidate.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = _strdup(line);
        if (strcmp(getfield(tmp, 1), string) == 0)
            return 1;
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    return 0;
}
int main()
{
    signupcandid();
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