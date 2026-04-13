#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
	char command[200], new_command[200], env2[200], *token, *env;
	int pid, stat;
	env = getenv("PATH");
	
	while(true){
		printf("Please put your command: ");
		fgets(command, 200,stdin);
		command[strlen(command) -1] = 0;
		if (strcmp(command,"leave") == 0) break;

		pid = fork();
		if (pid == 0){
			token = strtok(env,":");
			while(token != NULL){
				strcpy(new_command,token);
				strcat(new_command,"/");
				strcat(new_command,command);
				token = strtok(NULL,":");
				char * arr[] = {new_command,NULL};
				execv(arr[0],arr);
			}
			char * arr[] = {command,NULL};
			execv(arr[0],arr);
			printf("No such command %s, please try a different command\n",command);
			exit(1);
		}
		else{
			wait(&stat);
		}
	}
}


