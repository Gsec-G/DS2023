#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

union Reference
{
	unsigned char intRef;
	unsigned short extRef;
};

typedef union Reference RefInfo;

struct Student
{
	char* name;
	double income;
	RefInfo reference;
};

typedef struct Student StudentInfo;

struct Node
{
	StudentInfo* info;
	struct Node* next;
};

typedef struct Node ListNode;

//useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudent(StudentInfo*);
void displayStudents(StudentInfo**, int);
ListNode* createNode(StudentInfo*);
ListNode* insertNodeToEnd(ListNode*, ListNode*);
void insertNodeToHead(ListNode**, ListNode*);
void printList(ListNode*);
#define LINE_SIZE 128

void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	ListNode* simpleLinkedList1 = NULL;
	ListNode* simpleLinkedList2 = NULL;

	if (pFile)
	{
		StudentInfo* agenda[10];
		memset(agenda, 0, sizeof(agenda));
		char* token; char delimiter[] = ",\n";
		double income; unsigned short ref;
		char lineBuffer[LINE_SIZE], name[LINE_SIZE];
		int index = 0;
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
		{
			token = strtok(lineBuffer, delimiter);
			strcpy(name, token);
			token = strtok(NULL, delimiter);
			income = atof(token);
			token = strtok(NULL, delimiter);
			ref = atoi(token);
			StudentInfo* stud = createStudentInfo(name, income, ref);
			ListNode* node = createNode(stud);
			simpleLinkedList1 = insertNodeToEnd(simpleLinkedList1, node);
			insertNodeToHead(&simpleLinkedList2, node);
			agenda[index++] = stud;
		}
		//displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));
		printList(simpleLinkedList1);
		printList(simpleLinkedList2);
		fclose(pFile);
	}
}
void insertNodeToHead(ListNode** initialList, ListNode* node)
{
	node->next = *initialList;
	*initialList = node;
}
void printList(ListNode* list)
{
	while (list)
	{
		displayStudent(list->info);
		list = list->next;
	}
}
ListNode* insertNodeToEnd(ListNode* initialList, ListNode* node)
{
	if (initialList)
	{
		//cross through the list
		ListNode* aux = initialList;
		while (aux->next)
			aux = aux->next;
		aux->next = node;
		return initialList;
	}
	else
		return node;
}
ListNode* createNode(StudentInfo* stud)
{
	ListNode* result = NULL;
	result = (ListNode*)malloc(sizeof(ListNode));
	result->info = stud;
	result->next = NULL;
	return result;
}
void displayStudent(StudentInfo* student)
{
	if (student)
	{
		printf("Name: %s, income: %f\n", student->name, student->income);
		if (student->reference.extRef >> 15 == 1)
		{
			short uid = student->reference.extRef >> 8 & 127;
			printf("University ref: %d\n", uid);
			printf("External ref: %d\n", student->reference.extRef & 255);
		}
		else
		{
			printf("Internal ref: %d\n", student->reference.intRef);
		}
	}
}
void displayStudents(StudentInfo** agenda, int noEl)
{
	for (int i = 0; i < noEl; i++)
	{
		displayStudent(agenda[i]);
	}
}
void* deleteStudentInfo(StudentInfo* stud)
{
	if (stud != NULL)
	{
		free(stud->name);
		free(stud);
	}
	return NULL;
}
StudentInfo* createStudentInfo(const char* name, double income, unsigned short ref)
{
	StudentInfo* result = NULL;

	result = (StudentInfo*)malloc(sizeof(StudentInfo));
	result->name = (char*)malloc(strlen(name) + 1);
	strcpy(result->name, name);
	result->income = income;
	result->reference.extRef = ref;
	return result;

}