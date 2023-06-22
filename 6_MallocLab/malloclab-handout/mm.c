/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "mm.h"
#include "memlib.h"


#define NEXT_FIT
static char *heap_listp =0;
#ifdef NEXT_FIT
static char *rover;  /*for NEXT_FIT*/
#endif

static void place(void *bp,size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void *extend_heap(int words);

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};
/*Basic constants and Macros*/
#define WSIZE               4                          /* word and header/footer size in bytes */
#define DSIZE               8                          /* double word size */
#define CHUNKSIZE           (1<<12)                    /* extend heap by this amount of bytes */
#define MIN_SIZE            (2*DSIZE)                  /*min size to be allocated to maintain alignment*/

#define MAX(x,y)            ( (x) > (y)? (x):(y) )  
#define PACK(size,alloc)    ( (size) | (alloc) )       /*pack size and allocated bit in word (size=payload+header+footer)*/

/* Read and Write a word at address p */
#define PUT(p,val)          ( *(unsigned int*)(p) = (val) )
#define GET(p)              ( *(unsigned int*)(p) )

/*Read size and allocated bit from address p*/
#define GET_SIZE(p)         ( GET(p) & ~0x7)           /*and value with ~0x7 beause size allawys greater than 7 */
#define GET_ALLOC(p)        ( GET(p) & 0x1 )

/*find address of header/footer for given block bp*/
#define HDRP(bp)            ( (char*)(bp) - WSIZE)
#define FTRP(bp)            ( (char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/*find address of next and previous blocks for given current block bp */
#define NEXT_BLKP(bp)       ( (char*)(bp) + GET_SIZE((char*)(bp) - WSIZE) )
#define PREV_BLKP(bp)       ( (char*)(bp) - GET_SIZE((char*)(bp) - DSIZE) )

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))


static void *coalesce(void *bp)
{
    size_t asize;                                   //size of adjusted blocks
    size_t presize = GET_SIZE(HDRP(PREV_BLKP(bp))); //size of previous block
    size_t nxtsize = GET_SIZE(HDRP(NEXT_BLKP(bp))); //size of next block 
    size_t csize = GET_SIZE(HDRP(bp));              // size of current block
    /*
    * if prevoius and next  blocks are free
    * header of previous block and footer of next block are updated with new size
    */
    if(!GET_ALLOC(HDRP(PREV_BLKP(bp))) && !GET_ALLOC(HDRP(NEXT_BLKP(bp))))
    {
        asize =  presize + nxtsize + csize;
        PUT(HDRP(PREV_BLKP(bp)) , PACK(asize,0));
        PUT(FTRP(NEXT_BLKP(bp)) , PACK(asize,0));
        bp =  PREV_BLKP(bp);
    }else if(GET_ALLOC(HDRP(PREV_BLKP(bp))) && GET_ALLOC(HDRP(NEXT_BLKP(bp))))
    {
        /*
        * if prevoius and next  blocks are allocated 
        * return bp
        */
        return bp;
    }else if (!GET_ALLOC(HDRP(PREV_BLKP(bp))) && GET_ALLOC(HDRP(NEXT_BLKP(bp))))
    {
        /*
        * if prevoius block is free and next  blocks is allocated 
        * header of previous block and footer of current  block are updated with new size
        */
        asize = csize + presize;
        PUT(HDRP(PREV_BLKP(bp)) , PACK(asize,0));
        PUT(FTRP(bp), PACK(asize,0));
        bp = PREV_BLKP(bp);
    }
    else{
        /*
        * if prevoius block is allocated and next  blocks is free 
        * header of current block and footer of next  block are updated with new size
        */
        asize = csize + nxtsize;
        PUT(FTRP(NEXT_BLKP(bp)) , PACK(asize,0)); //can't replac this line with next because i update value in header and nxtblock depend on header 
        PUT(HDRP(bp) , PACK(asize,0));
    }
    #ifdef NEXT_FIT
    /* Make sure the rover isn't pointing into the free block */
    /* that we just coalesced */
    if ((rover > (char *)bp) && (rover < NEXT_BLKP(bp)))
        rover = bp;
    #endif
    return bp;

}

