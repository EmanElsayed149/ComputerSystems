# read fun 
- read(int fd,void *buf, int n) : copies at most n bytes from the current file position of descriptor to memory location buffer 
    - fd file descriptor 
    - buf memory location
    - number of bytes to be read
- file position of descriptor increase by n after each read call (if you call read(fd, buf,1) twice buf each call will contain different value)

## Examples

### 1. Suppose the disk file foobar.txt consists of the six ASCII characters foobar.Then what is the output of the following program?
```
#include "csapp.h"
int main()
{
  int fd1, fd2;
  char c;

  fd1 = Open("foobar.txt", O_RDONLY, 0);
  fd2 = Open("foobar.txt", O_RDONLY, 0);
  Read(fd1, &c, 1);
  Read(fd2, &c, 1);
  printf("c = %c\n", c);
  exit(0);
}
```
output 
```
c = f
```
explaination
```
The descriptors fd1 and fd2 each have their own open file table entry, so each
descriptor has its own file position for foobar.txt. Thus, the read from fd2 reads
the first byte of foobar.txt, and the output is
c = f
and not
c = o
```
### 2. suppose the disk file foobar.txt consists of the six ASCII characters foobar. Then what is the output of the following program?
```
#include "csapp.h"

int main()
{
  int fd;
  char c;
  fd = Open("foobar.txt", O_RDONLY, 0);
  if (Fork() == 0) {
  Read(fd, &c, 1);
  exit(0);
  }
  Wait(NULL);
  Read(fd, &c, 1);
 printf("c = %c\n", c);
 exit(0);
}
```
output
```
c = o
```
Explaination
```
Recall that the child inherits the parent’s descriptor table and that all processes
shared the same open file table. Thus, the descriptor fd in both the parent and
child points to the same open file table entry. When the child reads the first byte
of the file, the file position increases by 1. Thus, the parent reads the second byte,
and the output is
c = o
```

