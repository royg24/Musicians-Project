#ifndef GENERAL_H
#define GENERAL_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#define MAX_LINE_LEN 151
#define TRUE 1
#define FALSE 0
#define NOT_FOUND -1
#define ZERO 0
#define ENTER '\n'
#define SIZE_OF_HOUR 6
#define TWO_POINTS ":"
#define CONVERT 60
#define PLACE_OF_MIN 3
#define INIT_SIZE 1
#define SPACE ' '
#define END_OF_STR '\0'
#define IMP '1'
#define NOT_IMP '0'
#define ZERO_FLOAT 0.0
#define POS 1
#define NEG 0


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "CIList.h"
#include "Trees.h"

typedef struct
{
	int day, month, year;
	float hour;
}Date;

typedef struct
{
	Date date_of_concert; //date of concert
	char* name; // name of concert
	CIList instruments; // list of instruments with amount, id and importance
}Concert;

typedef struct {
	char** name; //the names of the musicinan
	int size;  //number of names
	short int insID; //id of instrument he plays in the concert
	float price; //price of the id
}ChosenMusicians;

#include "MPIList.h"
#include "Musician_Array.h"
#include"files.h"

//check allocation of any adress
void checkMalloc(void* ads);


//creates element for a single concert
Concert* getSingleConcert(InstrumentTree tr);

//get the hour of the concert
float getHour(char* str);

//get the concert's name from the user
char* getName();

//get instrument to list
CIList getInstrumentList(InstrumentTree tr);

//arraange a concert
ChosenMusicians** arrangeConcert(CIList* lst, Musician*** MusicianCollection, int* sizes, int size, int* resSize);

//pick musicians for a certain instrument
BOOL pickMusicians(Musician** arr, int size, ChosenMusicians** res, int index, CListNode* inst);

// create all concerts and print
void createConcert( Musician** MusicianGroup, int groupSize, Musician*** MusicianCollection, int* sizes, int size, InstrumentTree tr);

//change float to hour and prints it
void printHour(float hour);

// print all the musician and inst
void printBand(ChosenMusicians** arr, int size, InstrumentTree tr);

//print name arr
void printMusician(char** arr, int size);

//update the chosen muscian
void updateChosen(Musician** MusicianGroup, int groupSize);

#endif // !GENERAL_H
