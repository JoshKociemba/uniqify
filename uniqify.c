/**
 * Author: Joshua Kociemba (kociembj), joshua.kociemba@oregonstate.edu
 * Created: 2013-11-12 19:44:48
 * Filename: uniqify.c
 *
 * Description: Practice sorting user input/file input using pipes
 **/

#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#define MAX_SPROCS 1000
#define WORD_SIZE 34

/**
 * Function Header
 **/
void forking_setup(int num_sprocs);

/**
 * Function Header
 **/
void parse_in(int num_sprocs, int fd_in);

/**
 * Function Header
 **/
void forked_sort(void);

/**
 * Function Header
 **/
void wr_out(void);

/**
 * Function Header
 **/
void usage(void);



int main(int argc, char **argv) {

	int num_sprocs, fd_in, fd_out;
	
	if (argv[1] == NULL || argv[2] == NULL) {
		usage();
	} else {
		num_sprocs = atoi(argv[1]);
		fd_in = open(argv[2], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP\
			       	| S_IROTH | S_IWOTH);
	}

	if (argv[3] != NULL) {
		fd_out = open(argv[3], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP\
			       	| S_IWGRP | S_IROTH | S_IWOTH);
	} else {
		printf("User input from terminal"); ///Fix this
	}

	if (num_sprocs > MAX_SPROCS) {
		perror("You chose too many sorting processes, slow down!\n");
		exit(-1);
	}

	forking_setup(num_sprocs);

	return 0;
}

void forking_setup(int num_sprocs) {
	
	int pid;
	
	for (int i = 0; i < num_sprocs; i++) {
		
		switch((pid = fork())) {
		
		case -1:
			printf("Couldn't fork a new child!\n");
			break;
		case 0:
			printf("Hello from child: %d\n", getpid());
			sleep(10);
			//child
			_exit(EXIT_SUCCESS);
			break;
		default:
			wait(NULL);
			printf("Hello from parent: %d\n", getpid());
			//parent
			exit(EXIT_SUCCESS);
			break;
		}

		printf("Done.");



	}

}

void parse_in(int num_sprocs, int fd_in) {
	int pipe_fds[num_sprocs];
	char word_buff[WORD_SIZE];
	char *last_word;
	char c;
	int j;

	if (pipe(pipe_fds) != 0) {
		perror("Them pipes are clogged again\n");
		exit(-1);
	}

	for (int i = 0; i < num_sprocs; i++) {
		pipe_fds[i] = fdopen(fd_in[i][1], "w");

		if (pipe_fds[i] == 0) {
			perror("Couldn't open the pipe");
			exit(-1);
		}
	}

	while (fgets(word_buff, WORD_SIZE, stdin) != NULL) {
		for (int i = 0; i < strlen(word_buff); i++) {
			if (isalpha(word_buff[i]) == 0) {
				word_buff[i] = ' ';
			} else {
				word_buff[i] = tolower(word_buff[i]);
			}

		}
		j = 0;
		last_word = strtok(word_buff, " ");
		while (last_word != NULL) {
			fputs(word_buff, pipe_fds[j]);
			last_word = strtok(NULL, " ");
			
			if (j == (num_sprocs - 1)) {
				j = 0;
			} else {
				j++;
			}
		}
	}






}

void forked_sort(void) {


}

void wr_out(void) {


}

void usage(void) {
	printf("Usage: ./uniqify [Number of Sort Processes] [Input File] [Output File]\n");
	printf("Number of Sort Processes [1 - 1000]\n");
	printf("Input File [.txt] Must Exist\n");
	printf("Output File [.txt] If not specified, an output file will be created\n");
	exit(-1);

}








