# chat v0.2
Basic chat program with ncurses ui for Linux.

Compilation:

gcc client.c chat.c -lncurses -o client

gcc server.c chat.c -lncurses -o server 

Usage: 

server [port]   

client [ip] [port]

TODO: 

 - [x] Allow messages to be both sent and received simultaneously.
 - [ ] Implement proper client - server solution. 
 - [ ] Multiple clients. 
 - [ ] Chatrooms.
 - Constant UI improvements.
