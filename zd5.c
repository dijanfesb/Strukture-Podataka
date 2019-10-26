#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STRMAX 1024

typedef struct _struktura {
    int broj;
    struct _struktura * next;
} element;

int unesiIzDatoteke(element * HEAD, char * fileName);
int unesiSortirano(element * HEAD, int broj);
int unijaListi(element * HEAD_1, element * HEAD_2, element * HEAD_UNIJA);
int presjekListi(element * HEAD_1, element * HEAD_2, element * HEAD_PRESJEK);
int elementPostojiUListi(element * HEAD, element * el);
int ispis(element * HEAD);
int unesiIzStdin(element * HEAD);
int unesiIzDatoteke(element * HEAD, char * fileName);

int main()
{
    char select = 0;

    element * HEAD_L1 = (element *)malloc(sizeof(element));
    element * HEAD_L2 = (element *)malloc(sizeof(element));
    element * HEAD_UNIJA = (element *)malloc(sizeof(element));
    element * HEAD_PRESJEK = (element *)malloc(sizeof(element));

    if (!HEAD_L1 || !HEAD_L2 || !HEAD_PRESJEK || !HEAD_UNIJA)
        return -1;

    HEAD_L1->next=NULL;
    HEAD_L2->next=NULL;
    HEAD_UNIJA->next=NULL;
    HEAD_PRESJEK->next=NULL;


    printf("Zelite li unos iz datoteke [D] ili iz standardnog ulaza [S]? ");
    scanf(" %c", &select);

    select = toupper(select);

    if (select == 'D') {
        char fileName[STRMAX];
        printf("Unesi ime datoteke [LISTA 1]: ");
        scanf("%s", fileName);
        unesiIzDatoteke(HEAD_L1, fileName);
        printf("Unesi ime datoteke [LISTA 2]: ");
        scanf("%s", fileName);
        unesiIzDatoteke(HEAD_L2, fileName);
    }
    else if (select == 'S') {
        printf("Unos prve liste: \n");
        unesiIzStdin(HEAD_L1);
        printf("Unos druge liste: \n");
        unesiIzStdin(HEAD_L2);
    }

    unijaListi(HEAD_L1, HEAD_L2, HEAD_UNIJA);
    presjekListi(HEAD_L1, HEAD_L2, HEAD_PRESJEK);

    printf("Lista 1: ");
    ispis(HEAD_L1);
    printf("\nLista 2: ");
    ispis(HEAD_L2);
    printf("\nUnija: ");
    ispis(HEAD_UNIJA);
    printf("\nPresjek: ");
    ispis(HEAD_PRESJEK);


    return 0;
}

int unesiIzDatoteke(element * HEAD, char * fileName)
{
    element * P = HEAD;
    FILE * fp = NULL;
    char red[STRMAX];
    fp = fopen(fileName, "r");

    if(!fp)
        return -1;

    while(fgets(red, STRMAX, fp)) {
        unesiSortirano(HEAD, atoi(red));
    }

    fclose(fp);
    return 0;
}

int unesiSortirano(element * HEAD, int broj)
{
    element * P = HEAD;
    element * novi = (element *)malloc(sizeof(element));
    
    if (!novi)
        return -1;

    while(P->next != NULL && P->next->broj < broj)
        P=P->next;

    novi->next = P->next;
    P->next = novi;
    novi->broj = broj;

    return 0;
}

int unijaListi(element * HEAD_1, element * HEAD_2, element * HEAD_UNIJA)
{
    element * pHEAD_1 = HEAD_1->next;
    element * pHEAD_2 = HEAD_2->next;

    while(pHEAD_1 != NULL) {
        if (!elementPostojiUListi(HEAD_UNIJA, pHEAD_1))
            unesiSortirano(HEAD_UNIJA, pHEAD_1->broj);
        pHEAD_1 = pHEAD_1->next;
    }
    while(pHEAD_2 != NULL) {
        if (!elementPostojiUListi(HEAD_UNIJA, pHEAD_2))
            unesiSortirano(HEAD_UNIJA, pHEAD_2->broj);
        pHEAD_2 = pHEAD_2->next;
    }

    return 0;
}

int presjekListi(element * HEAD_1, element * HEAD_2, element * HEAD_PRESJEK)
{
    element * pHEAD_1 = HEAD_1->next;
    element * pHEAD_2 = HEAD_2->next;

    while(pHEAD_1!=NULL) {
        if(elementPostojiUListi(HEAD_2, pHEAD_1) && !elementPostojiUListi(HEAD_PRESJEK, pHEAD_1))
            unesiSortirano(HEAD_PRESJEK, pHEAD_1->broj);
        pHEAD_1=pHEAD_1->next;
    }
    while(pHEAD_2!=NULL) {
        if(elementPostojiUListi(HEAD_1, pHEAD_2) && !elementPostojiUListi(HEAD_PRESJEK, pHEAD_2))
            unesiSortirano(HEAD_PRESJEK, pHEAD_2->broj);
        pHEAD_2=pHEAD_2->next;
    }

    return 0;
}

int elementPostojiUListi(element * HEAD, element * el)
{
    element * P = HEAD->next;

    while(P!=NULL && P->broj != el->broj)
        P=P->next;

    if (P==NULL)
        return 0;
    
    return 1;
}

int ispis(element * HEAD)
{
    element * P = HEAD->next;

    while (P!=NULL) {
        printf("%d ", P->broj);
        P=P->next;
    }
    printf("\n");

    return 0;
}

int unesiIzStdin(element * HEAD)
{
    int i = 0;
    int n = 0;
    int tempbr = 0;

    printf("Koliko elemenata zelite unijeti? ");
    scanf("%d", &n);

    for(i=0; i<n; i++) {
        printf("Unesi broj [%d.]: ", i+1);
        scanf("%d", &tempbr);
        unesiSortirano(HEAD, tempbr);
    }

    return 0;
}