static void place(void *bp,size_t asize)
{
    size_t blocksize = GET_SIZE(HDRP(bp));
    size_t remainsize;
    remainsize = blocksize - asize;
    if(remainsize >= MIN_SIZE)
    {
        PUT(HDRP(bp) , PACK(asize,1));   //split block to asize and mark it as allocated at header 
        PUT(FTRP(bp) , PACK(asize,1));  //footer of block with asize bytes 
        PUT(HDRP(NEXT_BLKP(bp)) , PACK(remainsize,0)); //header of remainsize and mark it as unallocated 
        PUT(FTRP(NEXT_BLKP(bp)) , PACK(remainsize,0)); //footer of remainsize and mark it as unallocated 
        return ; 
    }
    PUT(HDRP(bp) , PACK(blocksize,1));   //header of block with blocksize bytes  and mark it as allocated  
    PUT(FTRP(bp) , PACK(blocksize,1));   //footer of block with blocksize bytes 
    return ; 
}
static void *find_fit(size_t asize)
{
    
    #ifdef NEXT_FIT
    //search for next fit
    char *oldrover = rover;
    for(; GET_SIZE(HDRP(rover)) > 0 ; rover = NEXT_BLKP(rover))
    {
        if(GET_SIZE(HDRP(rover)) >= asize && !GET_ALLOC(HDRP(rover)))
        {
            return rover;
        }
    }
    for(rover = heap_listp; rover != oldrover ; rover = NEXT_BLKP(rover))
    {
        if(GET_SIZE(HDRP(rover)) >= asize && !GET_ALLOC(HDRP(rover)))
        {
            return rover;
        }
    }
    #else
    //search for first fit
    char *ptr;
    for(prt = heap_listp ; GET_SIZE(HDRP(ptr)) ; ptr = NEXT_BLKP(ptr))
    {
        if(GET_SIZE(HDRP(ptr)) >= asize && !GET_ALLOC(HDRP(ptr)))
        {
            return ptr;
        }
    }
    #endif
    return NULL;

}
static void *extend_heap(int words)
{
    void *bp;
    int size;
    /*allocate an even number of words to maintain alignment */
    size = (words % 2)? (words+1) * WSIZE : words * WSIZE;
    if( (bp = mem_sbrk(size)) == (void*) -1)
    {
        return NULL;
    }
    PUT(HDRP(bp) , PACK(size,0));
    PUT(FTRP(bp) , PACK(size,0));
    PUT(HDRP(NEXT_BLKP(bp)) , PACK(0,1));  /*new epilogue header*/
    /*coalesce if previous block is free*/
    return coalesce(bp);
}
/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    /*create initial empty heap*/
    if( (heap_listp = mem_sbrk(4*WSIZE)) == (void*)-1)
    {
        return -1 ;
    }
    /*initialize prologue block and epilogue block header*/
    PUT(heap_listp,0);
    PUT(heap_listp + (1*WSIZE) , PACK(DSIZE,1)); /*header of prologue block*/
    PUT(heap_listp + (2*WSIZE) , PACK(DSIZE,1)); /*footer of prologue block*/
    PUT(heap_listp + (3*WSIZE) , PACK(0,1));     /*header of epilogue block*/
    heap_listp += 2*WSIZE ;

    #ifdef NEXT_FIT
        rover = heap_listp;
    #endif

    //extend heap with chunksize
    if(extend_heap(CHUNKSIZE/WSIZE) == NULL)
    {
        return -1;
    }
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize; /*size to be extended from heap*/
    int errorflag;
    char *bp;
    if(heap_listp == 0)
    {
        errorflag = mm_init();
        if(errorflag==-1){
            fprintf(stderr,"mm_init caused error\n");
            exit(0);
        }
    }
    if(size == 0 )
        return NULL;
    if(size <= DSIZE)
    {
        asize = MIN_SIZE;
    }
    else{
        asize = DSIZE*((size + (DSIZE-1)+(DSIZE))/DSIZE);
    }
    /*search the free list fot a fit */
    if( (bp = find_fit(asize)) != NULL)
    {
        place(bp,asize);
        return bp;
    }
    /*no fit found , get more memory and place it */
    extendsize = MAX(asize,CHUNKSIZE);
    if((bp = extend_heap(extendsize/WSIZE)) == NULL)
    {
        return NULL;
    }
    place(bp,asize);
    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t csize = GET_SIZE(HDRP(ptr));
    if(ptr == NULL || heap_listp==NULL)
       return;
    PUT(HDRP(ptr) , PACK(csize,0));
    PUT(FTRP(ptr) , PACK(csize,0));
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    size_t csize ;
    if(size == 0 )
    {
        mm_free(oldptr);
        return NULL;
    }
    newptr = mm_malloc(size);
    if(oldptr == NULL || newptr == NULL)
        return newptr;
    csize = GET_SIZE(HDRP(oldptr));
    copySize = csize < size ? csize : size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}
