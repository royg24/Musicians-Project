#include "MPIList.h"

MListNode* createNewMListNode(MusicianPriceInstrument data, MListNode* next)
{
	/*
	This function creates a new node for the MPIList with a data given
	*/
	MListNode* newNode;
	newNode = (MListNode*)malloc(sizeof(MListNode));
	checkMalloc(newNode);

	newNode->data = data;
	newNode->next = next;

	return newNode;
}

bool isEmptyMList(MPIList* lst)
{
	/*
	This function gets a MPIList and checks if its empty
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

void makeEmptyMList(MPIList* lst)
{
	/*
	This finction creates an empty MPIList
	*/
	lst->head = lst->tail = NULL;
}

void insertNodeToEndMList(MPIList* lst, MListNode* tail)
{
	/*
	This function gets a node and adds it to the end of an MPIList
	*/
	if (isEmptyMList(lst) == true)
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

void insertDataToEndMList(MPIList* lst, MusicianPriceInstrument data)
{
	/*
	This function creates a new node with a given data and adds it
	to the end of a MPIList
	*/
	MListNode* newTail = NULL;
	newTail = createNewMListNode(data, NULL);
	insertNodeToEndMList(lst, newTail);
}

void printMList(MPIList* lst)
{
	/*
	This function gets a MPList and prints its elements
	*/
	MListNode* curr = lst->head;

	while (curr != NULL)
	{
		printf("ID = %u | Price = %f\n", curr->data.insID, curr->data.price);
		curr = curr->next;
	}
}

void freeMPIList(MPIList* lst)
{
	/*
	This function gets a MPIList and frees its nodes
	*/
	MListNode* curr = lst->head, *temp;

	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
}

float findPrice(MPIList* lst, short int insID)
{
	/*
	This function finds the price of a specific instrument from the list
	*/
	MListNode* curr;
	curr = lst->head;

	while (curr != NULL)
	{
		if (curr->data.insID == insID)
		{
			return curr->data.price;
		}
		curr = curr->next;
	}
	return ZERO_FLOAT;
}