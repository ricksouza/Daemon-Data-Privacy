/*
 * common.h
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#include <pthread.h>

#ifndef COMMON_H_
#define COMMON_H_


#define THREAD_CC
#define THREAD_TYPE   pthread_t
#define THREAD_CREATE(tid, entry, arg)   pthread_create(&(tid),  NULL, (entry), (arg))

#define MUTEX_TYPE pthread_mutex_t
#define MUTEX_SETUP(x) pthread_mutex_init(&(x), NULL)
#define MUTEX_CLEANUP(x) pthread_mutex_destroy(&(x))
#define MUTEX_LOCK(x) pthread_mutex_lock(&(x))
#define MUTEX_UNLOCK(x) pthread_mutex_unlock(&(x))
#define THREAD_ID pthread_self( )

#define PORT "5000"
#define SERVER "server"
#define CLIENTE "client"

#define int_error(msg) handle_error(__FILE__, __LINE__, msg)

void handle_error (const char *file, int lineno, const char *msg);

/* This array will store all of the mutexes available to OpenSSL. */
static MUTEX_TYPE *mutex_buf = NULL ;

void init_OpenSSL(void);

int THREAD_setup(void);
int THREAD_cleanup(void);

static unsigned long id_function(void);
static void locking_function(int mode, int n, const char * file, int line);

#endif /* COMMON_H_ */
