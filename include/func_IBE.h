/*
 * func_IBE.h
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */

#ifndef FUNC_IBE_H_
#define FUNC_IBE_H_

#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include "common.h"
#include "func_aux_cryptographic.h"
#include "func_aux_file.h"



//Para o cliente
struct IBE_public_params{
	pairing_t pairing;
	element_t P;
	element_t Ppub;
	element_t Qid;
};

//Para os servidores
struct IBE_params{
	pairing_t pairing;
	element_t P;
	element_t Ppub;
	element_t Qid;
	element_t s;
};

struct IBE_encrypted_data{
	unsigned char *C;
	element_t U;
	int size;
};

struct IBE_private_key{
	element_t Did;
};

typedef struct IBE_public_params IBE_PUBLIC_PARAMS;
typedef struct IBE_params IBE_PARAMS;
typedef struct IBE_private_key IBE_PRIVATE_KEY;
typedef struct IBE_public_key IBE_PUBLIC_KEY;
typedef struct IBE_encrypted_data IBE_ENCRYPTED_DATA;

int IBE_Setup(IBE_PARAMS *ibe_params);
int IBE_Extract_Private_Key(IBE_PARAMS *ibe_params, char *id, IBE_PRIVATE_KEY *private_key);
int IBE_Encrypt(IBE_PARAMS *ibe_params, unsigned char *data, int data_len, IBE_ENCRYPTED_DATA *encrypted);
int IBE_Decrypt(IBE_PARAMS *ibe_params, IBE_ENCRYPTED_DATA encrypted, IBE_PRIVATE_KEY private_key, unsigned char **decrypted_data);

int recompor_ibe_encrypted_data(IBE_PARAMS *ibe_params, unsigned char *C, int C_len, unsigned char *U, IBE_ENCRYPTED_DATA *encrypted);


#endif /* FUNC_IBE_H_ */
