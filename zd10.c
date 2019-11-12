#include <stdio.h>
#include <stdlib.h>

#define STRMAX 1024

typedef struct _node
{
    char element;
    struct _node *left;
    struct _node *right;
} Node;

typedef struct _stack
{
    char element;
    struct _stack *next;
} Stack;

int postfixToStack(Stack *stackRoot, char *buffer);
int readFromFile(Stack *stackRoot, char *filename);
int isOperand(char element);
int pushStack(Stack *HEAD, char znak);

int main(void)
{
    Stack *ROOT = malloc(sizeof(Stack));
    ROOT->element = 0;
    ROOT->next = NULL;

    readFromFile(ROOT, "postfix.txt");

    return 0;
}

int readFromFile(Stack *stackRoot, char *filename)
{
    FILE *fp = NULL;
    char buffer[STRMAX] = {0};
    fp = fopen(filename, "r");

    if (!fp)
    {
        printf("Datoteka nije otvorena.\n");
        return -1;
    }

    fgets(buffer, STRMAX, fp);
    postfixToStack(stackRoot, buffer);

    return 0;
}

int postfixToStack(Stack *stackRoot, char *buffer)
{
    int offset = 0;
    char znak[11] = {0};

    while (sscanf(buffer, " %s %n", znak, &offset) == 1)
    {
        if (isOperand(znak[0]))
            pushStack(stackRoot, znak[0]);
        else
            pushStack(stackRoot, atoi(znak));
        buffer += offset;
        offset = 0;
    }

    return 0;
}

int isOperand(char element)
{
    switch (element)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return 1;
    }
    return 0;
}

int pushStack(Stack *HEAD, char znak)
{
    Stack *novi = (Stack *)malloc(sizeof(Stack));

    if (!novi)
        return -1;

    novi->next = HEAD->next;
    HEAD->next = novi;
    novi->element = znak;

    return 0;
}