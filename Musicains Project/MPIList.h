#ifndef MPILIST_H
#define MPILIST_H

typedef int BOOL;

typedef struct {
	unsigned short insID; // ID of the instrument
	float price; //the price of the instrument
}MusicianPriceInstrument;

typedef struct mlistNode {
	MusicianPriceInstrument data; // data about price of an istrument
	struct mlistNode* next;
}MListNode;

typedef struct {
	MListNode* head;
	MListNode* tail;
}MPIList;

typedef struct musician{
	char** name; // The Musician's Name
	MPIList instruments; // List of the Musician's instrument he can play
	int size; //number of names he has
	BOOL chosen; //if he plays in that concert
	short int CurrinsId;
}Musician;

#include "General.h"


//create new ListNode with data given
MListNode* createNewMListNode(MusicianPriceInstrument data, MListNode* next);

//chekc if a MPIList is empty
bool isEmptyMList(MPIList* lst);

//create an empty list
void makeEmptyMList(MPIList* lst);

// add an excisting node to the end of a MPIList
void insertNodeToEndMList(MPIList* lst, MListNode* tail);

// create a node and add it to the end of a MPIList
void insertDataToEndMList(MPIList* lst, MusicianPriceInstrument data);

// print a MPIList
void printMList(MPIList* lst);

//free the list
void freeMPIList(MPIList* lst);

//search the price of specific instrument
float findPrice(MPIList* lst, short int insID);


#endif // !MPILIST_H
