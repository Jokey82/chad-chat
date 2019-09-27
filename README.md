# chat v0.2
Basic chat program with ncurses ui.
Messages can now be sent in both directions.
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
