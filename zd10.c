//TODO: Zagrade

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define STRMAX 1024
#define ELEMENTMAX 21

typedef struct _node
{
    char element[ELEMENTMAX];
    struct _node *left;
    struct _node *right;
} Node;

typedef struct _stack
{
    char element[ELEMENTMAX];
    struct _stack *next;
} Stack;

int postfixToStack(Stack *stackRoot, char *buffer);
int readFromFile(Stack *stackRoot, char *filename);
int isOperand(char element);
int pushStack(Stack *HEAD, char * znak);
char * popStack(Stack * HEAD);
Node * stackToTree(Stack * HEAD, Node * ROOT);
Node * allocateNewNode(void);
int inorderPrint(Node * ROOT);

int main(void)
{
    char filename[STRMAX];
    Stack *HEAD = malloc(sizeof(Stack));
    Node *ROOT = allocateNewNode();
    HEAD->next = NULL;
    memset(HEAD->element, 0, ELEMENTMAX);

    printf("Unesite ime datoteke: ");
    scanf(" %s", filename);

    readFromFile(HEAD, filename);

    ROOT = stackToTree(HEAD, ROOT);

    inorderPrint(ROOT);

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
    char znak[ELEMENTMAX] = {0};

    while (sscanf(buffer, " %s %n", znak, &offset) == 1)
    {
            pushStack(stackRoot, znak);
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

int pushStack(Stack *HEAD, char * znak)
{
    Stack *novi = (Stack *)malloc(sizeof(Stack));

    if (!novi)
        return -1;

    novi->next = HEAD->next;
    HEAD->next = novi;
    strcpy(novi->element, znak);

    return 0;
}

char * popStack(Stack * HEAD)
{
    char * tempStr = malloc(sizeof(char));

    if (!HEAD->next)
        return NULL;

    Stack * temp = HEAD->next;
    strcpy(tempStr, temp->element);
    HEAD->next=HEAD->next->next;
    free(temp);

    return tempStr;
}

Node * stackToTree(Stack * HEAD, Node * ROOT)
{
    char * element = popStack(HEAD);

    ROOT = allocateNewNode();

    if (!element)
        return NULL;

    strcpy(ROOT->element, element);
    
    if (isOperand(ROOT->element[0])) {
        ROOT->right = stackToTree(HEAD, ROOT->right);
        ROOT->left = stackToTree(HEAD, ROOT->left);
    }

    return ROOT;    
}

Node * allocateNewNode(void)
{
    Node * newNode = malloc(sizeof(Node));
    newNode->left=NULL;
    newNode->right=NULL;

    return newNode;
}

int inorderPrint(Node * ROOT)
{
    if (!ROOT)
        return 0;

    inorderPrint(ROOT->left);

    printf("%s", ROOT->element);

    inorderPrint(ROOT->right);
}