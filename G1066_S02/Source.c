#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Stud
{
	char* name; //4B
	double income; //8B
};

typedef struct Stud Student;

//1. const char* name;
//2. char const* name;
//3. char* const name;
//4. const char* const name;

Student* createStudent(const char*, double);
void* deleteStudent(Student*);

void main()
{
	Student student = {.name ="Popescu Maria"};
	//student.name = "Popescu Maria";
	//student.name = "Ionescu Ioan";
	//student.name[3] = 'd';
	student.income = 1300.5;
	
	Student* agenda[10];



}
//Student* student = (Student*)malloc()

Student* createStudent(const char* name, double income)
{
	//1.declare the value
	Student* result = NULL;
	//2.allocate memory
	result = (Student*)malloc(sizeof(Student));
	result->name = (char*)malloc(strlen(name) + 1);
	//3.initialize attributes
	strcpy(result->name, name);
	result->income = income;
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
}