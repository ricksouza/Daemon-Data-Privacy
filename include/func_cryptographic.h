/*
 * func_cryptographic.c
 *
 *  Created on: Aug 6, 2013
 *      Author: rick
 */

#include "func_aux_cryptographic.h"

#ifndef FUNC_CRYPTOGRAPHIC_C_
#define FUNC_CRYPTOGRAPHIC_C_

/**
 * Inicia as variaveis necessarias para o funcionamento do openssl
 *
 */
int init_cryptographic_openssl();

int gen_rand(int num_bytes, unsigned char **data);

int gen_symmetric_key(int num_bytes, unsigned char **key);

int gen_iv(int num_bytes, unsigned char **iv);

int symmetric_function(struct manipulated_data data_in, struct symmetric_params params, struct manipulated_data **data_out, int function);

int symmetric_encrypt(struct manipulated_data open_data, struct symmetric_params params, unsigned char **encrypted_data, int *encrypted_size);
void sym_encrypt(unsigned char *open_data, int open_data_size, unsigned char **encrypted_data, int *encrypted_data_size, unsigned char *key, unsigned char *iv, int NID);

int symmetric_decrypt(struct manipulated_data encrypted_data, struct symmetric_params params, unsigned char **decrypted_data, int *decrypted_size);
void sym_decrypt(unsigned char *encrypted_data, int encrypted_data_size, unsigned char **decrypted_data, int *decrypted_data_size, unsigned char *key, unsigned char *iv, int NID);



#endif /* FUNC_CRYPTOGRAPHIC_C_ */
