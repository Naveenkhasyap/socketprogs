#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
 
int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
//    char message[2000];
    int read_size;
    char msg[2000],client_message[2000]; 
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        //Reply to the client
        char message[2000] = "\n";
        write(new_socket , message , strlen(message));
  //message[0]='\0';
	while( (read_size = recv(new_socket , client_message , 2000 , 0)) > 0 )
    	{
       		puts(client_message);
		client_message[0]='\0';
		gets(msg);
        	write(new_socket , msg , strlen(msg));
		msg[0]='\0';
    	}	
    	if(read_size == 0)
    	{
        	puts("Client disconnected");
        	fflush(stdout);
    	}
    	else if(read_size == -1)
    	{
        	perror("recv failed");
    	}
    }    
    if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }    
    return 0;
}
