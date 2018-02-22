/*
 * func_secret_share.h
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */

#ifndef FUNC_SECRET_SHARE_H_
#define FUNC_SECRET_SHARE_H_

#include <secretsharer.h>
#include <types.h>

/**
	 * compartilha um segredo com limiares e tamanhos especificados
	 * @param n nÃºmero mÃ­nimo de membro para remontar o segredo
	 * @param m nÃºmero total de partes a ser dividida o segredo
	 * @param data segredo que se deseja compartilhar
	 * @param ndata tamanho do segredo a ser compartilhado
	 * @return um estrutura contendo todas as partes
	 * @return NULL em caso de falha
	 */
secrets_st * secret_share(int n, int m, unsigned char *data, int ndata);

	/**
	 * juntas as partes de um segredo, remontando o segredo
	 * @param secrets estrutura com todos as partes para recuperaÃ§Ã£o do segredo
	 * @param m nÃºmero total de partes existentes
	 * @param n nÃºmero mÃ­nimo de membro para remontar o segredo
	 * @return estrutura contendo o segredo
	 * @return NULL em caso de falha
	 */
byteArray_st * join_secret(secrets_st *secrets, int m, int n);


#endif /* FUNC_SECRET_SHARE_H_ */
