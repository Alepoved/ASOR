#include <stdio.h>
#include <errno.h>
#include <stdlib.h> //exit

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

 #define BUF_SIZE 500


int main(int argc, char**argv){

	struct addrinfo hints;
           struct addrinfo *result, *rp;
           int sfd, s,cli_sd;
           struct sockaddr_storage peer_addr;
           socklen_t peer_addr_len;
           ssize_t nread;
           char buf[BUF_SIZE];
	     char host[NI_MAXHOST], service[NI_MAXSERV];
		ssize_t res;


           if (argc < 2) {
               fprintf(stderr, "Usage: %s port\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
           hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
           hints.ai_protocol = 0;          /* Any protocol */
           hints.ai_canonname = NULL;
           hints.ai_addr = NULL;
           hints.ai_next = NULL;

           s = getaddrinfo(argv[1], argv[2], &hints, &result);
           if (s != 0) {
               fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }

         
          
               sfd = socket(result->ai_family, result->ai_socktype,
                       result->ai_protocol);

               bind(sfd, result->ai_addr, result->ai_addrlen);

		listen(sfd,16);

		freeaddrinfo(result);         


           while (1) {
		cli_sd = accept(sfd,(struct sockaddr *)&peer_addr,&peer_addr_len);
		 s = getnameinfo((struct sockaddr *) &peer_addr,
                               peer_addr_len, host, NI_MAXHOST,
                               service, NI_MAXSERV, NI_NUMERICHOST);
		printf("Conexión desde %s:%s\n", host, service);
		
		while(1){
			 res = recv(cli_sd,buf,256,0);
			buf[res]='\0';
			printf("=>%s\n",buf);
			if(buf[0]=='Q'){break;}
			send(cli_sd,buf,res,0);
		}
             
           }

close(cli_sd);



return 0;

}
