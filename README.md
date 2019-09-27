# chat
Basic chat program with ncurses ui.
In current version messages can only be sent in one direction, by default it's from client to server.
I'm not sure if it even works over the Internet without port forwarding or something, only tested it over LAN.

Compilation:

gcc client.c chat.c -lncurses -o client

gcc server.c chat.c -lncurses -o server 

Usage: 

server [port]   

client [ip] [port]

TODO: 

[x] Allow messages to be both sent and received simultaneously.

[ ] Improve UI.
