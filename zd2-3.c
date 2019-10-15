#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 1024

typedef struct _student {
    char ime[STRMAX];
    char prezime[STRMAX];
    int godinaRodenja;
    struct _student * next;
} Student;

int unosPocetak(Student * HEAD);
int unosKraj(Student * HEAD);
int ispis(Student * HEAD);
Student * pronadiElement(Student * HEAD, char * prezime);
int brisiElement(Student * HEAD, Student * element);
int dodajElementIza(Student * element);
int dodajElementIspred(Student * HEAD, Student * element);
int spremiUDatoteku(Student * HEAD, char * filename);
/* int sortirajPoPrezimenu(Student * HEAD);  TODO */

int main(void)
{
    Student * HEAD = (Student *)malloc(sizeof(Student));
    char prezime[STRMAX] = {0};
    int i = 0;

    unosPocetak(HEAD);

    ispis(HEAD);

    for (i=0; i<5; i++)
        unosKraj(HEAD);

    ispis(HEAD);

    printf("Unesi prezime za brisanje: ");
    scanf("%s", prezime);

    brisiElement(HEAD, pronadiElement(HEAD, prezime));
    ispis(HEAD);

    printf("Unesi prezime za unos iza: ");
    scanf("%s", prezime);
    dodajElementIza(pronadiElement(HEAD, prezime));

    ispis(HEAD);

    printf("Unesi prezime za unos ispred: ");
    scanf("%s", prezime);
    dodajElementIspred(HEAD, pronadiElement(HEAD, prezime));

    ispis(HEAD);

    spremiUDatoteku(HEAD, "studenti1.txt");

    return 0;
}

int unosPocetak(Student * HEAD)
{
    Student * element = (Student *)malloc(sizeof(Student));

    element->next = HEAD->next;
    HEAD->next = element;

    printf("Unesi ime, prezime i godinu rodenja studenta [IME PREZIME GODINA]: ");
    scanf("%s %s %d", element->ime, element->prezime, &(element->godinaRodenja));

    return 0;
}

int ispis(Student * HEAD)
{
    Student * P = HEAD->next;

    while(P!=NULL) {
        printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d\n\n", P->ime, P->prezime, P->godinaRodenja);
        P=P->next;
    }

    return 0;
}

int unosKraj(Student * HEAD)
{
    Student * element = (Student *)malloc(sizeof(Student));
    Student * P = HEAD;

    while (P->next!=NULL)
        P=P->next;
    
    element->next = NULL;
    P->next=element;

    printf("Unesi ime, prezime i godinu rodenja studenta [IME PREZIME GODINA]: ");
    scanf("%s %s %d", element->ime, element->prezime, &(element->godinaRodenja));

    return 0; 
}

Student * pronadiElement(Student * HEAD, char * prezime)
{
    Student * P = HEAD->next;

    while(P != NULL && strcmp(P->prezime, prezime)) {
        P=P->next;
    }

    return P;
}

int brisiElement(Student * HEAD, Student * element)
{
    Student * P = HEAD;

    while (P != NULL && P->next != element) {
        P=P->next;
    }

    if (P==NULL)
        return -1;
    else
    {
            P->next=P->next->next;
            free(element);
    }

    return 0;
}

int dodajElementIza(Student * element)
{
    Student * noviElement = (Student *)malloc(sizeof(Student));

    noviElement->next = element->next;
    element->next = noviElement;

    printf("Unesi ime, prezime i godinu rodenja studenta [IME PREZIME GODINA]: ");
    scanf("%s %s %d", noviElement->ime, noviElement->prezime, &(noviElement->godinaRodenja));

    return 0;
}

int dodajElementIspred(Student * HEAD, Student * element)
{
    Student * P = HEAD;
    Student * noviElement = (Student *)malloc(sizeof(Student));

    while (P != NULL && P->next != element)
        P=P->next;

    if (P == NULL) {
        free(noviElement);
        return -1;
    }

    dodajElementIza(P);

    return 0;
}

int spremiUDatoteku(Student * HEAD, char * filename)
{
    Student * P = HEAD->next;
    FILE * fp = NULL;
    fp = fopen(filename, "w");

    if (fp==NULL)
        return -1;

    while (P!=NULL) {
        fprintf(fp, "Ime: %s, Prezime: %s, Godina rodenja: %d\n", P->ime, P->prezime, P->godinaRodenja);
        P=P->next;
    }

    fclose(fp);
    
    return 0;
}