# chat v0.2
Basic chat program with ncurses ui.
Messages can now be sent in both directions.
Port forwarding is needed to use this over the Internet.

Compilation:

gcc client.c chat.c -lncurses -o client

gcc server.c chat.c -lncurses -o server 

Usage: 

server [port]   

client [ip] [port]

TODO: 

[x] Allow messages to be both sent and received simultaneously.

[ ] Improve UI.
