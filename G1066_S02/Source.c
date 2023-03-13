#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
union Ref
{
	unsigned char intRef;
	unsigned short extRef;
};
typedef union Ref Reference;

struct Stud
{
	char* name; //4B
	double income; //8B
	Reference reference; //2B
};

typedef struct Stud Student;

//1. const char* name;
//2. char const* name;
//3. char* const name;
//4. const char* const name;

Student* createStudent(const char*, double, unsigned short);
void* deleteStudent(Student*);
void displayStudents(Student**, int);
#define LINE_SIZE 128
void main()
{
	Student student = {.name ="Popescu Maria"};
	//student.name = "Popescu Maria";
	//student.name = "Ionescu Ioan";
	//student.name[3] = 'd';
	student.income = 1300.5;
	
	Student* agenda[10];
	memset(agenda, NULL, sizeof(agenda));

	FILE* pFile = fopen("Data.txt","r");
	if (pFile)
	{
		const int n = 128;
		char lineBuffer[LINE_SIZE], name[LINE_SIZE];
		double income; unsigned short ref;
		char* token; char delimiter[] = "\n,";
		int index = 0;
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
		{
			token = strtok(lineBuffer, delimiter);
			strcpy(name, token);
			token = strtok(NULL, delimiter);
			income = atof(token);
			token = strtok(NULL, delimiter);
			ref = atoi(token);
			Student* stud = createStudent(name, income, ref);
			agenda[index++] = stud;
		}
		displayStudents(agenda, sizeof(agenda)/sizeof(Student*));
	}
}
void displayStudents(Student** agenda, int noEl)
{
	//10000001 00000011
	//00000000 00000001
	for (int i = 0; i < noEl; i++)
	{
		if (agenda[i]) {
			printf("Name: %s, income: %f\n", agenda[i]->name, agenda[i]->income);
			if (agenda[i]->reference.extRef >> 15 == 1)
			{	//10000001 00000011
				char univId = agenda[i]->reference.extRef >> 8 & 127;
				//00000000 10000001
				printf("University ref: %d\n", univId);
				printf("External ref: %d\n", agenda[i]->reference.extRef & 255);
			}
			else
				printf("Internal ref: %d\n", agenda[i]->reference.intRef);
		}
	}
}
//Student* student = (Student*)malloc()

Student* createStudent(const char* name, double income,unsigned short ref)
{
	//1.declare the value
	Student* result = NULL;
	//2.allocate memory
	result = (Student*)malloc(sizeof(Student));
	result->name = (char*)malloc(strlen(name) + 1);
	//3.initialize attributes
	strcpy(result->name, name);
	result->income = income;
	result->reference.extRef = ref;
	//4.return value
	return result;
}

void* deleteStudent(Student* student)
{
	if (student)
	{
		free(student->name);
		free(student);
	}
	return NULL;
}