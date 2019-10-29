# chad-chat v0.3.4
Basic chat program with ncurses UI for Linux.

## Compilation:

gcc client.c chat.c -lncurses -lpthread -o client

gcc server.c chat.c -lncurses -lpthread -o server 

## Usage:  

server [port] [password]  

client [ip] [port]  
To exit enter \` character  
## Issues:  
Present UI is only designed to support basic program functionality. 

## TODO: 

 - [x] Allow messages to be both sent and received simultaneously;
 - [x] Implement proper client - server model; 
 - [x] Multiple clients; 
 - [x] Chatrooms;
 - [x] Usernames;
 - [x] Password-protected servers;
 - [x] Fix corrupted usernames issue;
 - [ ] Major UI update; 
 - [ ] Encryption;
 - [ ] Major refactoring;
 - [ ] User accounts and password authentification; 
 - [ ] Private user-user communication;
 - Constant stability improvements;
