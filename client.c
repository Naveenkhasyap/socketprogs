#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> //inet_addr
 
int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char *message , server_reply[2000],msg[2000];
    int read_size;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
     
    puts("Connected\n");
     
    //Send some data
    while( (read_size = recv(socket_desc , server_reply , 2000 , 0)) > 0 )
    {
      puts(server_reply);
    	server_reply[0]='\0';
	gets(msg);
	write(socket_desc,msg,strlen(msg));
    }
    if(read_size==0)
    {
	printf("server disconnected\n");
    }
    else if(read_size=-1)
    {
	printf("receive failed\n");
    }
    return 0;
}
