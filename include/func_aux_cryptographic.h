/*
 * func_aux_cryptographic.h
 *
 *  Created on: Aug 6, 2013
 *      Author: rick
 */

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#ifndef FUNC_AUX_CRYPTOGRAPHIC_H_
#define FUNC_AUX_CRYPTOGRAPHIC_H_

#define AES_128_CBC NID_aes_128_cbc
#define AES_256_CBC NID_aes_256_cbc
#define TRIPLE_DES_CBC NID_des_ede3_cbc

#define ENCRYPT 1001
#define DECRYPT 1002

struct manipulated_data{
	unsigned char *data;
	int data_size;
};


struct symmetric_params{
	unsigned char *key;
	unsigned char *iv;
	int algorithm;
};



#endif /* FUNC_AUX_CRYPTOGRAPHIC_H_ */
