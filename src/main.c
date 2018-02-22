/*
 * main.c
 *
 *  Created on: Aug 6, 2013
 *      Author: rick
 */

#include "func_cryptographic.h"
#include "func_aux_file.h"
#include "func_IBE.h"
#include "func_secret_share.h"

int main(){



	unsigned char *key1 = NULL;
	unsigned char *iv1 = NULL;

	unsigned char *encrypted;
	int encrypted_size;

	unsigned char *decrypted = NULL;
	int decrypted_size;

	printf("Iniciou \n");

	char *file_path1 = "confirmacao.pdf";
	char *file_path2 = "confirmacao3.pdf";

	struct manipulated_data open_data;

	init_cryptographic_openssl();

	gen_rand(16, &key1);
	gen_rand(16, &iv1);

	open_file(file_path1, &(open_data.data), &open_data.data_size);

	sym_encrypt(open_data.data, open_data.data_size, &encrypted, &encrypted_size, key1, iv1, AES_128_CBC);

	IBE_PARAMS ibe_params;
	IBE_PRIVATE_KEY private_key;
	IBE_ENCRYPTED_DATA enc_key;
	unsigned char *decrypted_key;

	IBE_Setup(&ibe_params);
	IBE_Extract_Private_Key(&ibe_params, "rick", &private_key);

	IBE_Encrypt(&ibe_params, key1, 16, &enc_key);

	unsigned char *U_uns;
	U_uns = (unsigned char *)calloc(element_length_in_bytes(enc_key.U), sizeof(unsigned char));

	element_to_bytes(U_uns, enc_key.U);

	secrets_st *C_partido = SECRETS_new(3);

	C_partido = secret_share(2, 3, enc_key.C, enc_key.size);

	secrets_st *C_recomposto = SECRETS_new(3);

	SECRETS_add_data(C_recomposto, C_partido->member[0]->data, C_partido->member[0]->length, 0);
	SECRETS_add_data(C_recomposto, C_partido->member[1]->data, C_partido->member[1]->length, 2);

	byteArray_st *secret;
	secret = join_secret(C_recomposto, 3, 2);

	IBE_ENCRYPTED_DATA enc_key2;

	//element_init_G1(enc_key2->U, ibe_params.pairing);

	unsigned char *U;
	U = malloc(element_length_in_bytes(enc_key.U));
	element_to_bytes(U, enc_key.U);

	recompor_ibe_encrypted_data(&ibe_params, secret->data, secret->length, U, &enc_key2);

	IBE_Decrypt(&ibe_params, enc_key2, private_key, &decrypted_key);

	sym_decrypt(encrypted, encrypted_size, &decrypted, &decrypted_size, decrypted_key, iv1, AES_128_CBC);

	write_file(file_path2, decrypted, decrypted_size);

	printf("Terminou \n");

	return 0;
}
