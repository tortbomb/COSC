/*
 * COSC 3250 - Project 3
 * Testcases file for the xinu-hw3 assignment.
 * @author [Sam Torti] [Jack Bielinski]
 * Instructor [Sabirat Rubya]
 * TA-BOT:MAILTO [samuel.torti@marquette.edu] [jackson.bielinski@marquette.edu]
 * */


/**
 * @file testcases.c
 * @provides testcases
 *
 * $Id: testcases.c 175 2008-01-30 01:18:27Z brylow $
 *
 * Modified by:
 *
 * and
 *
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <xinu.h>

devcall putc(int dev, char c)
{
    return 0;
}


/**
 * testcases - called after initialization completes to test things.
 */
void testcases(void)
{
    int c;
	int b;

    kprintf("===TEST BEGIN===\r\n");

    c = kgetc();
    switch (c)
    {

        // TODO: Test your operating system!
		case 'a':
		b = kcheckc();		//returns T or F if there is an available character in buffer or UART
		kprintf("0 (false) or 1 (true): %d\n", b);
		break;
		
		case 'b':		//returns the char casted as an int
		b = kgetc();
		kprintf("Char as int: %d\n", b);
		break;
		
		case 'c':
		kungetc('c');		//places char in buffer array
		break;
		
		case 'd':
		kputc(c);	//puts in char, returns it
		break;
		
		case 'e':	//calling kgetc() with a char in the buffer array, should return the value in buffer
		kungetc(c);
		b = kgetc();
		kprintf("Array contains: %d\n", b);
		break;
		
		case 'f': 	//simply tests kprintf
		kprintf("Hello World Bing Bong Ding Dong");
		break;
		

    default:
        kprintf("Hello Xinu World!\r\n");
    }


    kprintf("\r\n===TEST END===\r\n");
    return;
}
