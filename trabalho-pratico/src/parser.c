/* parser.c
 Lê os ficheiros csv e realiza o parsing utilizando os módulos de dados e estatísticas
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parser.h"
#include"drivers.h"
#include"users.h"
#include"rides.h"
#include"stats.h"

#define MAX_PATH_SIZE 1024

void data_parser(char* path, Drivers drivers, Users users, Rides rides, Stats stats) {

	FILE* fp = NULL;
	char* drivers_path = (char*) malloc(MAX_PATH_SIZE * sizeof(char));
	char* users_path   = (char*) malloc(MAX_PATH_SIZE * sizeof(char));
	char* rides_path   = (char*) malloc(MAX_PATH_SIZE * sizeof(char));

	snprintf(drivers_path, MAX_PATH_SIZE, "%s/%s", path, "drivers.csv");
	snprintf(users_path,   MAX_PATH_SIZE, "%s/%s", path, "users.csv");
	snprintf(rides_path,   MAX_PATH_SIZE, "%s/%s", path, "rides.csv");

	fp = fopen(drivers_path, "r");
	if (!fp)
		perror("drivers.csv at parser.c");
	else
		parse_drivers(drivers_path, drivers, fp);
	fclose(fp);
	
	fp = fopen(users_path, "r");
	if (!fp)
		perror("users.csv at parser.c");
	else
		parse_users(users_path, users, fp);
	fclose(fp);

	fp = fopen(rides_path, "r");
	if (!fp)
		perror("rides.csv at parser.c");
	else
		parse_rides(rides_path, rides, drivers, users, stats, fp);
	fclose(fp);

	// Cálculo de estatísticas + sorting

	// Queries 1, 2
	calculate_med_score_drivers(drivers);
	sort_drivers_med_score(drivers, rides, stats);
	// Queries 1, 3
	calculate_med_score_users(users);
	sort_users_distance(users, rides, stats);
	// Query 7
	sort_drivers_avaliation(drivers, rides, stats);
	// Query 8
	sort_rides_male_age(rides);
	sort_rides_female_age(rides);
	//Query 9
	sort_tip_rides(rides,stats);
	free(drivers_path); free(users_path); free(rides_path);
}
