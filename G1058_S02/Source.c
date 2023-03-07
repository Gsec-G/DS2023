#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

union Referinta
{
	char refIntern;
	short refExtern;
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
#define LINE_BUFFER 128
void main()
{
	AngajatInfo angajat;
	angajat.nume = NULL;
	angajat.salariu = 100.4;
	AngajatInfo* agenda[10];
	char fileLineBuffer[LINE_BUFFER];
	FILE* pFile = fopen("Data.txt", "r");
	char* token; short referinta; double salariu;
	char nume[LINE_BUFFER];
	char separator[] = "\n,";
	if (pFile)
	{
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
		}
		
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