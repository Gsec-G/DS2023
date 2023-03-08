//MOUNAJED KARIM-RICHARD
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
union Referinta
{
	unsigned char refIntern; //1B
	unsigned short refExtern; //2B
};

typedef union Referinta RefInfo;
struct Angajat
{
	char* nume;
	double salariu;
	RefInfo referinta;
};

typedef struct Angajat AngInfo;
//management memorie info utila
AngInfo* creareAngajat(char*, double);
void* dezalocareAngajat(AngInfo*);
void afisareAngajati(AngInfo**, short);
#define LINE_SIZE 128
void main()
{
	AngInfo angajat;
	angajat.nume = "Popescu Maria";
	angajat.salariu = 23;

	AngInfo* agenda[10];
	memset(agenda, NULL, sizeof(agenda));

	FILE* pFile = fopen("Data.txt", "r");
	char* token; char separator[] = ",\n";
	char lineBuffer[LINE_SIZE];
	double salariu; unsigned short ref; char nume[LINE_SIZE];
	if (pFile)
	{
		int index = 0;
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
		{
			token = strtok(lineBuffer, separator);
			strcpy(nume, token);
			token = strtok(NULL, separator);
			salariu = atof(token);
			token = strtok(NULL, separator);
			ref = atoi(token);
			AngInfo* angajat = creareAngajat(nume, salariu, ref);
			agenda[index++] = angajat;
		}
		
		afisareAngajati(agenda, sizeof(agenda)/sizeof(AngInfo*));
		fclose(pFile);
	}
}

void afisareAngajati(AngInfo** agenda, short noEl)
{
	for (int i = 0; i < noEl; i++)
	{
		if (agenda[i] != NULL)
		{
			printf("Nume: %s, salariu: %f\n", agenda[i]->nume, agenda[i]->salariu);
			if (agenda[i]->referinta.refExtern >> 15 == 1)
			{
				char cid = agenda[i]->referinta.refExtern >> 8 & 127;
				printf("Contractor: %d\n", cid);
			}
			printf("Referinta: %d\n", agenda[i]->referinta.refIntern);
		}
	}
}
AngInfo* creareAngajat(const char* nume, double salariu, unsigned short ref)
{
	AngInfo* result = NULL;

	result = (AngInfo*)malloc(sizeof(AngInfo));
	result->nume = (char*)malloc((strlen(nume)));
	strcpy(result->nume, nume);
	result->salariu = salariu;
	result->referinta.refExtern = ref;
	return result;
}
void* dezalocareAngajat(AngInfo* angajat)
{
	if (angajat != NULL)
	{
		free(angajat->nume);
		free(angajat);
	}
	return NULL;
}