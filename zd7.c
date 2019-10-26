#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 1024

typedef struct _stack_element
{
    float broj;
    struct _stack_element *next;
} element;

int pushStack(element *HEAD, float broj);
float popStack(element *HEAD);
int izracunajPostfix(element *HEAD, char *filename);
int izracunajOperaciju(element * HEAD, char operator);

int main()
{
    element *HEAD = (element *)malloc(sizeof(element));

    if (!HEAD)
        return -1;

    HEAD->next = NULL;
    char filename[STRMAX];

    printf("Unesi ime datoteke s postfix izrazom: ");
    scanf("%s", filename);

    izracunajPostfix(HEAD, filename);

    if (!HEAD->next)
        return -1;

    printf("%.3f\n", HEAD->next->broj);

    return 0;
}

int pushStack(element *HEAD, float broj)
{
    element *novi = (element *)malloc(sizeof(element));

    if (!novi)
        return -1;

    novi->next = HEAD->next;
    HEAD->next = novi;
    novi->broj = broj;

    return 0;
}

float popStack(element *HEAD)
{
    float broj = HEAD->next->broj;
    element *temp = HEAD->next;
    HEAD->next = HEAD->next->next;

    free(temp);
    return broj;
}

int izracunajPostfix(element *HEAD, char *filename)
{
    FILE *fp = NULL;
    char buffer[STRMAX];
    char *pBuffer = buffer;
    float operand1 = 0;
    float operand2 = 0;

    fp = fopen(filename, "r");

    if (!fp)
        return -1;

    fgets(buffer, STRMAX, fp);

    fclose(fp);

    while (strlen(pBuffer) > 0)
    {
        char operator= 0;
        int offset = 0;
        float broj = 0;
        if (sscanf(pBuffer, " %f%n", &broj, &offset) == 1)
        {
            pushStack(HEAD, broj);
            pBuffer += offset;
        }
        else
        {
            sscanf(pBuffer, " %c%n", &operator, &offset);
            izracunajOperaciju(HEAD, operator);
            pBuffer += offset;
        }
    }

    return 0;
}

int izracunajOperaciju(element* HEAD, char operator)
{
    float operand1 = 0;
    float operand2 = 0;

    switch (operator)
    {
    case ('*'):
        operand1 = popStack(HEAD);
        operand2 = popStack(HEAD);
        pushStack(HEAD, operand1 * operand2);
        break;
    case ('/'):
        operand1 = popStack(HEAD);
        operand2 = popStack(HEAD);
        pushStack(HEAD, operand2 / operand1);
        break;
    case ('+'):
        operand1 = popStack(HEAD);
        operand2 = popStack(HEAD);
        pushStack(HEAD, operand1 + operand2);
        break;
    case ('-'):
        operand1 = popStack(HEAD);
        operand2 = popStack(HEAD);
        pushStack(HEAD, operand2 - operand1);
        break;
	}

    return 0;
}