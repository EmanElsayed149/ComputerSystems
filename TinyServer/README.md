# Tiny web server 

## description
- A small , iterative and HTTP/1.0 web server , it can server one client at a time 
- It is powerful enough to
serve both static and dynamic content to real Web browsers

## Main routine
- Tiny is an iterative server that listens
for connection requests on the port that is passed in the command line. 
- Open a listening socket by calling the open_listenfd function
- Tiny executes the typical infinite server loop repeatedly accepting a connection request
- Perform a transaction
    - Tiny serves five common types of static content: HTML files, unformatted textfiles, and images encoded in GIF, PNG, and JPEG formats.
    - Tiny serves any type of dynamic content by forking a child process and then running a CGI program in the context of the child. 
- close its end of the connection
## run server 
```
make 
```
```
./tiny  <port>
```
## Connect to the server 
1- **telnet** 
``` 
telnet <hostname> <port> 
```
![picture alt](https://github.com/EmanElsayed149/ComputerSystems/blob/main/TinyServer/videos/P1.png)
![picture alt](https://github.com/EmanElsayed149/ComputerSystems/blob/main/TinyServer/videos/P2.png)

2- **web browser**
 
![web browser](https://github.com/EmanElsayed149/ComputerSystems/blob/main/TinyServer/videos/P3.png)

![web browser](https://github.com/EmanElsayed149/ComputerSystems/blob/main/TinyServer/videos/P4.png)

## files
- cgi-bin/adder : CGI program
- videos : screenshots and video for runnling server
-  godila and happy for home.html
- tiny.c : main code for server
- helpers : helper functions
