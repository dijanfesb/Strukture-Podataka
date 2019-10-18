#include <stdio.h>
#include <stdlib.h>

#define STRMAX 512

typedef struct polinom {
    int koeficijent;
    int eksponent;
    struct polinom * next;
} Clan;

int ucitajIzDatoteke(Clan * HEAD, char * fileName);


int main(void)
{
    char fileName[] = "eksponenti.txt";

    Clan * HEAD_1 = (Clan *)malloc(sizeof(Clan));
    Clan * HEAD_2 = (Clan *)malloc(sizeof(Clan));
    
    return 0;
}

int ucitajIzDatoteke(Clan * HEAD, char * fileName);
{
    FILE * fp = NULL;
    char linija[STRMAX];
    int koeficijent = 0;
    int eksponent = 0;

    fp = fopen(fileName, "r");

    if(!fp)
        return -1;

    fgets(linija, STRMAX, fp);

    fclose(fp);

    while(sscanf(linija, "%d %d", &koeficijent, &eksponent)) {
        
    }


    return 0;
}
