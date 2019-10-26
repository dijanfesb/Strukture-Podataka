#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 512

typedef struct polinom {
    int koeficijent;
    int eksponent;
    struct polinom * next;
} Clan;

int ucitajIzDatoteke(Clan * HEAD_1, Clan * HEAD_2, char * fileName);
int umetniElementSortirano(Clan * HEAD, int koeficijent, int eksponent);
int procitajRed(Clan * HEAD, char * red);
int umetniElementIza(Clan * HEAD, Clan * element, Clan * novi);
Clan * pronadiPrethodniElement(Clan * HEAD, Clan * Pozicija);
int zbrojiPolinome(Clan * HEAD_1, Clan * HEAD_2, Clan * HEAD_SUM);
int pomnoziPolinome(Clan * HEAD_1, Clan * HEAD_2, Clan * HEAD_PRODUKT);
int ispis(Clan * HEAD);
int izbrisiElement(Clan * HEAD, Clan * prethodni, Clan * element);
int ocistiNulaElemente(Clan * HEAD);


int main(void)
{
    char fileName[] = "eksponenti.txt";

    Clan * HEAD_1 = (Clan *)malloc(sizeof(Clan));
    Clan * HEAD_2 = (Clan *)malloc(sizeof(Clan));
    Clan * HEAD_S = (Clan *)malloc(sizeof(Clan));
    Clan * HEAD_P = (Clan *)malloc(sizeof(Clan));

    HEAD_1->next=NULL;
    HEAD_2->next=NULL;
    HEAD_S->next=NULL;
    HEAD_P->next=NULL;

    ucitajIzDatoteke(HEAD_1, HEAD_2, fileName);

    printf("Prvi polinom: \n\t");
    ispis(HEAD_1);
    printf("\nDrugi polinom: \n\t");
    ispis(HEAD_2);
    
    zbrojiPolinome(HEAD_1, HEAD_2, HEAD_S);
    printf("\nSuma polinoma: \n\t");
    ispis(HEAD_S);
    pomnoziPolinome(HEAD_1, HEAD_2, HEAD_P);
    printf("\nUmnozak polinoma: \n\t");
    ispis(HEAD_P);
    printf("\n");
    
    return 0;
}

int ucitajIzDatoteke(Clan * HEAD_1, Clan * HEAD_2, char * fileName)
{
    FILE * fp = NULL;
    char linija[STRMAX];
    fp=fopen(fileName, "r");

    fgets(linija, STRMAX, fp);
    procitajRed(HEAD_1, linija);
    fgets(linija, STRMAX, fp);
    procitajRed(HEAD_2, linija);

    fclose(fp);
    return 0;
}

int procitajRed(Clan * HEAD, char * red)
{
    red[strlen(red)] = 0;
    int koeficijent = 0;
    int eksponent = 0;
    char * pRed = red;

    do {
        int n = 0;

        sscanf(pRed, " %d %d%n", &koeficijent, &eksponent, &n);
        pRed += n;

        umetniElementSortirano(HEAD, koeficijent, eksponent);
    } while (strlen(pRed)>1);
    
    return 0;
}

int umetniElementSortirano(Clan * HEAD, int koeficijent, int eksponent)
{
    Clan * P = HEAD;

    while(P->next!=NULL && P->next->eksponent>eksponent)
        P=P->next;

    if (P->next != NULL && P->next->eksponent == eksponent) {
            P->next->koeficijent+=koeficijent;
    }
    else {
        Clan * novi = (Clan *)malloc(sizeof(Clan));
        novi->next=P->next;
        P->next=novi;

        novi->koeficijent=koeficijent;
        novi->eksponent=eksponent;
    }

    return 0;
}


Clan * pronadiPrethodniElement(Clan * HEAD, Clan * Pozicija)
{
    Clan * P = HEAD;
    
    while(P!=NULL && P->next!=Pozicija)
        P=P->next;

    return P;
}

int ispis(Clan * HEAD)
{
    Clan * P = HEAD->next;

    while(P!=NULL) {
        printf("%dx^%d", P->koeficijent, P->eksponent);
        if (P->next != NULL)
            printf(" + ");
        P=P->next;
    }
}

int zbrojiPolinome(Clan * HEAD_1, Clan * HEAD_2, Clan * HEAD_SUM)
{
    Clan * pHEAD_1 = HEAD_1->next;
    Clan * pHEAD_2 = HEAD_2->next;

    while(pHEAD_1 != NULL) {
        umetniElementSortirano(HEAD_SUM, pHEAD_1->koeficijent, pHEAD_1->eksponent);
        pHEAD_1 = pHEAD_1->next;
    }

    while(pHEAD_2 != NULL) {
        umetniElementSortirano(HEAD_SUM, pHEAD_2->koeficijent, pHEAD_2->eksponent);
        pHEAD_2 = pHEAD_2->next;
    }

    ocistiNulaElemente(HEAD_SUM);

    return 0;
}

int pomnoziPolinome(Clan * HEAD_1, Clan * HEAD_2, Clan * HEAD_PRODUKT)
{
     Clan *pHEAD_1 = HEAD_1->next;
     Clan *pHEAD_2 = HEAD_2->next;
     
     while(pHEAD_1 != NULL) {
         pHEAD_2=HEAD_2->next;
         while(pHEAD_2 != NULL) {
             umetniElementSortirano(HEAD_PRODUKT, pHEAD_1->koeficijent*pHEAD_2->koeficijent, pHEAD_1->eksponent+pHEAD_2->eksponent);
             pHEAD_2=pHEAD_2->next;
         }
         pHEAD_1=pHEAD_1->next;
     }

    ocistiNulaElemente(HEAD_PRODUKT);

    return 0;
}

int ocistiNulaElemente(Clan * HEAD)
{
    Clan * P = HEAD;
    Clan * temp;
    
    while(P->next != NULL) {
        if (!P->next->koeficijent) {
            temp = P->next;
            P->next = P->next->next;
            free(temp);
        }
        P=P->next;
    }

    return 0;
}
