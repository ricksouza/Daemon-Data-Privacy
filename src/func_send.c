/*
 * func_send.c
 *
 *  Created on: Aug 7, 2013
 *      Author: rick
 */


int management_send(int argc, char *argv[]) {


	if (!strcmp(argv[0], "encrypted")) {

		if (!func_send_encrypted(argc, argv))
			return 0;
	} else if (!strcmp(argv[0], "open")) {

		if (!func_send_open(argc, argv))
			return 0;
	}

	return 1;
}

int func_send_encrypted(int argc, char **argv){



	return 1;
}

int func_send_open(int argc, char **argv){



	return 1;
}
