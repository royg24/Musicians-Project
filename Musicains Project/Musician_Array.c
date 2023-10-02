#include "Musician_Array.h"

const char seps[] = " ,.;:?!-\t'()[]{}<>~_";

Musician** createArrOfMusicians(char* fileName, int size, InstrumentTree* tr)
{
	/*
	This function gets a name of file of musicians and their amount.
	It creates an array that contain all the data from the file
	*/
	char line[MAX_LINE_LEN];
	int i;
	FILE* f;
	Musician** MusiciansGroup = (Musician**)malloc(size * sizeof(Musician*)); //need to free
	checkMalloc(MusiciansGroup);
	f = fopen(fileName, "r");
	openFilesCheck(f);

	for (i = 0; i < size; i++)
	{
		fgets(line, MAX_LINE_LEN, f);
		MusiciansGroup[i] = getDataFromLine(line, tr);
	}
	fclose(f);
	return MusiciansGroup;
}

Musician* getDataFromLine(char* line, InstrumentTree* tr)
{
	/*
	This function gets a string of data, creates a Musician node and returns it
	*/
	char lineCopy[MAX_LINE_LEN];
	Musician* res = (Musician*)malloc(sizeof(Musician)); //need to free
	checkMalloc(res);
	strcpy(lineCopy, line);
	res->size = getSizeOfNamesArr(lineCopy);
	res->name = (char**)malloc(sizeof(char*) * res->size); //need to free
	checkMalloc(res->name);
	res = getValuesOfMusician(res, line, tr);
	return res;	
}

int getSizeOfNamesArr(char* line)
{
	/*
	This function gets data about a musician and counts how many
	names he has
	*/
	char* token;
	int temp = ZERO;
	int size = 1, endOfInput = ZERO;
	token = strtok(line, seps);

	while (endOfInput == ZERO)
	{
		token = strtok(NULL, seps);
		if (sscanf(token, "%d", &temp) == ZERO)
		{
			size++;
		}
		else
		{
			endOfInput = TRUE;
		}
	}

	return size - 1;
}

void printMusicianArr(Musician** arr, int size)
{
	/*
	This function prints arr of musicians
	*/
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < arr[i]->size; j++)
		{
			printf("%s ", arr[i]->name[j]);
		}
		printf("\n");
		printMList(&arr[i]->instruments);
		printf("\n");
	}
}

struct musician* getValuesOfMusician(Musician* node, char* line, struct tree* tr)
{
	/*
	This function gets data about musician and enters it
	in the proper place in the array
	*/
	char* token;
	int i = 0;
	bool endOfInput = false;
	node->chosen = FALSE;
	makeEmptyMList(&node->instruments);
	MListNode* newNode;
	MusicianPriceInstrument data;
	token = strtok(line, seps);
	node->name[i] = strdup(token); // need to free

	for (i = 1; i < node->size; i++)
	{
		token = strtok(NULL, seps);
		node->name[i] = strdup(token);
	}
	while (endOfInput == false)
	{
		token = strtok(NULL, seps);
		if (token == NULL || token[0] == ENTER)
			endOfInput = true;
		else
		{
			data.insID = findInsId(*tr, token);
			token = strtok(NULL, seps);
			sscanf(token, "%f", &data.price);
			insertDataToEndMList(&node->instruments, data);
		}

	}
	return node;
}

Musician*** createMusicianCollectionArray(Musician** MusicianGroup, int GroupSize, int newSize, int** Psizes)
{
	/*
	This function creates the MusicianCollection array and an array of the size of it's each element
	*/
	int i;
	Musician*** MusicianCollection = (Musician***)malloc(sizeof(Musician**) * newSize); //need to free
	checkMalloc(MusicianCollection);
	int* sizes = (int*)calloc(newSize, sizeof(int)); //need to free
	checkMalloc(sizes);

	for (i = 0; i < newSize; i++)
	{
		MusicianCollection[i] = (Musician**)malloc(sizeof(Musician*) * GroupSize); //need to free
		checkMalloc(MusicianCollection[i]);
	}
	fillMusicianCollection(MusicianGroup, GroupSize, sizes, MusicianCollection, newSize);
	*Psizes = sizes;
	return MusicianCollection;
}

void fillMusicianCollection(Musician** MusicianGroup, int GroupSize, int* sizes, Musician*** MusicianCollection, int newSize)
{
	/*
	This function fills the MusicianCollection. each element is an array
	of pointers represents an instrumerns tha points for a musician who can play
	this instrument.
	*/
	int i;
	MListNode* curr;

	for (i = 0; i < GroupSize; i++)
	{
		curr = MusicianGroup[i]->instruments.head;
		while (curr != NULL)
		{
			MusicianCollection[curr->data.insID][sizes[curr->data.insID]] = MusicianGroup[i];
			sizes[curr->data.insID]++;
			curr = curr->next;
		}
	}
	for (i = 0; i < newSize; i++)
	{
		MusicianCollection[i] = realloc(MusicianCollection[i], sizes[i] * sizeof(Musician**));
	}
}

int musCompExp(void* M1, void* M2)
{
	/*
	This function gets 2 musicians and checks who takes more money
	for a specific instrument.
	*/
	Musician** a = (Musician**)M1;
	Musician** b = (Musician**)M2;

	float aPrice = findPrice(&a[ZERO]->instruments, a[ZERO]->CurrinsId);
	float bPrice = findPrice(&b[ZERO]->instruments, b[ZERO]->CurrinsId);

	if (aPrice < bPrice)
		return POS;
	else if (aPrice > bPrice)
		return NEG;
	else
		return ZERO;
}

int musCompChp(void* M1, void* M2)
{
	/*
	This function gets 2 musicians and checks who takes less money
	for a specific instrument.
	*/
	Musician** a = (Musician**)M1;
	Musician** b = (Musician**)M2;

	float aPrice = findPrice(&a[ZERO]->instruments, a[ZERO]->CurrinsId);
	float bPrice = findPrice(&b[ZERO]->instruments, b[ZERO]->CurrinsId);
	
	if (aPrice > bPrice)
		return POS;
	else if (aPrice < bPrice)
		return NEG;
	else
		return ZERO;
}

void sortArray(Musician** arr, int size, char importance)
{
	/*
	This function sorts the array according to the importance:
	1: expensive to cheap; 0: cheap to expensive
	*/
	if(importance == IMP)
	{
		qsort(arr, size, sizeof(Musician*), musCompExp);
	}
	else
	{
		qsort(arr, size, sizeof(Musician*), musCompChp);
	}
}

void freeMusicianGroup(Musician** arr, int size)
{
	/*
	This function frees the MusicianGroup array and its elements.
	*/
	int i,j;
	int nameSize = 0;
	for (i = 0; i < size; i++)
	{
		nameSize = arr[i]->size;
		for (j = 0; j < nameSize; j++)
		{
			free(arr[i]->name[j]);
		}
		free(arr[i]->name);
		freeMPIList(&arr[i]->instruments);
	}
	free(arr);
}

void freeMusicianCollection(Musician*** arr, int size, int* sizes)
{
	/*
	This function frees the MusicianCollection array and its elements.
	*/
	int i;

	for (i = 0; i < size; i++)
	{
		free(arr[i]);
	}
	free(arr);
	free(sizes);

}

void updateCurrInsId(Musician** arr, short int id, int size)
{
	/*
	this function update the currInsid field according to the instrument
	we need to find for the concert
	*/

	int i;

	for (i = 0; i < size; i++)
	{
		arr[i]->CurrinsId = id;
	}
}