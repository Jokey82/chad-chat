# chad-chat v0.3.2
Basic chat program with ncurses UI for Linux.

Compilation:

gcc client.c chat.c -lncurses -lpthread -o client

gcc server.c chat.c -lncurses -lpthread -o server 

Usage: 

server [port]   

client [ip] [port]

TODO: 

 - [x] Allow messages to be both sent and received simultaneously.
 - [x] Implement proper client - server solution. 
 - [x] Multiple clients. 
 - [x] Chatrooms.
 - [x] Usernames
 - [ ] Stability
 - [ ] Password-protected servers
 - Constant UI improvements.
