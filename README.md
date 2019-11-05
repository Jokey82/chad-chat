# chad-chat v0.4
Basic chat program with ncurses UI for Linux.

## Update
Completely rewritten UI. Still ugly but a bit more useful.

## Compilation:

gcc client.c chat.c ui.c -lncurses -o client

gcc server.c chat.c -lncurses -lpthread -o server 

## Usage:  

server [port] [password]  

client [ip] [port]  
To exit enter \` character  
## Issues:  
Backspace does not work in the username submitting window. 

## TODO: 

 - [x] Allow messages to be both sent and received simultaneously;
 - [x] Implement proper client - server model; 
 - [x] Multiple clients; 
 - [x] Chatrooms;
 - [x] Usernames;
 - [x] Password-protected servers;
 - [x] Fix corrupted usernames issue;
 - [x] Major UI update; 
 - [ ] Encryption;
 - [ ] Major refactoring;
 - [ ] User accounts and password authentification; 
 - [ ] Private user-user communication;
 - Constant stability improvements;
