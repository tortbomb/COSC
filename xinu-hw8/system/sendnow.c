/**
 * @file sendnow.c
 * @provides sendnow.
 *
 */
/* Embedded Xinu, Copyright (C) 2020.   All rights reserved. */

#include <xinu.h>

/**
 * Send a message to anoher thread
 * @param pid proc id of recipient
 * @param msg contents of message
 * @return OK on sucess, SYSERR on failure
 */

syscall sendnow(int pid, message msg)
{
	register pcb *ppcb;
	ppcb = &proctab[currpid[getcpuid()]];

	/* TODO:
 	* - Acquire Lock and release when appropriate
 	* - PID & Process Error Checking
 	* - Deposit Message, raise flag
 	* -  If receving message is blocked, ready process
 	* - Return OK
 	*/

	if(isbadpid(pid)){
		return SYSERR;
	}
	
	lock_acquire(ppcb->msg_var.core_com_lock);
	
	if(ppcb->msg_var.hasMessage == 1){
		lock_release(ppcb->msg_var.core_com_lock);
		return SYSERR;
	}
	else {
		ppcb->msg_var.msgin = msg;		//deposit msg
		ppcb->msg_var.hasMessage = 1;	//raise flag
	}
	
	if(ppcb->state == PRRECV){
		ready(pid, 1, ppcb->core_affinity);
	}
	lock_release(ppcb->msg_var.core_com_lock);

	return OK;
}
