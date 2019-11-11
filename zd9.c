#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int num;
    struct _tree * left;
    struct _tree * right;
} Tree;

Tree * insert(Tree * ROOT, int num);
Tree * findElement(const Tree * ROOT, int num);
int getNum(void);
Tree * allocateNew(int num);
int printTree(const Tree * ROOT, int space);
int treeDepth(const Tree * ROOT);
Tree * findMin(Tree * node);
Tree * deleteElement(const Tree * ROOT, Tree * element);
Tree * menu(Tree * ROOT);

int main()
{
    Tree * ROOT = NULL;

    do {
        ROOT = menu(ROOT);
    } while (ROOT);


    return 0;
}

Tree * insert(Tree * ROOT, int num)
{
    if (!ROOT)
        ROOT = allocateNew(num);
    else if (num<ROOT->num)
        ROOT->left = insert(ROOT->left, num);
    else if (num>ROOT->num)
        ROOT->right = insert(ROOT->right, num);

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

Tree * findElement(const Tree * ROOT, int num)
{
    Tree * node = (Tree *)ROOT;
    if (!node)
        return NULL;
    else if (num<node->num)
        node = findElement(node->left, num);
    else if (num>node->num)
        node = findElement(node->right, num);
    
    return node;    
}

int printTree(const Tree * ROOT, int space)
{
    Tree * node = (Tree *)ROOT;
    int i = 0;

    if (!node)
        return 0;

    printTree(node->right, space+10);
    printf("\n");

    for (i=10; i<space+10; i++)
        printf(" ");

    printf("%d\n", node->num);
    printTree(node->left, space+10);
}

int treeDepth(const Tree * ROOT)
{
    Tree * node = (Tree *)ROOT;

    int Ldepth = 0;
    int Rdepth = 0;

    if(!node)
        return 0;

    Ldepth = treeDepth(node->left);
    Rdepth = treeDepth(node->right);

    if (Ldepth>Rdepth)
        return Ldepth+1;
    else if (Ldepth<Rdepth)
        return Rdepth+1;

    return Ldepth+1;
}

Tree * findMin(Tree * node)
{
    if (!node)
        return NULL;
    else if (!node->left)
        return node;
    
    return findMin(node->left);
}

Tree * deleteElement(const Tree * ROOT, Tree * Element)
{
    Tree * node = (Tree *)ROOT;
    Tree * temp = NULL;

    if (!node)
        return NULL;
    else if (Element->num<node->num)
        node->left = deleteElement(node->left, Element);
    else if (Element->num>node->num)
        node->right = deleteElement(node->right, Element);
    else if (node->left && node->right) {
        temp = findMin(node->right);
        node->num = temp->num;
        node->right = deleteElement(node->right, node);
    }
    else {
        temp = node;
        if (!node->left)
            node = node->right;
        else
            node = node->left;
        free(temp);
    }

    return node;
}

Tree * menu(Tree * ROOT)
{
    int izbor = 0;

    printf("Odaberite operaciju: \n");
    printf("\t1.) Unesi element\n");
    printf("\t2.) Izbrisi element\n");
    printf("\t3.) Ispisi stablo\n");
    printf("\t0.) Zatvori program\n");
    
    scanf("%d", &izbor);

    switch (izbor) {
        case 1:
            ROOT = insert(ROOT, getNum());
            return ROOT;
        case 2:
            ROOT = deleteElement(ROOT, findElement(ROOT, getNum()));
            return ROOT;
        case 3:
            printTree(ROOT, 10);
            return ROOT;
        case 0:
            return NULL;
    }
}