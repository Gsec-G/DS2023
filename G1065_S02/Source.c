#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Student
{
	char* name;
	double income;
	//char* const group;
};

typedef struct Student StudentInfo;

//useful info memory management
StudentInfo* createStudentInfo(char*, double);
void* deleteStudentInfo(StudentInfo*);

void main()
{
	StudentInfo student;
	student.name = "Popescu Maria";
	student.income = 1400.3;

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		StudentInfo* agenda[10];

		fclose(pFile);
	}
}

StudentInfo* createStudentInfo(const char* name, double income)
{
	StudentInfo* result = NULL;

	result = (StudentInfo*)malloc(sizeof(StudentInfo));
	result->name = (char*)malloc(strlen(name) + 1);
	strcpy(result->name, name);
	result->income = income;

	return result;

}
