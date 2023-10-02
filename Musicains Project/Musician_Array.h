#ifndef MUSICIAN_ARRAY_H
#define MUSICIAN_ARRAY_H

#include "General.h"

//creates a musician's array with given size and data from file
Musician** createArrOfMusicians(char* fileName, int size,struct InstrumentTree* tr);

//creates an element for the MusiciansGroup array with given data
Musician* getDataFromLine(char* line, struct InstrumentTree* tr);

//counts the number of names of a musician
int getSizeOfNamesArr(char* line);

//prints arr of musicians
void printMusicianArr(Musician** arr, int size);

//enters values of musician to a node from the array
struct musician* getValuesOfMusician(Musician* node, char* line,struct tree* tr );

//builds the array of instrument-musician collection
Musician*** createMusicianCollectionArray(Musician** MusicianGroup, int GroupSize, int newSize, int** Psizes);

//fill the MusicianCollection array
void fillMusicianCollection(Musician** MusicianGroup, int GroupSize, int* sizes, Musician*** MusicianCollection, int newSize);

//sort the musicians array according to the importance
void sortArray(Musician** arr, int size, char importance);

//the fun free the musician group array
void freeMusicianGroup(Musician** arr, int size);

//the func free the musician collection array
void freeMusicianCollection(Musician*** arr, int size, int* sizes);

//compares two musicians according to their price
int musCompExp(void* M1, void* M2); //expensive
int musCompChp(void* M1, void* M2); //cheap

//update the insId in the Musician
void updateCurrInsId(Musician** arr, short int id, int size);


#endif // !MUSICIAN_ARRAY_H

