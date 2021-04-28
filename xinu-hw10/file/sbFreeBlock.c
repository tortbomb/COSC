/* sbFreeBlock.c - sbFreeBlock */
/* Copyright (C) 2008, Marquette University.  All rights reserved. */
/*                                                                 */
/* Modified by                                                     */
/*                                                                 */
/* and                                                             */
/*                                                                 */
/*                                                                 */

#include <kernel.h>
#include <device.h>
#include <memory.h>
#include <disk.h>
#include <file.h>

/*------------------------------------------------------------------------
 * sbFreeBlock - Add a block back into the free list of disk blocks.
 *------------------------------------------------------------------------
 */
devcall sbFreeBlock(struct superblock *psuper, int block)
{
    // TODO: Add the block back into the filesystem's list of
    //  free blocks.  Use the superblock's locks to guarantee
    //  mutually exclusive access to the free list, and write
    //  the changed free list segment(s) back to disk.
	
	struct freeblock *freeblk, *free2;
	struct dirblock *swizzle;
    struct dentry *phw;
	int result, i;
    int diskfd;
	
	if (NULL == psuper)
    {
        return SYSERR;
    }
	phw = psuper->sb_disk;
    if (NULL == phw)
    {
        return SYSERR;
    }
	diskfd = phw - devtab;
	freeblk = psuper->sb_freelst;
    if (NULL == freeblk)
    {
        //printf("sbGetFree() ERROR: Superblock free list is empty!\n");
        return SYSERR;
    }
	
	// Updating the free list must be mutually exclusive.
    wait(psuper->sb_freelock);
	//if room in freeblock
	if (freeblk->fr_count < FREEBLOCKMAX){
		
		freeblk->fr_free[freeblk->fr_count] = block;
		freeblk->fr_count++;
		freeblk->fr_free[freeblk->fr_count] = 0;
		
		//below is copied from getBlock
		// Update this free block record on disk.
        free2 = freeblk->fr_next;
        if (NULL == freeblk->fr_next)
        {
            freeblk->fr_next = 0;
        }
        else
        {
            freeblk->fr_next =
                (struct freeblock *)freeblk->fr_next->fr_blocknum;
        }
        seek(diskfd, freeblk->fr_blocknum);
        if (SYSERR == write(diskfd, freeblk, sizeof(struct freeblock)))
        {
            return SYSERR;
        }
        freeblk->fr_next = free2;
		
		
	} else { //freelist is full
		
		if(NULL == freeblk->fr_next)
		{
			//if next block is null, were screwed, no room to add
			
            return SYSERR;
		}
		//this is also just copied
		// Copy over contents of next free block list segment,
        //  and then give out the block containing that segment. (put in the block. this comment is copied)
        free2 = freeblk->fr_next;
        free2->fr_free[free2->fr_count] = block;		//except for this
		free2->fr_count++;
        for (i = free2->fr_count - 1; i >= 0; i--) 	
        {
            freeblk->fr_free[i] = free2->fr_free[i];
        }
        freeblk->fr_count = free2->fr_count;
        freeblk->fr_next = free2->fr_next;
        free(free2);

        // Update this free block record on disk.
        free2 = freeblk->fr_next;
        if (NULL == freeblk->fr_next)
        {
            freeblk->fr_next = 0;
        }
        else
        {
            freeblk->fr_next =
                (struct freeblock *)freeblk->fr_next->fr_blocknum;
        }
        seek(diskfd, freeblk->fr_blocknum);
        if (SYSERR == write(diskfd, freeblk, sizeof(struct freeblock)))
        {
            return SYSERR;
        }
        freeblk->fr_next = free2;
		
		
	
		
	}
	
	
	
	signal(psuper->sb_freelock);
	
    return OK;
}
