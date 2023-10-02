#ifndef FILES_H
#define FILES_H

#include"General.h"


//check if file open succeed
void openFilesCheck(FILE* f);

// counts the number of lines in a file
long int NumOfLinesInFile(char* fileName);

#endif // !FILES_H
