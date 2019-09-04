#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define MYPORT 13 /*well know port */
#define BACKLOG 10 /* how many pending connection queue will hold */
#define MAXLINE 200

int main(int argc, char **argv)
{
          int sockfd , new_fd ; /* listen on sock_fd ,new connection on new_fd */
	struct sockaddr_in my_addr; /* my address */
	struct sockaddr_in their_addr ;/* connector addr */
	char buff[MAXLINE];
	time_t ticks;
	int sin_size;
	if ( (sockfd = socket (AF_INET, SOCK_STREAM ,0))==-1)
	{
		perror("soket");
		exit(1);
	}
	my_addr.sin_family= AF_INET;
	my_addr.sin_port= htons(MYPORT);
	my_addr.sin_addr.s_addr= htonl(INADDR_ANY);
	bzero(&(my_addr.sin_zero),8);
	if (bind(sockfd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if(listen(sockfd,BACKLOG) == -1)
	 {
		perror("listen");
		exit(1);
	 }
	for( ; ;)
	{
		sin_size = sizeof(struct sockaddr_in);
   		new_fd =accept(sockfd, (struct sockaddr*)&their_addr,&sin_size) ;
		ticks = time(NULL);
printf("server: got connection from  %s  \n", 	inet_ntoa(their_addr.sin_addr));
                snprintf(buff, sizeof(buff),  "%.24s \r\n", ctime(&ticks));
                write(new_fd, buff, strlen(buff)); 
                close(new_fd);
	 }  
}
