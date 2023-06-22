## MallocLab (Dynamic storage allocator)
## Description 
In this lab ,  my implementation for specific explicit allocator in which application allocates and frees space ,means that when application is finished with it ,system won't free space unless you do it . using (mm_malloc - mm_free - mm_realloc)
## Main routine 
* This allocator depends on  **implicit free list** structure  to jump between blocks (first word in block contain size and allocated bit called header ) using size stored in header to jump to next block checking if it free or allocated
* there are two techniques to search for a fit space (**first fit - second fit**)
* If fit space is larger than size , **split it if and only extra space > min_space** (min_space = 2*8 bytes to maintain alignment)
* When freeing block , You should merge all neighbouring free blocks **(coalescing) by boundary tags tecnique** to reduce external fragmentation
## How to use allocator
* cd malloclab-handout
* make
* ./mdriver -h to get help
## files
***solution in malloclab-handout***
* mm.c : package implementation
* mdriver.c	: The malloc driver that tests your mm.c file
* Makefile : Builds the driver
* Other support files for the driver