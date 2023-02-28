#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct AngStruct
{
	char* nume;
	double salariu;
};

typedef struct AngStruct Angajat;
//management memorie info utila
Angajat* creareAngajat(char*, double);
void* dezalocareAngajat(Angajat*);

void main()
{
	Angajat angajat;
	angajat.nume = "Popescu Maria";
	angajat.salariu = 23;

	Angajat* agenda[10];

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		Angajat* angajat = creareAngajat("Popescu Maria", 1500.3);
		fclose(pFile);
	}
}
Angajat* creareAngajat(const char* nume, double salariu)
{
	Angajat* result = NULL;

	result = (Angajat*)malloc(sizeof(Angajat));
	result->nume = (char*)malloc((strlen(nume)));
	strcpy(result->nume, nume);
	result->salariu = salariu;
	return result;
}
void* dezalocareAngajat(Angajat* angajat)
{
	if (angajat != NULL)
	{
		free(angajat->nume);
		free(angajat);
	}
	return NULL;
}