/*
 * func_aux_file.h
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */



#ifndef FUNC_AUX_FILE_H_
#define FUNC_AUX_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int open_file(char *file_path, unsigned char **file_data, int *file_data_size);

int write_file(char *file_path, unsigned char *file_data, int file_data_size);

#endif /* FUNC_AUX_FILE_H_ */
