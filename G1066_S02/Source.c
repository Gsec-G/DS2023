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
#define LINE_SIZE 128
void main()
{
	Student student = {.name ="Popescu Maria"};
	//student.name = "Popescu Maria";
	//student.name = "Ionescu Ioan";
	//student.name[3] = 'd';
	student.income = 1300.5;
	
	Student* agenda[10];

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