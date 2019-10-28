# chad-chat v0.3.3
Basic chat program with ncurses UI for Linux.

Compilation:

gcc client.c chat.c -lncurses -lpthread -o client

gcc server.c chat.c -lncurses -lpthread -o server 

Usage:  

server [port] [password]  

client [ip] [port]

Issues:  
Passwords and usernames are currently required to be >6 charachters, due to issues encountered during testing.

TODO: 

 - [x] Allow messages to be both sent and received simultaneously;
 - [x] Implement proper client - server solution; 
 - [x] Multiple clients; 
 - [x] Chatrooms;
 - [x] Usernames;
 - [x] Password-protected servers;
 - [ ] User accounts and password authentification; 
 - [ ] Big UI update; 
 - [ ] Private user-user communication;
 - Constant stability improvements;
 - Constant UI improvements.
