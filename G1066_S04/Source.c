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
void displayStudents(StudentInfo**, int);
void displayStudent(StudentInfo*);
void printList(ListNode* list);
ListNode* insertListNodeTail(ListNode*, ListNode*);
ListNode* insertListNodeFront(ListNode*, ListNode*);
ListNode* createNode(StudentInfo*);
void insertListNodePosition(ListNode**, ListNode*, int);

#define LINE_SIZE 128
void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	ListNode* simpleLinkedList = NULL;

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
			//simpleLinkedList = insertListNodeFront(simpleLinkedList, node);
			simpleLinkedList = insertListNodeTail(simpleLinkedList, node);
			agenda[index++] = stud;
		}

		StudentInfo* info = createStudentInfo("Popescu Elena", 1200.23, 39800);
		ListNode* node = createNode(info);
		int position = 6;
		insertListNodePosition(&simpleLinkedList, node, position);

		printList(simpleLinkedList);
		//displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));
		fclose(pFile);
	}
}

void insertListNodePosition(ListNode** list, ListNode* node, int index)
{
	if (index == 1)
		*list = insertListNodeFront(*list, node);
	else
	{
		int i = 1;
		ListNode* aux = *list;
		while (aux->next != NULL && i < index - 1)
		{
			aux = aux->next;
			i++;
		}
		if (aux->next == NULL)
		{
			aux->next = insertListNodeTail(aux->next, node);
		}
		else
		{
			node->next = aux->next;
			aux->next = node;
		}
	}
}
void printList(ListNode* list)
{
	while (list)
	{
		displayStudent(list->info);
		list = list->next;
	}
}
ListNode* insertListNodeTail(ListNode* list, ListNode* node)
{

	if (list == NULL)
		return node;
	else
	{
		ListNode* head = list;
		while (list->next)
			list = list->next;
		list->next = node;
		return head;
	}
}
ListNode* insertListNodeFront(ListNode* list, ListNode* node)
{
	node->next = list;
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
void displayStudent(StudentInfo* stud)
{
	if (stud)
	{
		printf("Name: %s, income: %.2f\n", stud->name, stud->income);
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