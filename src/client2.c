/*
 * client2.c
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */


#include "common.h"

int management_enter_datas(char *argv[], int argc){

//	if (!strcmp(argv[0], "send")){
//		argv++; argc--;
//		if (!(management_send(argc, argv))){
//				return 0;
//		}
//	}else if (!strcmp(argv[0], "retrieve")){
//		argv++; argc--;
//		if (!(management_retrieve(argc, argv))){
//				return 0;
//		}
//	}

	return 0;
}

void do_client_loop(){

	int err, nwritten, enter_number;
	char buf[80];
	char *buffer_parts[150];

	for(;;){
		if(!fgets(buf, sizeof(buf), stdin))
			break;
		for(nwritten = 0; nwritten < sizeof(buf); nwritten += err){
			if (!strcmp(buf, "quit") || !strcmp(buf, "exit")){
				//free(buf);
				break;
			}

			enter_number = umount_string_by_space(buf, buffer_parts);
		}
	}
}

int main4(int argc, char **argv){

	//BIO *conn;

	init_OpenSSL();

	//conn = BIO_new_connect(SERVER ":" PORT);

	//if(!conn)
	//	int_error("Error creating connection BIO");

	//if(BIO_do_connect(conn) <= 0)
	//	int_error("Error connecting to remote machine");

	//fprintf(stderr, "Connection opened \n");

	do_client_loop();

	//frptinf(stderr, "Connection close \n");

	//BIO_free(conn);

	return 0;

}
