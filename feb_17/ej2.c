#include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>

       int main(int argc, char *argv[])
       {
	int pipe_p[2],pipe_h[2],i;
	char buf_p[256],buf_h[256],flag = 'l',aux[2];
	pipe(pipe_p); pipe(pipe_h);

	switch(fork()){
	
	case 0:
		close(pipe_p[1]); close(pipe_h[0]);
		for(i = 0; i<4; i++){
			ssize_t leer = read(pipe_p[0],buf_h,256);
			buf_h[leer] = '\0';
			printf("HIJO=>%s\n",buf_h);
			sleep(1);
			if(i == 3) flag = 'q';
			write(pipe_h[1],&flag,1);			
		}

	break;
	
	default:
		close(pipe_p[0]); close(pipe_h[1]);
		while(1){
			ssize_t leer = read(0,buf_p,256);
			buf_p[leer] = '\0';
			printf("PADRE=>%s\n",buf_p);
			write(pipe_p[1],buf_p,256);
			leer = read(pipe_h[0],aux,1);
			aux[leer] ='\0';
			printf("listo(%s) \n",aux);
		}
		
		
	}
	
	return 0;

	}
