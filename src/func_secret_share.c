/*
 * func_secret_share.c
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */

#include "func_secret_share.h"

secrets_st * secret_share(int n, int m, unsigned char *data, int ndata){
	secrets_st *rc;
	byteArray_st *secret = BYTEARRAY_new();
	BYTEARRAY_set(secret, data, ndata, 0);
	rc = split(secret, m, n);
	BYTEARRAY_free(secret);
	return rc;
}

byteArray_st * join_secret(secrets_st *secrets, int m, int n){
	byteArray_st *rc;
	rc = join(secrets, m, n);
	return rc;
}
