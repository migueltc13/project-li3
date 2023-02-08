#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"interact.h"
#include"drivers.h"
#include"users.h"
#include"rides.h"
#include"stats.h"
#include"parser.h"
#include"handle.h"

void interact() {

	printf("Enter dataset path: ");
	
	char* buffer = NULL;
	int counter = 0;
	size_t bufsize = 0;
	ssize_t line_size;
	
	line_size = getline(&buffer, &bufsize, stdin);
	sscanf(buffer,"%s\n",buffer);

	Drivers ds = init_drivers();
	Users us = init_users();
	Rides rs = init_rides();
	Stats s = init_stats();

	data_parser(buffer, ds, us, rs, s);

	printf("$ ");
	while((line_size = getline(&buffer, &bufsize, stdin)) >= 0){
		counter++;
		handle(buffer, ds, us, rs, s, counter, 0); // interact mode != 1
		printf("$ ");
	}
	
	free(buffer); free_drivers(ds); free_users(us); free_rides(rs); free_stats(s);
	printf("\nExit with success\n");
}
