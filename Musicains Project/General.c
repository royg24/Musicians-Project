#include "General.h"

void checkMalloc(void* ads)
{
	/*
	This function checks allocation for a given adress
	*/
	if (ads == NULL)
	{
		printf("Error with memory allocation!\n");
		exit(1);
	}
}

Concert* getSingleConcert(InstrumentTree tr)
{
	/*
	This function gets a single concert data from the user and returns it in a 
	Concert variable
	*/

	Concert* res;
	char hour[SIZE_OF_HOUR];
	res = (Concert*)malloc(sizeof(Concert)); //need to free
	checkMalloc(res);
	res->name = getName();
	if (res->name == NULL)
		return NULL;
	scanf("%d", &(res->date_of_concert.day));
	scanf("%d", &(res->date_of_concert.month));
	scanf("%d", &(res->date_of_concert.year));
	scanf("%s", hour);
	res->date_of_concert.hour = getHour(hour);
	res->instruments = getInstrumentList(tr);

	return res;

}

CIList getInstrumentList(InstrumentTree tr)
{
	/*
	This function creates the list to store the data about the instruments
	needed for a single concert
	*/
	char inst[MAX_LINE_LEN];
	char ch;
	bool endOfinput = false;
	CIList res;
	ConcertInstrument data;
	makeEmptyCList(&res);

	while (endOfinput == false)
	{
		scanf("%c", &ch);
		if (ch == ENTER)
			endOfinput = true;
		else
		{
			scanf("%s", inst);
			data.inst = findInsId(tr, inst);
			scanf("%d", &data.num);
			scanf(" %c", &data.importance);
			if (data.inst != NOT_FOUND)
				insertDataToEndCList(&res, data);

		}
	}
	return res;
}

char* getName()
{
	/*
	This function gets from the user the name of the concert with an 
	unknwon size
	*/
	char ch;
	char* temp;
	int logSize = ZERO, phySize = INIT_SIZE;
	char* name = (char*)malloc(sizeof(char) * INIT_SIZE); //need to free
	checkMalloc(name);
	scanf("%c", &ch);
	if (ch == ENTER)
		return NULL;
	name[logSize] = ch;
	logSize++;
	while (ch != SPACE)
	{
		if (phySize == logSize)
		{
			phySize *= 2;
			temp = (char*)realloc(name, sizeof(char) * phySize);
			if (temp != NULL)
				name = temp;
			else
				exit(1);
		}
		scanf("%c", &ch);
		name[logSize] = ch;
		logSize++;
	}
	if (phySize > logSize)
	{
		temp = (char*)realloc(name, sizeof(char) * logSize);
		if (temp != NULL)
			name = temp;
		else
			exit(1);
	}
	name[logSize - 1] = END_OF_STR;
	return name;
}

float getHour(char* str)
{
	/*
	This function converts the display of hour we get from the user to a float number
	(the minutes become a fracture)
	*/
	float hour = ZERO;
	float minute = ZERO;

	sscanf(str, "%f", &hour);
	sscanf(str + PLACE_OF_MIN, "%f", &minute);

	minute = minute / CONVERT;
	return minute + hour;

}

ChosenMusicians** arrangeConcert(CIList* lst, Musician*** MusicianCollection, int* sizes, int size, int* resSize)
{
	/*
	This function gets the data about the musicians and the concert and arranage a concert
	according to its data
	*/
	int numOfMusician;
	short int i;
	ChosenMusicians** res;
	CListNode* curr = lst->head;
	int chosenIndex = ZERO;
	BOOL pick;

	numOfMusician = NumOfMusician(lst);
	res = (ChosenMusicians**)malloc(sizeof(ChosenMusicians*) * numOfMusician); //need to free
	checkMalloc(res);
	while (curr != NULL)
	{
		i = curr->data.inst;
		updateCurrInsId(MusicianCollection[i],i, sizes[i]);
		sortArray(MusicianCollection[i], sizes[i], curr->data.importance);
		pick = pickMusicians(MusicianCollection[i], sizes[i], res, chosenIndex, curr);
		if (pick == TRUE)
			chosenIndex = chosenIndex + curr->data.num;
		else
			return NULL;
		curr = curr->next;
	}
	*resSize = numOfMusician;
	return res;
}


