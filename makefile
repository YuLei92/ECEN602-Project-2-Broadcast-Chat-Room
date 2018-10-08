all: server client

client: client.c sbchead.h
	gcc sbchead.h client.c -o client

server: server.c sbchead.h
	gcc sbchead.h server.c -o server

clean:
	rm -rf server
	rm -rf client
