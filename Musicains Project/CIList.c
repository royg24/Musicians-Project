#include "CIList.h"


CListNode* createNewCListNode(ConcertInstrument data, CListNode* next)
{
	/*
	This function creates a new node for the CIList with a data given
	*/
	CListNode* newNode;

	newNode = (CListNode*)malloc(sizeof(CListNode));
	checkMalloc(newNode);

	newNode->data = data;
	newNode->next = next;
	return newNode;
}

bool isEmptyCList(CIList* lst)
{
	/*
	This function gets a CIList and checks if its empty
	*/
	if (lst->head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void makeEmptyCList(CIList* lst)
{
	/*
	This finction creates an empty MPIList
	*/
	lst->head = lst->tail = NULL;
}

void insertNodeToEndCList(CIList* lst, CListNode* tail)
{
	/*
	This function gets a node and adds it to the end of an CIList
	*/
	if (isEmptyCList(lst) == true)
	{
		lst->head = lst->tail = tail;
	}
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

void insertDataToEndCList(CIList* lst, ConcertInstrument data)
{
	/*
	This function creates a new node with a given data and adds it
	to the end of a CIList
	*/
	CListNode* newTail = NULL;
	newTail = createNewCListNode(data, NULL);
	insertNodeToEndCList(lst, newTail);
}

void printCList(CIList* lst)
{
	/*
	This function gets a CIList and prints its elements
	*/
	CListNode* curr = lst->head;

	while (curr != NULL)
	{
		printf("Num = %d | ID = %d | Importance is %c\n", curr->data.num, curr->data.inst, curr->data.importance);
		curr = curr->next;
	}
}

void freeCIList(CIList* lst)
{
	/*
	This function gets a CIList and frees its nodes
	*/
	CListNode* curr = lst->head, * temp;

	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
}

int NumOfMusician(CIList* lst)
{
	/*
	This function counts the number of musicians needed for a concert
	*/
	int counter = ZERO;
	CListNode* curr = lst->head;

	while (curr != NULL)
	{
		counter += curr->data.num;
		curr = curr->next;
	}
	return counter;

}