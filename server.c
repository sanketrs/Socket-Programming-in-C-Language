#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define MYPORT 3490 /*well know port */
#define BACKLOG 10 /* how many pending connection queue will hold */

main()
{
	int sockfd , new_fd ; /* listen on sock_fd ,new connection on new_fd */
	struct sockaddr_in my_addr; /* my ip address */
	struct sockaddr_in their_addr ;/* connector client addr */
	int sin_size;  /* to get length of socket adress struct*/
	
/* 1)CREATE  SOCKET*/

	if ((sockfd = socket (AF_INET, SOCK_STREAM ,0))==-1)
		{
		perror("soket");
		exit(1);
		}
	my_addr.sin_family= AF_INET;
	my_addr.sin_port= htons(MYPORT);
	my_addr.sin_addr.s_addr= htonl(INADDR_ANY);
	bzero(&(my_addr.sin_zero),8);
	
/* 2)BIND  SOCKET*/
	if (bind(sockfd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
/* 3)LISTNING  SOCKET*/
	if(listen(sockfd,BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}

/* 4)ACCEPT CLIENT CONN*/
	while(1)
	{
	sin_size = sizeof(struct sockaddr_in);
	if ((new_fd =accept(sockfd, (struct sockaddr*)&their_addr,&sin_size)) == -1)
	{
		perror("accept");
		continue;
	}
	printf("server: got connection from %s\r\n", inet_ntoa(their_addr.sin_addr));
	
/* 5)SEND HELLO TO CLIENT*/

if (!fork())
	{ 
		if (write (new_fd,"\n hello ,world!  \n",14 )==-1)
  		perror("send");
		close(new_fd);
		exit(0);
	}
	close(new_fd);
   while(waitpid(-1,NULL,WNOHANG)> 0); /*time wait state*/
}
}
