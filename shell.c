#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//char * path = getenv();


int main(){
	char command[200], new_command[200], env2[200], *token, *env;
	int pid, stat;
	env = getenv("PATH");
	token = strtok(env,":");
	while(token != NULL){
		printf("the token is: %s\n",token);
		token = strtok(NULL,":");
	}
	while(true){
		printf("Please put your command: ");
		fgets(command, 200,stdin);
		command[strlen(command) -1] = 0;
		if (strcmp(command,"leave") == 0) break;

		pid = fork();
		if (pid == 0){
			execl(command,command,NULL);
			printf("No such command %s, please try a different command\n",command);
			exit(1);
		}
		else{
			wait(&stat);
		}
	}
}


