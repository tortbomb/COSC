/* fileDelete.c - fileDelete */
/* Copyright (C) 2008, Marquette University.  All rights reserved. */
/*                                                                 */
/* Modified by                                                     */
/*                                                                 */
/* and                                                             */
/*                                                                 */
/*                                                                 */

#include <kernel.h>
#include <memory.h>
#include <file.h>

/*------------------------------------------------------------------------
 * fileDelete - Delete a file.
 *------------------------------------------------------------------------
 */
devcall fileDelete(int fd)
{
    // TODO: Unlink this file from the master directory index,
    //  and return its space to the free disk block list.
    //  Use the superblock's locks to guarantee mutually exclusive
    //  access to the directory index.
	
	if ((NULL == supertab) || (NULL == filetab))
    {
        return SYSERR;
    }
	
	if ((fd < 0) || (fd > DIRENTRIES)){
		
		return SYSERR;
	}

	wait(supertab->sb_dirlock);
	while ((fd < DIRENTRIES) && (FILE_FREE != filetab[fd].fn_state))
    {
        fd++;
    }

    if (fd >= DIRENTRIES)
    {
        signal(supertab->sb_dirlock);
        return SYSERR;
    }

 
    //filetab[fd].fn_length = fd;
    //filetab[fd].fn_cursor = 0;
    //strncpy(filetab[fd].fn_name, name, FNAMLEN);
    //filetab[fd].fn_name[FNAMLEN] = '\0';
    //filetab[fd].fn_data = (char *)malloc(DISKBLOCKLEN);          

    if (NULL != filetab[fd].fn_data)
    {
        //filetab[fd].fn_state = FILE_FREE;
        signal(supertab->sb_dirlock);
        return SYSERR;

    }

    filetab[fd].fn_state = FILE_OPEN;        
                sbFreeBlock(supertab, fd);
    signal(supertab->sb_dirlock);

    filetab[fd].fn_blocknum = 0;

    if (SYSERR == filetab[fd].fn_blocknum)
    {
        return SYSERR;
    }
	
    return OK;
}