BOOL pickMusicians(Musician** arr, int size, ChosenMusicians** res, int index, CListNode* inst)
{
	/*
	This function gets the data about the musicians, a certain instrument and the number of musicnas
	with that instrument needed. it picks musicians to that concert if it's possible
	*/
	int i, counter = ZERO; //counter is for musician for the instrument that arr represents
						  // index is for the index in res to put the musician
	for (i = 0; i < size && counter < inst->data.num; i++) 
	{
		if (arr[i]->chosen == FALSE)
		{
			res[index] = (ChosenMusicians*)malloc(sizeof(ChosenMusicians)); //need to free
			checkMalloc(res[index]);
			res[index]->name = arr[i]->name;
			res[index]->insID = inst->data.inst;
			res[index]->price = findPrice(&arr[i]->instruments, inst->data.inst);
			res[index]->size = arr[i]->size;
			index++;
			counter++;
			arr[i]->chosen = TRUE;
		}
	}

	if (counter == inst->data.num)
		return TRUE;
	else
		return FALSE;
}

void createConcert(Musician** MusicianGroup,int groupSize, Musician*** MusicianCollection, int* sizes, int size, InstrumentTree tr)
{
	/*
	This function creates concert according to the data given by the user.
	It prints its name, date, time, musicians, the instrument they play,
	price of each and the total price or an announcment if it can't happen.
	*/
	int bandSize;
	ChosenMusicians** band;
	Concert* con;
	BOOL endOfInput = FALSE;

	while (endOfInput == FALSE)
	{
		con = getSingleConcert(tr);
		printf("%c", ENTER);
		if (con == NULL)
			endOfInput = TRUE;
		else
		{
			band = arrangeConcert(&con->instruments, MusicianCollection, sizes, size, &bandSize);
			if (band == NULL)
				printf("Could not find Musicians for the concert %s", con->name);
			else
			{
				printf("%s ", con->name);
				printf("%d %d %d ", con->date_of_concert.day, con->date_of_concert.month, con->date_of_concert.year);
				printHour(con->date_of_concert.hour);
				printBand(band, bandSize, tr);
			}
			printf("%c%c", ENTER, ENTER);
			updateChosen(MusicianGroup, groupSize);
		}
		free(con);
	}


}

void printBand(ChosenMusicians** arr, int size, InstrumentTree tr)
{
	/*
	This function prints all the musicians for the concert, their instruments and the 
	price of each
	*/
	int i;
	char* insName;
	float totalPrice = ZERO_FLOAT;

	for (i = 0; i < size; i++)
	{
		printMusician(arr[i]->name, arr[i]->size);
		printf("- ");
		insName = insIdToName(arr[i]->insID, tr);
		printf("%s ", insName);
		printf("(%.0f), ", arr[i]->price);
		totalPrice = totalPrice + arr[i]->price;
		free(arr[i]);
	}
	printf(". Total cost: %.0f.", totalPrice);
	free(arr);
}

void printHour(float hour)
{
	/*
	This function gets a float represents hour and prints it in the correct format
	*/
	int num;
	int min = ZERO;
	num = (int)hour;
	hour = (hour - num) * CONVERT;
	min += hour;
	printf("%d:%d: ", num, min);

}

void printMusician(char** arr, int size)
{
	/*
	This function prints all the names of one musician
	*/
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%s ",arr[i]);
	}
}

void updateChosen(Musician** MusicianGroup, int groupSize)
{
	/*
	make all the musicians not-chosen after a concert
	*/
	int i;

	for (i = 0; i < groupSize; i++)
	{
		MusicianGroup[i]->chosen = FALSE;
	}
}