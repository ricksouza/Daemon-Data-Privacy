/*
 * func_aux_file.c
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */


#include "func_aux_file.h"

int open_file( char *file_path, unsigned char **file_data, int *file_data_size){

	FILE * pFile;
	long lSize;
	size_t result;

	pFile = fopen(file_path, "rb");
	if (pFile == NULL) {
		fputs("File error", stderr);
		exit(1);
	}

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	*file_data = (unsigned char*) malloc(sizeof(unsigned char) * lSize);
	if (*file_data == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}

	// copy the file into the buffer:
	result = fread(*file_data, 1, lSize, pFile);
	fclose(pFile);

	*file_data_size = lSize;

	return 0;
}

int write_file(char *file_path, unsigned char *file_data, int file_data_size){

	FILE * pFile;

	pFile = fopen (file_path, "wb");
	fwrite (file_data , sizeof(unsigned char), (size_t)file_data_size, pFile);
	fclose (pFile);

	return 0;
}
