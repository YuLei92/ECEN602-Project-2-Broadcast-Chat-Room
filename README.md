# Network Programming Assignment 2

* README and Test Case Report are written by Yu Lei.

* How to run:
    *  Enter "make -f Makefile" to compile the code.
    *  Use the command "./server <server.ip> <port.no> <max_clients>" to open the server.
    *  Open another Terminal and use the command "./client <username> <server.ip> <server.port>" to create a client.


* sbchead.h is the headfile defines the data struct and some static constants.
* For Client(client.c):
* join() – The function implements JOIN. 
* send_MSG() – When SELECT find that there are inputs from the keyboard, then will send them to the server. (SEND)
* read_MSG() - When SELECT find that there are inputs from the server, then will read them and display. (FWD)

* For Server(server.c):
* join_user() - When the user is qualified to join into the chatroom, use this function to add him to the use file.
* isExist() - Find out whether the username is in the use file before or not.
* delete_user() - When detect the user input an EOF, make him offline, and let the usename of him available.
* fwd_MSG() - Forward the username and message to all the connected clients.
* read_MSG() - Read the message from the client, find out it's JOIN, SEND or something not understood. And take related actions.

* Group distribution: 
    * Yulei writes the client part, server part and the test case.
    * Zeyu Wang try to implements some server code and the IPV6 feature, but he failed.
