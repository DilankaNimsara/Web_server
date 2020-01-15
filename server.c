#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>

#define BYTES 1024

int main(){
    
char msg[256]="HTTP/1.1 200 OK\r\n"
"Content-Type : text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><head><title>localhost</title>\r\n"
"<style>body { background-color:#A9C0F5 }</style></head>\r\n"
"<body><center><h1>Server reached!</h1><br>\r\n"
"<hr>\r\n"
"</center></body></html>\r\n";

int sock = socket(AF_INET,SOCK_STREAM,0);

struct sockaddr_in s_addr,c_addr;
s_addr.sin_family=AF_INET;
s_addr.sin_port=htons(8080);
s_addr.sin_addr.s_addr=htonl(INADDR_ANY);

int b=bind(sock,(struct sockaddr *) &s_addr,sizeof(s_addr));
int l=listen(sock, 5);

char mesg[99999], *reqline[3], data_to_send[BYTES], path[99999];
int rcvd, fd, bytes_read;

while(1){

int client= sizeof(c_addr);
int a = accept(sock,(struct sockaddr *) & c_addr,&client);
 memset( (void*)mesg, (int)'\0', 99999 );

    rcvd=recv(a, mesg, 99999, 0);

close(a);
}

close(sock);

}	// printf("%s\n", buf);

		// if(!strncmp(buf,"GET /1.png",16)){

		// fdimg=open("GET /1.png",O_RDONLY);
		// sendfile(fd_client,fdimg,NULL,fsize("GET /1.png"));
		// close(fdimg);

		// }else if(!strncmp(buf,"GET /1.png",16)){

		// fdimg=open("1.png",O_RDONLY);
		// sendfile(fd_client,fdimg,NULL,fsize("1.png"));
		// close(fdimg);

		// }else{

		
		// //  write(fd_client,webpage,sizeof(webpage));
