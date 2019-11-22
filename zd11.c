#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 256
#define TSIZE 11

typedef struct _node {
    char first[STRMAX];
    char last[STRMAX];
    int mbr;
    struct _node * next;
} Node;

Node * addNewElement(void);
Node ** initializeTable(int num);
int calculateHash(char * lastName, int tableSize);
int fillInElement(Node ** table, char * first, char * last, int mbr);
int readFromFile(Node ** table, char * filename);
int printTable(Node ** table, int tableSize);
int printList(Node * tableElement, int index);
Node * insertSorted(Node * rowHead, char * first, char * last);
Node * rewindToFirst(Node * tableElement, char * last);
int printMbr(Node * element);
Node * findElement(Node ** table, char * firstName, char * lastName);

int main(int argc, char * argv[])
{
    Node ** table = initializeTable(TSIZE);
    char firstName[STRMAX] = {0};
    char lastName[STRMAX] = {0};
    char select = 'n';

    if (argc<2) {
        printf("Unesite ime datoteke!");
        return -1;
    }

    readFromFile(table, argv[1]);

    printTable(table, TSIZE);

    do {
        printf("Unesite ime i prezime za ispis MBR-a [IME PREZIME]: ");
        scanf(" %s %s", firstName, lastName);
        printMbr(findElement(table, firstName, lastName));
        printf("Zelite li ispisati mbr za drugog korisnika? [y/n] ");
        scanf(" %c", &select);
    } while (select == 'y');

    return 0;
}

Node * addNewElement(void)
{
    Node * element = malloc(sizeof(Node));

    if (!element) {
        printf("Greska u alokaciji memorije!");
        return NULL;
    }

    memset(element->first, 0, STRMAX);
    memset(element->last, 0, STRMAX);

    element->mbr = 0;
    element->next = NULL;

    return element;
}

Node ** initializeTable(int num)
{
    int i = 0;
    Node ** table = malloc(num*sizeof(Node *));

    if (!table) {
        printf("Greska u alokaciji memorije!");
        return NULL;
    }

    for (i=0; i<num; i++) {
        table[i] = addNewElement();
    }

    return table;
}

int calculateHash(char * lastName, int tableSize)
{
    int sum = 0;
    int i = 0;

    for (i=0; i<5; i++) {
        sum += (int) lastName[i];
    }
    
    return sum%tableSize;
}

int fillInElement(Node ** table, char * first, char * last, int mbr)
{
    int position = calculateHash(last, TSIZE);
    Node * element = NULL;
    Node * temp = NULL;

    element = insertSorted(table[position], first, last);

    strcpy(element->first, first);
    strcpy(element->last, last);
    element->mbr = mbr;

    return 0;
}

int readFromFile(Node ** table, char * filename)
{
    char buffer[STRMAX] = {0};
    FILE * fp = fopen(filename, "r");

    if (!fp)
        return -1;

    while (!feof(fp)) {
        char first[STRMAX];
        char last[STRMAX];
        int mbr;
        fgets(buffer, STRMAX, fp);
        sscanf(buffer, "%s %s %d", first, last, &mbr);
        fillInElement(table, first, last, mbr);
    }

    fclose(fp);

    return 0;
}

int printTable(Node ** table, int tableSize)
{
    int i = 0;

    for (i=0; i<tableSize; i++)
        if (table[i]->next)
            printList(table[i]->next, i);
        else
            printf("%d) --- \n", i);

    return 0;
}

int printList(Node * tableElement, int index)
{
    Node * element = tableElement;

    printf("%d)", index);

    do {
        printf(" %s %s\t", element->first, element->last);
        element=element->next;
    } while(element);

    printf("\n");

    return 0;
}

Node * insertSorted(Node * rowHead, char * first, char * last)
{
    Node * element = rowHead;
    Node * temp = NULL;

    while (element->next && strcmp(last, element->next->last)>0)
        element=element->next;
    
    if (element->next && !strcmp(last, element->next->last)) {
        element = rewindToFirst(rowHead, last);
        while (element->next && !strcmp(last, element->next->last) && strcmp(first, element->next->first)>0)
            element=element->next;
    }

    temp = element->next;
    element->next = addNewElement();
    element = element->next;
    element->next = temp;

    return element;
}

Node * rewindToFirst(Node * tableElement, char * last)
{
    Node * element = tableElement;

    while (strcmp(element->next->last, last))
        element = element->next;

    return element;
}

Node * findElement(Node ** table, char * firstName, char * lastName)
{
    int position = calculateHash(lastName, TSIZE);

    Node * element = table[position]->next;

    while (element)
        if (!strcmp(element->last, lastName) && !strcmp(element->first, firstName))
            return element;
        else
            element = element->next;

    return element;
}

int printMbr(Node * element)
{
    if (!element)
        return -1;

    printf("%d\n", element->mbr);

    return 0;
}