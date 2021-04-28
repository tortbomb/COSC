/**
 * @file     xsh_test.c
 * @provides xsh_test
 *
 */
/* Embedded XINU, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/**
 * Shell command (test) is testing hook.
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_test(int nargs, char *args[])
{
    //TODO: Test your O/S.
    printf("This is where you should put some testing code.\n");
	
	//struct superblock biggo = sbOpen(disktab[0]);
	
	printf("TESTING GET BLOCK BABEY\n");
	//struct superblock *biggo;// = sbInit(biggo, int diskfd)
	
	int dummo = sbGetBlock(supertab);
	sbFreeBlock(supertab, dummo);
	
    return OK;
}
