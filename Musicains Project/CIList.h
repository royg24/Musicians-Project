#ifndef CILIST_H
#define CILIST_H

typedef struct {
	int num; //amount of this instrument
	int inst; // ID of the instrument
	char importance; //if this instrument needs high budget
}ConcertInstrument;

typedef struct clistNode {
	ConcertInstrument data; //data of the instrument
	struct clistNode* next;
}CListNode;

typedef struct {
	CListNode* head;
	CListNode* tail;
}CIList;

#include "General.h"


//create new ListNode with data given
CListNode* createNewCListNode(ConcertInstrument data, CListNode* next);

//chekc if a MPIList is empty
bool isEmptyCList(CIList* lst);

//create an empty list
void makeEmptyCList(CIList* lst);

// add an excisting node to the end of a MPIList
void insertNodeToEndCList(CIList* lst, CListNode* tail);

// create a node and add it to the end of a MPIList
void insertDataToEndCList(CIList* lst, ConcertInstrument data);

// print a MPIList
void printCList(CIList* lst);

//free a CIList
void freeCIList(CIList* lst);

// check the num of musicians in single concert
int NumOfMusician(CIList* lst);


#endif // !CILIST_H
