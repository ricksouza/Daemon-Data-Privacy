/*
 * func_cryptographic.c
 *
 *  Created on: Aug 6, 2013
 *      Author: rick
 */

#include "func_cryptographic.h"

int init_cryptographic_openssl(){

	int ret = 0;

	ERR_load_crypto_strings();
	SSL_load_error_strings();
	OpenSSL_add_all_ciphers();
	OPENSSL_add_all_algorithms_conf();

	return ret;

}

int gen_rand(int num_bytes, unsigned char **data){

	*data = (unsigned char *) calloc(num_bytes + 1, sizeof(unsigned char));
	RAND_bytes(*data, num_bytes);

	return 0;
}

void sym_encrypt(unsigned char *open_data, int open_data_size, unsigned char **encrypted_data, int *encrypted_data_size, unsigned char *key, unsigned char *iv, int NID){

	EVP_CIPHER_CTX ctx;
	const EVP_CIPHER *cipher;

	int data_alloc;
	int final_encrypted_block_size = 0;

	cipher = EVP_get_cipherbynid(NID);

	data_alloc = open_data_size + (16 - (open_data_size % (cipher->block_size)));
	*encrypted_data = (unsigned char *)calloc(data_alloc, sizeof(unsigned char));

	EVP_CIPHER_CTX_init(&ctx);
	EVP_CipherInit_ex(&ctx, cipher, NULL, key, iv, 1);
	EVP_CipherUpdate(&ctx, *encrypted_data, encrypted_data_size, open_data, open_data_size);
	EVP_CipherFinal_ex(&ctx, *encrypted_data + *encrypted_data_size, &final_encrypted_block_size);

	*encrypted_data_size = *encrypted_data_size + final_encrypted_block_size;

}

void sym_decrypt(unsigned char *encrypted_data, int encrypted_data_size, unsigned char **decrypted_data, int *decrypted_data_size, unsigned char *key, unsigned char *iv, int NID){

	EVP_CIPHER_CTX ctx;
	const EVP_CIPHER *cipher;

	int final_decrypted_block_size = 0;
	int data_alloc;

	cipher = EVP_get_cipherbynid(NID);

	data_alloc = encrypted_data_size;
	*decrypted_data = (unsigned char *)calloc(data_alloc - 5, sizeof(unsigned char));

	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit_ex(&ctx, cipher, NULL, key, iv);
	EVP_DecryptUpdate(&ctx, *decrypted_data, decrypted_data_size, encrypted_data, encrypted_data_size);
	EVP_DecryptFinal_ex(&ctx, *decrypted_data + *decrypted_data_size, &final_decrypted_block_size);

	int test1 = *decrypted_data_size;
	int test2 = decrypted_data_size;

	*decrypted_data_size = *decrypted_data_size + final_decrypted_block_size;

}
