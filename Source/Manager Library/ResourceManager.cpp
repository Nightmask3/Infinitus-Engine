#include <fstream>
#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	BINARY_MAP_WIDTH = 0;
	BINARY_MAP_HEIGHT = 0;
}


ResourceManager::~ResourceManager()
{
}

int ResourceManager::ImportMapDataFromFile(char *pFileName)
{
	FILE *file = NULL;
	char * file_contents;		 // Holds the contents of the file
	char *temp = 0;				 // Holds the character pointer to each line in the file
	char *token = "\n";			 // Holds the token to parse the file input by
	char *t;
	long file_size;				 // Holds the file size
	int count = 0;				 // Used to count line numbers in the file
	int i = 0, j = 0;			 // Loop control variables

	file = fopen(pFileName, "rb");// Opens the file using the file name
	if (file == NULL)			 // If file fails to open, because file "Filename" does not exist
		return 0;

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);	 // Used to get the file size into file_size
	rewind(file);

	file_contents = static_cast<char *>(malloc(file_size * sizeof(char)));	  // Allocating space to the character pointer
	file_contents[file_size] = 0;						  // Initializing to 0 to get rid of junk characters
	fread(file_contents, sizeof(char), file_size, file); // Reads the entire file into file_contents

	temp = strtok(file_contents, token);				  // Reads the first line of the file
	for (t = temp; *t; t++)
	{
		if (isdigit(*t))								  /* if *t is a digit */
		{
			BINARY_MAP_WIDTH *= 10;
			BINARY_MAP_WIDTH += (int)(*t - '0');
		}
	}

	temp = strtok(NULL, token);							  // Reads the second line of the file

	for (t = temp; *t; t++)
	{
		if (isdigit(*t))								  /* if *t is a digit */
		{
			BINARY_MAP_HEIGHT *= 10;
			BINARY_MAP_HEIGHT += (int)(*t - '0');
		}
	}

	MapData = (int **)malloc(BINARY_MAP_HEIGHT * sizeof(int *));
	for (i = 0; i < BINARY_MAP_HEIGHT; i++)
		MapData[i] = (int *)malloc(BINARY_MAP_WIDTH * sizeof(int));

	temp = strtok(NULL, token);

	for (j = BINARY_MAP_HEIGHT - 1; j >= 0; j--)
	{
		for (i = 0; i < BINARY_MAP_WIDTH; i++)
		{
			MapData[i][j] = temp[i * 2] % 48;	// Skips the spaces and converts to integer
		}
		temp = strtok(NULL, token);
	}

	return 1;
}