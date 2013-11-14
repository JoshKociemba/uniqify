/**
 * Author: Joshua Kociemba (kociembj), joshua.kociemba@oregonstate.edu
 * Created: 2013-11-12 19:44:48
 * Filename: uniqify.c
 *
 * Description: Practice sorting user input/file input using pipes
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_SPROCS 1000
#define WORD_SIZE 34

/**
 * Function Header
 **/
void forking_setup(int num_sprocs);

/**
 * Function Header
 **/
void parse_in(int num_sprocs);

/**
 * Function Header
 **/
void forke_sort(void);

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
		FILE *input = fopen(argv[2], "w+");
		fd_in = open
	}

	if (argv[3] != NULL) {
		FILE *output = fopen(argv[3], "w+");
	} else {
		FILE *output = fopen("output", "w+");
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

void parse_in(int num_sprocs, FILE *input) {
	int pipe_fds[num_sprocs];

	if (pipe(pipefds) != 0) {
		perror("Them pipes are clogged again\n");
		exit(-1);
	}

	for (int i = 0; i < num_sprocs; i++) {
		

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








