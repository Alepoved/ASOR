#include <stdio.h>
#include <errno.h>
#include <stdlib.h> //exit

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

 #define BUF_SIZE 500


void main(int argc, char**argv){

	struct addrinfo hints;
           struct addrinfo *result, *rp;
           int sfd, s;
           struct sockaddr_storage peer_addr;
           socklen_t peer_addr_len;
           ssize_t nread;
           char buf[BUF_SIZE];

           if (argc < 2) {
               fprintf(stderr, "Usage: %s port\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
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
                 

              
		freeaddrinfo(result);           /* No longer needed */

           /* Read datagrams and echo them back to sender */

           for (;;) {
               peer_addr_len = sizeof(struct sockaddr_storage);
               nread = recvfrom(sfd, buf, BUF_SIZE, 0,
                       (struct sockaddr *) &peer_addr, &peer_addr_len);
               if (nread == -1)
                   continue;               /* Ignore failed request */

               char host[NI_MAXHOST], service[NI_MAXSERV];

               s = getnameinfo((struct sockaddr *) &peer_addr,
                               peer_addr_len, host, NI_MAXHOST,
                               service, NI_MAXSERV, NI_NUMERICHOST);
              if (s == 0)
                   printf("Received %ld bytes from %s:%s\n",
                           (long) nread, host, service);
               else
                   fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

		printf("host:%s puerto:%s\n",host,service);

               sendto(sfd, host, strlen(host), 0,
                           (struct sockaddr *) &peer_addr,
                           peer_addr_len);
                   
           }

  

}
