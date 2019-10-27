#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _listElement {
    int broj;
    struct _listElement * next;
} element;

int pushStack(element * HEAD, int broj);
int popStack(element * HEAD);
int pushQueue(element * HEAD, int broj);
int popQueue(element * HEAD);
int generateRandom(void);
int menu(element * HEAD_STACK, element * HEAD_QUEUE);

int main()
{
    element * HEAD_QUEUE = (element *)malloc(sizeof(element));
    element * HEAD_STACK = (element *)malloc(sizeof(element));

    if (!HEAD_QUEUE || !HEAD_STACK)
        return -1;

    HEAD_QUEUE->next = NULL;
    HEAD_STACK->next = NULL;

    int status = 0;

    srand((unsigned)time(NULL));

    do {
        status = menu(HEAD_STACK, HEAD_QUEUE);
    } while(status);

    return 0;
}

int pushStack(element * HEAD, int broj)
{
    element * novi = (element *)malloc(sizeof(element));

    if (!novi)
        return -1;

    novi->next=HEAD->next;
    HEAD->next = novi;
    novi->broj = broj;

    return 0;
}

int popStack(element * HEAD)
{
    int broj = HEAD->next->broj;
    element * temp = HEAD->next;
    HEAD->next=HEAD->next->next;

    free(temp);
    return broj;
}

int pushQueue(element * HEAD, int broj)
{
    element * novi = (element *)malloc(sizeof(element));

    if (!novi)
        return -1;

    novi->broj = broj;
    novi->next = HEAD->next;
    HEAD->next=novi;

    return 0;
}

int popQueue(element * HEAD) {
    element * P = HEAD;
    element * temp;
    int broj = 0;

    while(P->next->next != NULL)
        P=P->next;

    broj = P->next->broj;
    temp = P->next;
    P->next = NULL;
    free(temp);

    return broj;
}

int generateRandom(void)
{
    int broj = 0;

    broj = (rand()%90)+10;
    return broj;
}

int menu(element * HEAD_STACK, element * HEAD_QUEUE)
{
    int select = 0;
    int broj = 0;

    printf("Odaberi zeljenu opciju:\n\t");
    printf("1. Dodaj broj u stack\n\t");
    printf("2. Dodaj broj u queue\n\t");
    printf("3. Izbaci broj iz stacka\n\t");
    printf("4. Izbaci broj iz qeueuea\n\t");
    printf("0. Zatvori program\n\n");

    scanf("%d", &select);

    switch (select)
    {
        case (1):
            broj = generateRandom();
            pushStack(HEAD_STACK, broj);
            printf("Dodani broj [stack]: %d\n", broj);
            break;
        case (2):
            broj = generateRandom();
            pushQueue(HEAD_QUEUE, broj);
            printf("Dodani broj [queue]:%d\n", broj);
            break;
        case (3):
            if(HEAD_STACK->next != NULL) {
                printf("Izbaceni broj [stack]: %d\n", popStack(HEAD_STACK));
            }
            else
                printf("Stack je prazan!\n");
            break;
        case (4):
            if(HEAD_QUEUE->next != NULL) {
                    printf("Izbaceni broj [queue]: %d\n", popQueue(HEAD_QUEUE));
                }
                else
                    printf("Queue je prazan!\n");
                break;
        case (0):
            return 0;
    }

	return 1;
}