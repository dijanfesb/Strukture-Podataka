#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int num;
    struct _tree * left;
    struct _tree * right;
} Tree;

Tree * insert(Tree * ROOT, int num);
int getNum(void);
Tree * allocateNew(int num);

int main()
{
    Tree * ROOT = NULL;

    ROOT = insert(ROOT, getNum());

    return 0;
}

Tree * insert(Tree * ROOT, int num)
{
    if (!ROOT)
        ROOT = allocateNew(num);
    else if (num<ROOT->num)
        ROOT = insert(ROOT->left, num);
    else if (num>ROOT->num)
        ROOT = insert(ROOT->right, num);

    return ROOT;  
}

int getNum(void)
{
    int n;
    
    printf("Unesite broj: \n");
    scanf("%d", &n);

    return n;
}

Tree * allocateNew(int num)
{
    Tree * newNode = malloc(sizeof(Tree));

    newNode->num=num;
    newNode->left=NULL;
    newNode->right=NULL;

    return newNode;
}