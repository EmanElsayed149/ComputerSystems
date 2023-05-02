# Tiny-Shell 
## Description :
- Shell supports the notion of job control, which allows users to move jobs back and forth between back-
ground and foreground, and to change the process state (running, stopped, or terminated) of the processes
in a job. 
- Main routine is :
   -  prints a prompt
   -  reads cmdline 
   - then evaluates 
- Main routine for evaluation :
    - parses cmdline to bulid argv (cmdline arguments)
    - checks if it built-in cmd to evaluate it in current process , if not ,it forks child process which call exceve to execute it
    -  then checks if job BG(background) or FG(foreground)
        - if BG : it doesn't wait it to terminate 
        - else : if waits it to terminate 
- This shell supports the following built-in commands:
    - **jobs** : command lists all background jobs.
    - **quit** : command terminates the shell.
    - **bg \<job>**: command restarts \<job> by sending it a SIGCONT signal, and then runs it in
the background. The \<job> argument can be either a PID or a JID
   - **fg \<job>** : command restarts \<job> by sending it a SIGCONT signal, and then runs it in
the foreground. The \<job> argument can be either a PID or a JID
- you can also run your programm by giving tinyshell path of your programm for example :
   - **tsh> /bin/echo 'hello, world!'**
### **note: this shell can't support pipe (|) or redirections (> <)**

## How to use it :
- cd shlab-handout
-  make
- ./tsh
## Files (solution in shlab-handout):
- tsh.c : this file contains my implementation of shell code 
- tsh : executable file to run shell
- tshref : the reference solution for the shell
- trace01.txt - trace15.txt :  you will use in conjunction with the shell driver to test the correctness of your shell