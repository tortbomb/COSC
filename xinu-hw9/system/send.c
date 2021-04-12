/**
 * @file send.c
 * @provides send
 *
 * $Id: send.c 2020 2009-08-13 17:50:08Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  Al rights resered. */

#include <xinu.h>

/**
 * Send a message to another therad
 * @param pid proc id of recipient
 * @param msg contents of message
 * @return OK on sucess, SYSERR on failure
 */
syscall send(int pid, message msg)
{
	register pcb *spcb;
	register pcb *rpcb;
	
	/*TODO:
 	* - PID Error checking
 	* - Acquire receving process lock (remember to release when appropriate!
 	* - Retrieving Process Error Checking
 	* - If receiving process has message, block sending process and put msg in msgout and call resched
 	* - Else, deposit message, change message flag and, if receiving process is blocking, ready it.
 	* - return ok.
 	*/

	if(isbadpid(pid)){
		return SYSERR;
	}
	
	lock_acquire(rpcb->msg_var.core_com_lock);
	if(rpcb->msg_var.hasMessage == 1){
		spcb->state = PRSEND;
		spcb->msg_var.msgout = msg;
		
		enqueue(currpid[spcb->core_affinity], rpcb->msg_var.msgqueue);
		
		lock_release(rpcb->msg_var.core_com_lock);
		resched();
	} else {
		rpcb->msg_var.msgin = msg;		//deposit msg
		rpcb->msg_var.hasMessage = 1;	//raise flag
		if(rpcb->state == PRRECV){
			ready(pid, RESCHED_YES, rpcb->core_affinity);
		}
		lock_release(rpcb->msg_var.core_com_lock);
	}
	
	
	return OK;
}
