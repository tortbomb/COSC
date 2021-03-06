/**
 * @file testcases.c
 * @provides testcases
 *
 *
 * Modified by:	
 *
 * TA-BOT:MAILTO 
 *
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <xinu.h>

void infinite(void){
	uint cpuid = getcpuid();
	int i = 0;
	enable();
	
	while(1==1){
				kprintf("Number %d\r\n", i);
				i++;
				udelay(1);}
	
}


void print_freelist(void)
{
	int cpuid;
	cpuid = getcpuid();
	
	register memblk *prev, *curr;
	
	ulong this, cur;
	this = (ulong)freelist[cpuid].head;

	kprintf("Current node address: %d\n", this);
	
	/*int i = 0;
	for(i = 0; i < 4; i++){
		curr = freelist[i].head;
		prev = freelist[i].base;
		
		//cur = (ulong)freelist[i].head;
		//pre = (ulong)freelist[i].base;
			while(curr->next != NULL){
				cur = (ulong)curr;
				kprintf("Current node address: %p \n", cur);
				prev = curr;
				curr = curr->next;
				
			}
	}
		*/





	//printpid below

    /*int i = 0;
    uint cpuid = getcpuid();

    enable();
    for (i = 0; i < times; i++)
    {
        kprintf("This is process %d\r\n", currpid[cpuid]);
        udelay(10);
    }
	*/
}

/**
 * testcases - called after initialization completes to test things.
 */
void testcases(void)
{
    uchar c;

    kprintf("===TEST BEGIN===\r\n");
	//print_freelist();
	//getmem(10);
	//print_freelist();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//kprintf("0) Test priority scheduling\r\n");					//i did this, this is old tests
    //kprintf("\'A\') Aging / Starvation testcase\r\n");
    //kprintf("\'P\') Preemption testcase\r\n");

    // TODO: Test your operating system!

	/*
    c = kgetc();
    switch (c)
    {
    case '0':
        // Run 3 processes with varying priorities
        ready(create
              ((void *)printpid, INITSTK, PRIORITY_HIGH, "PRINTER-A", 1,
               5), RESCHED_NO, 0);
        ready(create
              ((void *)printpid, INITSTK, PRIORITY_MED, "PRINTER-B", 1,
               5), RESCHED_NO, 0);
        ready(create
              ((void *)printpid, INITSTK, PRIORITY_LOW, "PRINTER-C", 1,
               5), RESCHED_YES, 0);

        break;

    case 'a':
    case 'A':
#if AGING
        // AGING TESTCASE
        kprintf("AGING is enabled.\r\n");

        // TODO: Create a testcase that demonstrates aging 
		ready(create
              ((void *)printpid, INITSTK, PRIORITY_MED, "B", 1,5)
               , RESCHED_NO, 0);
			   
		ready(create
              ((void *)printpid, INITSTK, PRIORITY_MED, "C", 1,5)
               , RESCHED_NO, 0);
		
		ready(create
              ((void *)infinite, INITSTK, PRIORITY_HIGH, "A", 0)
               , RESCHED_YES, 0); 
		
		
		


#else
        // STARVING TESTCASE
        kprintf("\r\nAGING is not currently enabled.\r\n");

        // TODO: Create a testcase that demonstrates starvation
		ready(create
              ((void *)printpid, INITSTK, PRIORITY_LOW, "B", 1, 5)
               , RESCHED_NO, 0);
		
		ready(create
              ((void *)infinite, INITSTK, PRIORITY_HIGH, "A", 0)
               , RESCHED_YES, 0);
			   
		


#endif
        break;

    case 'p':
    case 'P':
#if PREEMPT
        // PREEMPTION TESTCASE
        kprintf("\r\nPreemption is enabled.\r\n");

        // TODO: Create a testcase that demonstrates preemption
		
		ready(create
              ((void *)infinite, INITSTK, PRIORITY_HIGH, "A", 0)
               , RESCHED_NO, 0);
			   
		ready(create
              ((void *)printpid, INITSTK, PRIORITY_HIGH, "B", 1, 5)
               , RESCHED_YES, 0);
			   
		

#else
        kprintf("\r\nPreemption is not currently enabled...\r\n");
#endif
        break;

    default:
        break;
    }*/																

    kprintf("\r\n===TEST END===\r\n");
    return;
}
