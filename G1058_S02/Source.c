#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

union Referinta
{
	char refIntern;
	unsigned short refExtern;
};
typedef union Referinta RefInfo;
struct Angajat
{
	char* nume;
	double salariu;
	RefInfo referinta;
};
typedef struct Angajat AngajatInfo;
//management info utila stocata in HEAP
AngajatInfo* creareAngajat(char*, double, short);
void dezalocareAngajat(AngajatInfo*);
void afisareAngajati(AngajatInfo**, short);
#define LINE_BUFFER 128
void main()
{
	AngajatInfo angajat;
	angajat.nume = NULL;
	angajat.salariu = 100.4;
	AngajatInfo* agenda[10];
	memset(agenda, NULL, sizeof(AngajatInfo*) * 10);
	char fileLineBuffer[LINE_BUFFER];
	FILE* pFile = fopen("Data.txt", "r");
	char* token; short referinta; double salariu;
	char nume[LINE_BUFFER];
	char separator[] = "\n,";
	if (pFile)
	{
		int index = 0;
		while (fgets(fileLineBuffer, sizeof(fileLineBuffer), pFile))
		{
			//citire nume
			token = strtok(fileLineBuffer, separator);
			strcpy(nume, token);
			//citire salariu
			token = strtok(NULL, separator);
			salariu = atof(token);
			//citire referinta
			token = strtok(NULL, separator);
			referinta = atoi(token);
			AngajatInfo* ang = creareAngajat(nume, salariu, referinta);
			agenda[index++] = ang;
		}
		afisareAngajati(agenda, sizeof(agenda)/sizeof(AngajatInfo*));
		fclose(pFile);
	}
}

void afisareAngajati(AngajatInfo** agenda, short noEl)
{
	for (int i = 0; i < noEl; i++)
	{
		AngajatInfo* angajat = agenda[i];
		if (angajat)
		{
			printf("Nume: %s, salariu: %f\n", angajat->nume, angajat->salariu);
			if (angajat->referinta.refExtern >> 15 == 1)
			{
				char contractor = angajat->referinta.refExtern >> 8;
				printf("Contractor: %d\n", contractor);
				printf("Referinta: %d\n", angajat->referinta.refExtern & 255);
			}
			else
				printf("Referinta: %d\n", angajat->referinta.refIntern);

		}
	}
}
void dezalocareAngajat(AngajatInfo* angajat)
{
	if (angajat != NULL)
	{
		free(angajat->nume);
		free(angajat);
	}
}

AngajatInfo* creareAngajat(char* nume, double salariu, short referinta)
{
	AngajatInfo* result = NULL;
	
	result = (AngajatInfo*)malloc(sizeof(AngajatInfo));
	result->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(result->nume, nume);
	result->salariu = salariu;
	result->referinta.refExtern = referinta;
	return result;
}