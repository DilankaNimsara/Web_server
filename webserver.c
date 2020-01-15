#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	
	struct sockaddr_in server_addr, client_addr;
	socklen_t sin_len= sizeof(client_addr);
	int fd_server,fd_client;
	int on=1;
	char msg[99999], *reqline[3], data_to_send[1024], path[99999];
    int received, fd, bytes_read;

	fd_server= socket(AF_INET,SOCK_STREAM,0);

	if(fd_server<0){
		perror("socket");
		exit(1);
	}

	setsockopt(fd_server,SOL_SOCKET, SO_REUSEADDR,&on,sizeof(int));

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(8081);

	if(bind(fd_server, (struct sockaddr *) &server_addr,sizeof(server_addr))==-1){
		perror("bind");
		close(fd_server);
		exit(1);
	}

	if(listen(fd_server,10)==-1){
		perror("listen");
		close(fd_server);
		exit(1);
	}

	while(1){

		fd_client=accept(fd_server,(struct sockaddr *) &client_addr,&sin_len);

		if(fd_client==-1){
			perror("connection faild");
			continue;
		}else{
			
			printf("got client connection \n");

			if(!fork()){

			received=recv(fd_client, msg, 99999, 0);

				if(received>0){
					printf("%s", msg);
					reqline[0] = strtok (msg, " \t\n");
					if ( strncmp(reqline[0], "GET\0", 4)==0 ){

						reqline[1] = strtok (NULL, " \t");

						if ( strncmp(reqline[1], "/\0", 2)==0 ){
							reqline[1] = "/index.html";     
						}

						strcpy(path, getenv("PWD"));
						strcpy(&path[strlen(getenv("PWD"))], reqline[1]);
						printf("file: %s\n", path);

						if ( (fd=open(path, O_RDONLY))!=-1 ){    //FILE FOUND
							send(fd_client, "HTTP/1.1 200 OK\n\n", 17, 0);
							while ( (bytes_read=read(fd, data_to_send, 1024))>0 ){
								write (fd_client, data_to_send, bytes_read);
							}
						}else{
							write(fd_client, "HTTP/1.1 404 Not Found\n", 23); //FILE NOT FOUND
						}   
					}
				}
			}

			close(fd_client);	
		
		} 
	}

	return 0;
}












