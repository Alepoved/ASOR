#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile int count_int,count_tstp;

void handler(int signal){
	if (signal == SIGINT) count_int++;
	if (signal == SIGTSTP) count_tstp++;

}


int main(){

	struct sigaction act;

	sigaction(SIGINT,NULL,&act);
	act.sa_handler = handler;
	sigaction(SIGINT,&act,NULL);
	sigaction(SIGTSTP,NULL,&act);
	act.sa_handler = handler;
	sigaction(SIGTSTP,&act,NULL);

	sigset_t set;
	sigemptyset(&set);

	while(count_int + count_tstp < 5)
		sigsuspend(&set);

	printf("SIGINT captured: %i\n", count_int);
	printf("SIGTSTP captured: %i\n", count_tstp);
}
