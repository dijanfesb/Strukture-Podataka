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
int popStack(element *HEAD);
int izracunajPostfix(element *HEAD, char *filename);

int main()
{
    element *HEAD = (element *)malloc(sizeof(element));
    HEAD->next = NULL;

    izracunajPostfix(HEAD, "postfix.txt");

    printf("%.3f\n", HEAD->next->broj);

    return 0;
}

int pushStack(element *HEAD, float broj)
{
    element *novi = (element *)malloc(sizeof(element));

    novi->next = HEAD->next;
    HEAD->next = novi;
    novi->broj = broj;

    return 0;
}

int popStack(element *HEAD)
{
    int broj = HEAD->next->broj;
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

            switch (operator)
            {
            case ('*'):
                operand1 = popStack(HEAD);
                operand2 = popStack(HEAD);
                pushStack(HEAD, operand1 * operand2);
                pBuffer += offset;
                break;
            case ('/'):
                operand1 = popStack(HEAD);
                operand2 = popStack(HEAD);
                pushStack(HEAD, operand2 / operand1);
                pBuffer += offset;
                break;
            case ('+'):
                operand1 = popStack(HEAD);
                operand2 = popStack(HEAD);
                pushStack(HEAD, operand1 + operand2);
                pBuffer += offset;
                break;
            case ('-'):
                operand1 = popStack(HEAD);
                operand2 = popStack(HEAD);
                pushStack(HEAD, operand2 - operand1);
                pBuffer += offset;
                break;
            default:
                pBuffer += 1;
                break;
            }
        }
    }

    return 0;
}