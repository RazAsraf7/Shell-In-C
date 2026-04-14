#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
	char command[200], new_command[200], env_copy[500], *token, *env;
	int pid, stat;
	env = getenv("PATH");
	
	while(true){
		printf("Please put your command: ");
		fgets(command, 200,stdin);
		command[strlen(command) -1] = 0;
		if (strcmp(command,"leave") == 0){
			printf("Goodbye\n");
			break;
		}
		else if (strcmp(command,"") == 0){
			printf("Error: Command cannot be empty\n");
			continue;
		}
		else if((command[0] == ' ') || (command[0] == '\t')){
			printf("Error: Whitespaces are not allowed at the start of the command\n");
			continue;
		}

		pid = fork();
		if (pid == 0){
			char * args[80];
			int i = 0;
			args[i] = strtok(command," ");
			while(args[i] != NULL){
				i++;
				args[i] = strtok(NULL," ");
			}
			if(env){
				strcpy(env_copy,env);
			}
			token = strtok(env_copy,":");
			while(token != NULL){
				strcpy(new_command,token);
				strcat(new_command,"/");
				strcat(new_command,args[0]);
				execv(new_command,args);
				token = strtok(NULL,":");

			}
			
			execv(args[0],args);
			printf("Error: No such command: %s\n",command);
			exit(1);
		}
		else{
			wait(&stat);
		}
	}
}


