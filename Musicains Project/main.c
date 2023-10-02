#include "General.h"

//const char seps[] = " ,.;:?!-\t'()[]{}<>~_"

void main(int argc, char* argv[])
{
	/*
	Project by:
	Roy Goldhar, id: 208610402
	Noa Berdah, id: 206860066
	*/
	int numOfInst;
	int* sizes;
	int sizeOfConcert;
	InstrumentTree tr = getDataFromFileToTree(argv[1], &numOfInst); // part 1
	int size = NumOfLinesInFile(argv[2]);
	Musician** MusicianGroup = createArrOfMusicians(argv[2], size,&tr); //part 3
	Musician*** MusicianCollection = createMusicianCollectionArray(MusicianGroup, size, numOfInst, &sizes); //part 4

	createConcert( MusicianGroup, size, MusicianCollection, sizes, numOfInst, tr); //part 5
	freeTree(&tr);
	freeMusicianGroup(MusicianGroup, size);
	freeMusicianCollection(MusicianCollection, numOfInst, sizes);

}

