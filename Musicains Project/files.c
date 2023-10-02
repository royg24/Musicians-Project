#include "files.h"


void openFilesCheck(FILE* f)
{
	/*
	check if the file open succeed
	*/
	if (f == NULL)
	{
		printf("Open of file was failed!\n");
		exit(1);
	}
}

long int NumOfLinesInFile(char* fileName)
{
	/*
	This function gets a name of a text file and counts its lines
	*/
	FILE* f = fopen(fileName, "r");
	openFilesCheck(f);
	char line[MAX_LINE_LEN];

	long int counter = 0;
	while (fgets(line, MAX_LINE_LEN, f) != NULL)
	{
		counter++;
	}

	fclose(f);
	return counter;
}


