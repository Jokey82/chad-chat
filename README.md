# chad-chat v0.3.3
Basic chat program with ncurses UI for Linux.

Compilation:

gcc client.c chat.c -lncurses -lpthread -o client

gcc server.c chat.c -lncurses -lpthread -o server 

Usage: 

server [port]   

client [ip] [port]

Issues:  
Program had been tested on virtual machine(Debian-10 on Hyper-V) and on the physical one. Virtual machine tests showed some issues, wich caused usernames sometimes to appear corrupted and appended with unprintable characters. This issues, despite being fairly common for vm tests, have never been envountered on physical machine, so at the moment I consider them to be caused by certain VM specialities. 

TODO: 

 - [x] Allow messages to be both sent and received simultaneously;
 - [x] Implement proper client - server solution; 
 - [x] Multiple clients; 
 - [x] Chatrooms;
 - [x] Usernames;
 - [ ] User accounts and password authentification; 
 - [ ] Password-protected servers;
 - [ ] Big UI update; 
 - [ ] Private user-user communication;
 - Constant stability improvements;
 - Constant UI improvements.
