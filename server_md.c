// Author : Yu Lei
// Last Update: 
// Format: ./server server_ip server_port max_clients
// initiate JOIN, can SEND and FWD messages
// use select to handle both sending and receving

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "sbchead.h"

void subprocess(int socket, struct SBCP_Message *message_from_client){
    int msglen= sizeof(message_from_client);
    bzero((struct message *) &message_from_client,msglen);
    int n=read(socket,(struct SBCP_Message *) &message_from_client,msglen);
    printf("username is ");
    int i = 0;
    for(i=0;i<(message_from_client->attribute.Length-4);i++){
        printf("%c",(message_from_client->attribute.Payload[i]));
    }
};

int main(int argc, char* argv[]){
    struct sockaddr_in sin;
    int len;
    int socket_id, new_socket_id; //This is the socket
//we don't need buf in the main.
    
    if(argc != 4){
        fprintf(stderr, "usage: simplex - talk host\n");
        exit(0);
    }
    
    char* server_address = argv[1];
    char* port_no = argv[2];
    int max_clients = atoi(argv[3]);
    
    printf("The port number from command line is %s\n",port_no);
    
//    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(server_address); // maysbe ip address;
    sin.sin_port = htons(atoi(port_no));
    printf("The max_clients is %d\n", max_clients);
    
    struct SBCP_Message *message_from_client;
    message_from_client = malloc(sizeof(struct SBCP_Message));
    
    /* setup passive open*/
    if((socket_id = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Simplex - talk : socket");
        exit(0);
    }
    printf("Socket successfully created!\n");
    
    
    if((bind(socket_id, (struct sockaddr *)&sin, sizeof(sin))) < 0){
        perror("simplex -talk: bind\n");
        exit(0);
    }else{
        printf("Socket binded.\n");
    }
    
    printf("Listening to the client...\n");
    
    if(listen(socket_id, MAX_PEDING)< 0){
        perror("Cannot find the client!\n");
    }
    
    while(1){
        if((new_socket_id = accept(socket_id,(struct sockaddr *)&sin, &len)) <0){
            perror("simplex - talk: accept\n");
            exit(0);
        }
        
        int pid = fork();
        
        if(pid < 0){
            perror("Failure to fork");
        }
        if (pid == 0) { // The child process is generated.
            subprocess(new_socket_id, message_from_client); // Fork successfully and try to handle the messages
            exit(0);
        }
        else {
             close(new_socket_id);
        }
    }
    return 0;
}