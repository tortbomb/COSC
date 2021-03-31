/*
 * COSC 3250 - Project 5
 * create.c file to create a new process and initialize it
 * @author [Sam Torti] [Jack Bielinski]
 * Instructor [Sabirat Rubya]
 * TA-BOT:MAILTO [samuel.torti@marquette.edu] [jackson.bielinski@marquette.edu]
 * */


/**
 * @file create.c
 * @provides create, newpid, userret
 *
 * COSC 3250 / COEN 4820 Assignment 4
 */
/* Embedded XINU, Copyright (C) 2008.  All rights reserved. */

#include <arm.h>
#include <xinu.h>

/* Assembly routine for atomic operations */
extern int _atomic_increment(int *);
extern int _atomic_increment_mod(int *, int);

static pid_typ newpid(void);
void userret(void);
void *getstk(ulong);

/**
 * Create a new process to start running a function.
 * @param funcaddr address of function that will begin in new process
 * @param ssize    stack size in bytes
 * @param name     name of the process, used for debugging
 * @param nargs    number of arguments that follow
 * @return the new process id
 */
syscall create(void *funcaddr, ulong ssize, int priority, char *name, ulong nargs, ...)
{
	int c,d;
	ulong *saddr;               /* stack address                */
	ulong pid;                  /* stores new process id        */
	pcb *ppcb;                  /* pointer to proc control blk  */
	ulong i;
	va_list ap;                 /* points to list of var args   */
	ulong pads = 0;             /* padding entries in record.   */
	void INITRET(void);

	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (ulong)(ssize + 3) & 0xFFFFFFFC;
	/* round up to even boundary    */
	saddr = (ulong *)getmem(ssize);     /* allocate new stack and pid   */
	pid = newpid();
	/* a little error checking      */
	if ((((ulong *)SYSERR) == saddr) || (SYSERR == pid))
	{
		return SYSERR;
	}

	_atomic_increment(&numproc);

	ppcb = &proctab[pid];
	/* setup PCB entry for new proc */
	ppcb->state = PRSUSP;

	// TODO: Setup PCB entry for new process.
	ppcb->stkbase = saddr;
	ppcb->stklen = ssize;
	ppcb->core_affinity = -1;
	strcpy((char *)ppcb->name, name);			//use strcpy here, no = needed 
	ppcb->priority = priority;
	

	/* Initialize stack with accounting block. */
	*saddr = STACKMAGIC;
	*--saddr = pid;
	*--saddr = ppcb->stklen;
	*--saddr = (ulong)ppcb->stkbase;

	/* Handle variable number of arguments passed to starting function   */
	if (nargs)
	{
		pads = ((nargs - 1) / 4) * 4;
	}
	/* If more than 4 args, pad record size to multiple of native memory */
	/*  transfer size.  Reserve space for extra args                     */
	for (i = 0; i < pads; i++)
	{
		*--saddr = 0;
	}

	// TODO: Initialize process context.
	
	
	
	ppcb->regs[PREG_PC] = (int) funcaddr;
	ppcb->regs[PREG_LR] = (int) INITRET;
	ppcb->regs[PREG_SP] = saddr;
	/* *--saddr = ppcb->regs[PREG_IP];
	*--saddr = ppcb->regs[PREG_R11];
	*--saddr = ppcb->regs[PREG_R10];
	*--saddr = ppcb->regs[PREG_R9];
	*--saddr = ppcb->regs[PREG_R8];
	*--saddr = ppcb->regs[PREG_R7];
	*--saddr = ppcb->regs[PREG_R6];
	*--saddr = ppcb->regs[PREG_R5];
	*--saddr = ppcb->regs[PREG_R4];
	*--saddr = ppcb->regs[PREG_R3];
	*--saddr = ppcb->regs[PREG_R2];
	*--saddr = ppcb->regs[PREG_R1];
	*--saddr = ppcb->regs[PREG_R0]; */
	
	
	// TODO:  Place arguments into activation record.
	//        See K&R 7.3 for example using va_start, va_arg and
	//        va_end macros for variable argument functions.
	
	va_start(ap, funcaddr);
	if(nargs<5){
		for(c = 0; c < nargs; c++){
			ppcb->regs[c] = va_arg(ap, int);
		}
		va_end(ap);
		return pid;
	} else {
		for(c = 0; c < 4; c++){
			ppcb->regs[c] = va_arg(ap, int);
		}
		for(d = 4; d < nargs; d++){
			*saddr = va_arg(ap, int);
			*++saddr;
		}
	}
	
	va_end(ap);	
	
	
	
	
	
	
	
	
	
	

	return pid;
}

/**
 * Obtain a new (free) process id.
 * @return a free process id, SYSERR if all ids are used
 */
static pid_typ newpid(void)
{
	pid_typ pid;                /* process id to return     */
	static pid_typ nextpid = 0;

	for (pid = 0; pid < NPROC; pid++)
	{                           /* check all NPROC slots    */
		//        nextpid = (nextpid + 1) % NPROC;
		_atomic_increment_mod(&nextpid, NPROC);
		if (PRFREE == proctab[nextpid].state)
		{
			return nextpid;
		}
	}
	return SYSERR;
}

/**
 * Entered when a process exits by return.
 */
void userret(void)
{
	uint cpuid = getcpuid();
	kill(currpid[cpuid]);
}
