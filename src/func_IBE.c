/*
 * func_IBE.c
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */

#include "func_IBE.h"

int IBE_Setup(IBE_PARAMS *ibe_params){

	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;

	pFile = fopen("pairing.param", "r");
	if (pFile == NULL) {
		fputs("File error", stderr);
		exit(1);
	}

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	buffer = (char*) malloc(sizeof(char) * lSize);
	if (buffer == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, pFile);
	fclose(pFile);

	if (!result)
		pbc_die("input error");

	pairing_init_set_buf(ibe_params->pairing, buffer, result);


	/***
	initialization of G1 elements
	***/
	element_init_G1(ibe_params->P, ibe_params->pairing);
	element_init_G1(ibe_params->Ppub, ibe_params->pairing);

	/***
	initialization of Zr elements
	***/
	element_init_Zr(ibe_params->s, ibe_params->pairing);

	//element_random(ibe_params->P);
//	char *P;
//	int size1;
//	open_file("g", &P, &size1);
//
//	element_set_str(ibe_params->P, P, 10);



  	//element_random(ibe_params->s);


  	//element_mul_zn(ibe_params->Ppub, ibe_params->P, ibe_params->s);
  	char *Ppub;
  	int size2;
  	open_file("pub_key", &Ppub, &size2);

  	element_set_str(ibe_params->Ppub, Ppub, 10);

	return 0;
}

int IBE_Extract_Private_Key(IBE_PARAMS *ibe_params, char *id, IBE_PRIVATE_KEY *private_key){

	unsigned char hash[SHA_DIGEST_LENGTH]={0};

	element_init_G1(ibe_params->Qid, ibe_params->pairing);

	if (SHA1((unsigned char *)id, SHA_DIGEST_LENGTH, (unsigned char *) hash) == NULL) {
		//ERR_error_string(ERR_get_error(), stderr);
		//printf("%s\n", stderr);
	}

	element_init_G1(private_key->Did, ibe_params->pairing);

	//char *u_qid;
	//int size1;
	//open_file("public_key", &u_qid, &size1);
	//element_set_str(private_key->Qid, u_qid, 10);
	element_from_hash(ibe_params->Qid, hash, SHA_DIGEST_LENGTH);
	//free(u_qid);
	//comentando momentaneamente element_mul_zn(private_key->Did, ibe_params->Qid, ibe_params->s);

	/**
	 * Codigo para carregar a chave privada de um arquivo.
	 */
	char *u_priv_key;
	int size;
	open_file("private_key", &u_priv_key, &size);

	element_set_str(private_key->Did, u_priv_key, 10);
	free(u_priv_key);

	//element_init_GT(ibe_params->gid, ibe_params->pairing);
	//element_pairing(ibe_params->gid, ibe_params->Qid, ibe_params->Ppub);

	return 0;
}

int IBE_Encrypt(IBE_PARAMS *ibe_params, unsigned char *data, int data_len, IBE_ENCRYPTED_DATA *encrypted){

	//element_t r, gid;
	unsigned char *gs = NULL;
	unsigned char hash_gs[SHA_DIGEST_LENGTH]={0};

	element_t r, gid;

	/***
	initialization of G1 elements
	***/
	element_init_G1(encrypted->U, ibe_params->pairing);

	/***
	initialization of Zr elements
	***/
	element_init_Zr(r, ibe_params->pairing);

	/***
	initialization of GT elements
	***/
	element_init_GT(gid, ibe_params->pairing);

	element_random(r);

	char *c_u;
	int size;
	open_file("U", &c_u, &size);

	element_set_str(encrypted->U, c_u, 10);

	//element_mul_zn(encrypted->U, ibe_params->P, r);
	element_pairing(gid, ibe_params->Qid, ibe_params->Ppub);
	element_pow_zn(gid, gid, r);

	gs = malloc(element_length_in_bytes(gid));
	element_to_bytes(gs, gid);

	if(SHA1(gs , 20, hash_gs)==NULL)
	{
		//ERR_error_string(ERR_get_error(), stderr);
		//printf("%s\n",stderr);
	}

	encrypted->C = (unsigned char *)calloc( data_len, sizeof(unsigned char));

	int i;
	for(i = 0; i < data_len ; i++)
	{
		encrypted->C[i] = data[i]^hash_gs[i % data_len];
	}
	free(gs);

	encrypted->size = data_len;

	return 0;
}

int IBE_Decrypt(IBE_PARAMS *ibe_params, IBE_ENCRYPTED_DATA encrypted, IBE_PRIVATE_KEY private_key, unsigned char **decrypted_data){

	element_t xt;
	unsigned char *gs = NULL;
	unsigned char hash_gs[SHA_DIGEST_LENGTH]={0};

	/***
	initialization of GT elements
	***/
	element_init_GT(xt, ibe_params->pairing);

	element_pairing(xt, private_key.Did, encrypted.U);

	gs = malloc(element_length_in_bytes(xt));

	element_to_bytes(gs,xt);

	if(SHA1(gs , 20, (unsigned char *)hash_gs)==NULL)
	{
		//ERR_error_string(ERR_get_error(),stderr);
		//printf("%s\n",stderr);
	}

	*decrypted_data = (unsigned char *)calloc( encrypted.size, sizeof(unsigned char));

	int i;
	for(i = 0; i < encrypted.size; i++)
	{
		(*decrypted_data)[i] = encrypted.C[i]^ hash_gs[i % encrypted.size];
	}


	return 0;
}

int recompor_ibe_encrypted_data(IBE_PARAMS *ibe_params, unsigned char *C, int C_len, unsigned char *U, IBE_ENCRYPTED_DATA *encrypted){

	/***
	initialization of G1 elements
	***/
	element_init_G1(encrypted->U, ibe_params->pairing);

	element_from_bytes(encrypted->U, U);

	encrypted->C = (unsigned char *)calloc( C_len, sizeof(unsigned char));
	memcpy(encrypted->C, C, C_len);

	encrypted->size = C_len;

	return 0;
}
