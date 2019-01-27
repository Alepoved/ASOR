#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){

	
	char *tub1 = "tuberia1";
	char *tub2 = "tuberia2";
	mkfifo(tub1,0644);
	mkfifo(tub2,0644);
	fd_set set;

	int pipe,pipe_num,buf[256];

	int fd1 = open(tub1, O_RDONLY | O_NONBLOCK);
	int fd2 = open(tub2, O_RDONLY | O_NONBLOCK);

	while(1){
		FD_ZERO(&set);
		FD_SET(fd1,&set);
		FD_SET(fd2,&set);

		int res = select((fd2>fd1)? fd2+1 : fd1,&set,NULL,NULL,NULL);

		if(FD_ISSET(fd1,&set)){
			pipe = fd1; pipe_num = 1; 
		}
		else if(FD_ISSET(fd2,&set)){
			pipe = fd2; pipe_num = 2;
		}

		ssize_t leer = 256;

		while(leer == 256){
			leer = read(pipe,buf,256);
			buf[leer] = '\0';
			printf("Tuberia[%i]=>%s\n",pipe_num,buf);		
		}

		if(pipe_num == 1){
			close(fd1); fd1 = open(tub1,O_RDONLY | O_NONBLOCK);		
		}
		else if(pipe_num == 2){
			close(fd2); fd2 = open(tub2,O_RDONLY | O_NONBLOCK);		
		}
	
	}


		

return 0;
           
}

