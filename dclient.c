#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include<netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define PORT 13 /*well know port */
#define MAXDATASIZE 100 /*data buffer */
 
	int main (int argc,char* argv[])
{
	int sockfd,numbytes;
	char buf[MAXDATASIZE + 1];
	struct hostent* he;
	struct sockaddr_in their_addr;
if (argc != 2)
	{
		fprintf(stderr,"usage:client hostname\n");
		exit(1);
	}
if ((he =gethostbyname (argv[1])) ==NULL)
	{
		perror ("**gethostbyname");
		exit(1);
	}
if ((sockfd = socket (AF_INET, SOCK_STREAM ,0))==-1)
	{
		perror("socket");
		exit(1);
	}
	their_addr.sin_family= AF_INET;
	their_addr.sin_port= htons(PORT);
	their_addr.sin_addr= * ((struct in_addr*)he->h_addr);
	bzero(&(their_addr.sin_zero),8);
	if (connect (sockfd, (struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1)
	{
        	perror("connect");
	        exit(1);
	}
	while ((numbytes =read (sockfd, buf, MAXDATASIZE )) > 0)
	{
    	buf[numbytes]= 0;
    	if ( fputs(buf,stdout) == EOF)
	{     	
	perror("recv");
	exit(1);
	}
	buf[numbytes]='\0';
        printf("Todays date & time is:\n");        
	printf("recived: %s",buf);
        }
        close(sockfd);
	return 0;
 }


