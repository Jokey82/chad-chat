# chat
Basic chat program with ncurses ui. In current version client and server are separated into two executables.
Messages can only be sent in one direction, by default it's from client to server.
I'm not sure if it even works over Internet without port forwarding or something, only tested it over LAN.

Compilation:

gcc client.c chat.c -lncurses -o client

gcc server.c chat.c -lncurses -o server 

TODO: 

- Allow messages to be both sent and received simultaneously.

- Merge both client and server into one executable in order to simplify the process of starting the application.

- Improve UI.
