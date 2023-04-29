# fork function :
- retun 0 to child process , child's pid to parent process
- Child get an identiacl copy of parent's virsual address space (but seperate)
- called once return twice 
- concurrent execution , can't predict execution order of parent and child

# reaping :
- performed by parent on terminated child by (wait () or waitpid() )
- parent is given exit status information 
- then kernal deletes  zombie child

# setjump and longjump
### [this link helped me to understand C setjump and longjump :](https://www.geeksforgeeks.org/c-setjump-and-longjump/)
- setjump(jmp_buf buf) :
  #### uses buf to remember the current position and returns 0.
- longjump(jmp_buf buf, i) : 
  #### Go back to place buf is pointing to and return i

### Example 
```
#include <setjmp.h>
#include <stdio.h>
jmp_buf buf;
void func()
{
    printf("Welcome to GeeksforGeeks\n");
  
    // Jump to the point setup by setjmp
    longjmp(buf, 1);
  
    printf("Geek2\n");
}
  
int main()
{
    // Setup jump position using buf and return 0
    if (setjmp(buf))
        printf("Geek3\n");
    else {
        printf("Geek4\n");
        func();
    }
    return 0;
}
```
### output :
```
Geek4
Welcome to GeeksforGeeks
Geek3
```
#### when you call longjmp(buf, 1) it makes code return  to place buf is pointing to , return value of setjmp = 1 instead of 0
