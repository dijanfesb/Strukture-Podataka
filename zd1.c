#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>

typedef struct _student {
	char ime[10];
	char prezime[10];
	int bodovi;
}Student;

int main()
{
	FILE * fp;
	int br_red = 0;
	int i;
	Student * studenti;
	int maxbr;
	char buf[1024];

	fp = fopen("C:\\Users\\student\\Documents\\studenti.txt", "r");

	while (fgets(buf, 60, fp)) br_red++;
	studenti = (Student *)malloc(sizeof(Student) * br_red);

	rewind(fp);

	for (i = 0; i < br_red; i++) {
		fscanf(fp, "%d %s %s", &(studenti[i].bodovi), studenti[i].ime, studenti[i].prezime);
	}

	maxbr = studenti[0].bodovi;
	for(i=0; i<br_red; i++)
		if (studenti[i].bodovi > maxbr) maxbr = studenti[i].bodovi;

	for (i = 0; i < br_red; i++) printf("Ime: %s, Prezime: %s, Bodovi: %d, Relativni: %.2lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, (double)(studenti[i].bodovi*100/maxbr));

	system("PAUSE");

	return 0;

}