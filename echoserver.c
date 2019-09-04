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
#define MAXLINE 100
void  str_echo(int sockfd)
{
     int  n,i;
     char line[MAXLINE];
for ( ; ; )
  {
	for(i=0;i<100;i++)
 		line[i]='\0';
	  if((n=read(sockfd,line,MAXLINE)) ==0)
          return;
          write(sockfd,line,n);
	  printf ("client line was:  %s\n", line);
   }
}
main()
{
int sockfd , new_fd ; /* listen on sock_fd ,new connection on new_fd */
struct sockaddr_in my_addr; /* my address */
struct sockaddr_in their_addr; 
int clilen;
int childpid;
if ((sockfd = socket (AF_INET, SOCK_STREAM ,0))==-1)
{
perror("soket");
exit(1);
}
my_addr.sin_family= AF_INET;
my_addr.sin_port= htons(MYPORT);
my_addr.sin_addr.s_addr= htonl(INADDR_ANY);
bzero(&(my_addr.sin_zero),8);
if (bind(sockfd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1){
perror("bind");
exit(1);
}
if(listen(sockfd,BACKLOG) == -1) {
perror("listen");
exit(1);
}
for( ; ; )
{
clilen =  sizeof(their_addr);
if ((new_fd =accept(sockfd, (struct sockaddr*)&their_addr,&clilen)) == -1)
{
perror("accept");
continue;
}
	if ( ( childpid = fork() ) == 0)
	{
		close(sockfd);
		str_echo(new_fd);
                exit(0);
	}
	close(new_fd);	
   }
}
  

