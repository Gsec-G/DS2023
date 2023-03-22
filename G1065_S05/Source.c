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
	struct Node* prev;
	StudentInfo* info;
	struct Node* next;
};

typedef struct Node ListNode;

//useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudents(StudentInfo**, int);
void displayStudent(StudentInfo*);
ListNode* createNode(StudentInfo*);
ListNode* insertOnPosition(ListNode*, ListNode*, int);
void printList(ListNode*);

#define LINE_SIZE 128

void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	ListNode* doubleLinkedList = NULL;
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

			doubleLinkedList = insertOnPosition(doubleLinkedList, node, index);
			agenda[index++] = stud;
		}
		//displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));
		StudentInfo* stud = createStudentInfo("Popa Maria", 3200.4, 39089);
		ListNode* node = createNode(stud);
		insertOnPosition(doubleLinkedList, node, 3);

		printList(doubleLinkedList);
		fclose(pFile);
	}
}
void printList(ListNode* list)
{
	while (list->next)
	{
		displayStudent(list->info);
		list = list->next;
	}
	displayStudent(list->info);
	while (list)
	{
		displayStudent(list->info);
		list = list->prev;
	}
}

ListNode* insertOnPosition(ListNode* list, ListNode* node, int position)
{
	if (position <= 0)
	{
		if (list != NULL)
		{
			node->next = list;
			list->prev = node;
		}
		list = node;
	}
	else
	{
		ListNode* aux = list;
		int index = 0;
		while (aux->next != NULL && index < position-1)
		{
			aux = aux->next;
			index++;
		}
		if (aux->next == NULL)
		{
			node->prev = aux;
			aux->next = node;
		}
		else
		{
			node->next = aux->next;
			node->prev = aux;
			aux->next->prev = node;
			aux->next = node;
		}
	}
	return list;
}

ListNode* createNode(StudentInfo* stud)
{
	ListNode* result = NULL;
	result = (ListNode*)malloc(sizeof(ListNode));
	result->info = stud;
	result->next = result->prev = NULL;
	return result;
}
void displayStudent(StudentInfo* stud)
{
	if (stud)
	{
		printf("Name: %s, income: %f\n", stud->name, stud->income);
		if (stud->reference.extRef >> 15 == 1)
		{
			short uid = stud->reference.extRef >> 8 & 127;
			printf("University ref: %d\n", uid);
			printf("External ref: %d\n", stud->reference.extRef & 255);
		}
		else
		{
			printf("Internal ref: %d\n", stud->reference.intRef);
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