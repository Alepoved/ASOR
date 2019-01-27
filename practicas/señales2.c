#include <signal.h>
#include <stdlib.h>
#include <stdio.h>


int main(){

	sigset_t set;
	sigset_t pending;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGTSTP);
	sigprocmask(SIG_BLOCK,&set,NULL);
	int cont = 0;

	
	while(1){
		sigpending(&pending);
		if(sigismember(&pending,SIGINT) && cont == 0){
			printf("Recibido SIGINT\n");
			sigdelset(&set,SIGINT);	cont++;
		}
		else if(sigismember(&pending,SIGTSTP) && cont == 0){
			printf("Recibido SIGTSTP\n");
			sigdelset(&set,SIGTSTP);
		}
		
	}

	sigprocmask(SIG_UNBLOCK,&set,NULL);


return 0;

}
