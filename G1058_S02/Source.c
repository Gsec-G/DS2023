#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
struct Angajat
{
	char* nume;
	double salariu;
};
typedef struct Angajat AngajatInfo;
//management info utila stocata in HEAP
AngajatInfo* creareAngajat(char*, double);
void dezalocareAngajat(AngajatInfo*);

void main()
{
	AngajatInfo angajat;
	angajat.nume = NULL;
	angajat.salariu = 100.4;

	AngajatInfo* agenda[10];

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		AngajatInfo* ang = creareAngajat("Popescu Maria", 1200.0);
		fclose(pFile);
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

AngajatInfo* creareAngajat(char* nume, double salariu)
{
	AngajatInfo* result = NULL;
	
	result = (AngajatInfo*)malloc(sizeof(AngajatInfo));
	result->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(result->nume, nume);
	result->salariu = salariu;

	return result;
}