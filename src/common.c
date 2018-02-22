/*
 * common.c
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */


#include "common.h"

static unsigned long id_function(void)
{
  return ((unsigned long)THREAD_ID);
}

static void locking_function(int mode, int n, const char * file, int line)
{
  if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(mutex_buf[n]);
  else
    MUTEX_UNLOCK(mutex_buf[n]);
}

int THREAD_setup(void)
{
  int i;
  mutex_buf = (MUTEX_TYPE *) malloc(CRYPTO_num_locks( ) * sizeof(MUTEX_TYPE));
  if(!mutex_buf)
    return 0;
  for (i = 0; i < CRYPTO_num_locks( ); i++)
    MUTEX_SETUP(mutex_buf[i]);
  CRYPTO_set_id_callback(id_function);
  CRYPTO_set_locking_callback(locking_function);
  return 1;
}

int THREAD_cleanup(void)
{
  int i;
  if (!mutex_buf)
    return 0;
  CRYPTO_set_id_callback(NULL);
  CRYPTO_set_locking_callback(NULL);
  for (i = 0; i < CRYPTO_num_locks( ); i++)
    MUTEX_CLEANUP(mutex_buf[i]);
  free(mutex_buf);
  mutex_buf = NULL;
  return 1;
}

void handle_error(const char *file, int lineno, const char *msg){

	fprintf(stderr, "** %s:%i %s\n", file, lineno, msg);
	ERR_print_errors_fp(stderr);

	exit(-1);
}

void init_OpenSSL(void){
	if(!THREAD_setup() || !SSL_library_init()){
		fprintf(stderr, "** OpenSSL initialization failed! \n");

		exit(-1);
	}

	SSL_load_error_strings();
}

int find_next(const char *buffer, int start, char obj){
	int i, rc = 0;
	for (i = start; i < strlen(buffer); i++) {
		if (buffer[i] == obj) {
			rc = i + 1;
			break;
		}
	}
	return rc;
}

int umount_string_by_space(const char *in, char *out[]){
	int start = 0;
	int pos = 0;
	int members = 0;
	while (in[start] == ' ') {
		start++;
	}
	while (start < strlen(in)) {
		if (in[start] == '"') {
			while (in[start + 1] == ' ') {
				start++;
			}
			pos = find_next(in, start + 1, '"');
			if (pos == 0) {
				pos = strlen(in) + 1;
			}
			if (start + 2 == pos) {
				start = pos + 1;
			} else {
				out[members] = (char *) calloc(pos - start + 1, sizeof(char));
				strncpy(out[members], &(in[start + 1]), pos - start - 2);
				members++;
				start = pos;
			}
		} else {
			pos = find_next(in, start, ' ');
			if (pos == 0) {
				pos = strlen(in) + 1;
			}
			out[members] = (char *) calloc(pos - start + 1, sizeof(char));
			strncpy(out[members], &(in[start]), pos - start - 1);
			members++;
			start = pos;
		}
	}
	return members;
}
