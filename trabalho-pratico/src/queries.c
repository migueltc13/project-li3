#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"queries.h"
#include"driver.h"
#include"drivers.h"
#include"user.h"
#include"users.h"
#include"ride.h"
#include"rides.h"
#include"stats.h"
#include"date.h"
#include"cities.h"
#include"city.h"
#include"valid.h"

char* query1(char* token, Drivers ds, Users us, Rides rs, int n) {

	char* result = (char*) calloc(MAX_SIZE_OUTPUT, sizeof(char));

	Driver d = init_empty_driver();
	User u = init_empty_user();

	if (is_id(token) == 0) {

		if (get_driver_by_id(ds, atoi(token))) {
			d = get_driver_by_id(ds, atoi(token));
			if (is_driver_active(d))
			snprintf(result,MAX_SIZE_OUTPUT,"%s;%c;%d;%.3f;%d;%.3f\n",
				get_driver_name(d),
				get_driver_gender(d),
				get_driver_age(d),
				get_driver_med_score(d),
				get_driver_nr_rides(d),
				get_total_made(d));
		}
		else strcpy(result, "");
	}
	else {
		if (get_user_by_username(us, token)) {
			u = get_user_by_username(us, token);
		
			if (is_user_active(u))
				snprintf(result,MAX_SIZE_OUTPUT,"%s;%c;%d;%.3f;%d;%.3f\n",
					get_name(u),
					get_gender(u),
					get_user_age(u),
					get_user_med_score(u),
					get_user_nr_rides(u),
					get_total_spent(u));
		}
		else strcpy(result, "");
	}
	return result;
}


char* query2(char* token_line, Stats stats, int n){
	
	char* token = (char*) malloc(sizeof(char) * MAX_SIZE_OUTPUT);
	sscanf(token_line, "%s\n", token);
	int N = atoi(token_line);

	char* result = (char*) calloc(MAX_SIZE_OUTPUT * N, sizeof(char));
	char* aux    = (char*) calloc(MAX_SIZE_OUTPUT, sizeof(char));

	Driver* ds = get_sorted_drivers_med_score(stats);

	int max = get_nr_drivers_stats(stats) - 1;
	for (int i=max; i>max-N && i>0; i--) {
		if (is_driver_active(ds[i])) {
			sprintf(aux, "%012d;%s;%.3f\n", get_driver_id(ds[i]), get_driver_name(ds[i]), get_driver_med_score(ds[i]));
			strcat(result, aux);
		}
	}
	free(token); free(aux);
	return result;
}


char* query3(char* token_line, Stats stats, int n) {

	char* token = (char*) malloc(sizeof(char) * MAX_SIZE_OUTPUT);
	sscanf(token_line, "%s\n", token);
	int N = atoi(token_line);

	char* result = (char*) calloc(MAX_SIZE_OUTPUT * N, sizeof(char));
	char* aux    = (char*) calloc(MAX_SIZE_OUTPUT, sizeof(char));

	User* us = get_sorted_users_distance(stats);

	int max = get_nr_users_stats(stats) - 1;
	for (int i=max; i>max-N && i>0; i--) {
		if (is_user_active(us[i])) {
			sprintf(aux, "%s;%s;%d\n", get_username(us[i]), get_name(us[i]), get_total_distance(us[i]));
			strcat(result, aux);
		}
	}
	free(token); free(aux);
	return result;
}


char* query4(char* token_line, Stats stats, int n) {

	char* city_name = strsep(&token_line,"\n");
	char* result = (char*) calloc(MAX_SIZE_OUTPUT, sizeof(char));
	Cities cs = get_cities_stats(stats);
	double med_price = get_med_price_by_city(cs, city_name);

	if (med_price == -1) {
		strcpy(result, "");
		return result;
	}

	sprintf(result, "%.3f\n", med_price);
	return result;
}


char* query5(char* token_line, Drivers ds, Rides rs, int n) {

	char* result	= (char*) calloc(MAX_SIZE_OUTPUT, sizeof(char));
	char* dataA_aux	= (char*) calloc(SIZE_DATE, sizeof(char));
	char* dataB_aux	= (char*) calloc(SIZE_DATE, sizeof(char));
	Date date_ride	= init_date();

	int nr_rides = 0;
	double total_price = 0;

	sscanf(token_line, "%s %s\n", dataA_aux, dataB_aux);
	Date dataA = string_to_date(dataA_aux);
	Date dataB = string_to_date(dataB_aux);

	GHashTable* rides = get_rides(rs);

	GHashTableIter iter;
	g_hash_table_iter_init(&iter, rides);
	void *val = NULL;

	while(g_hash_table_iter_next(&iter, NULL, &val)) {
		Ride r = (Ride) val;
	        date_ride = get_ride_date(r);

	        if ((compare_date(date_ride,dataA) != 2) && (compare_date(date_ride,dataB) != 1)) {
	                int driver_id = get_ride_driver(r);
	                char car_class = get_driver_car_class(get_driver_by_id(ds, driver_id));
	                total_price += calculate_ride_price(r, car_class);
	                nr_rides++;
	        }
	}
	if (nr_rides == 0) {
		strcpy(result, "");
		return result;
	}
	double price_med = total_price / nr_rides;
	snprintf(result, MAX_SIZE_OUTPUT, "%.3f\n", price_med);
	free(dataA_aux); free(dataB_aux); // free_date(date_ride);
	return result;	
}


char* query6(char* token_line, Rides rs, int n) {

	char* result	= (char*) calloc(MAX_SIZE_OUTPUT, sizeof(char));
	char* city	= (char*) malloc(sizeof(char));
	char* dataA_aux	= (char*) calloc(SIZE_DATE, sizeof(char));
	char* dataB_aux	= (char*) calloc(SIZE_DATE, sizeof(char));
	Date date_ride	= init_date();

	int nr_rides = 0;
	double distancia_total = 0, dist_media = 0;
	char* ride_city = NULL;

	sscanf(token_line, "%s %s %s\n", city, dataA_aux, dataB_aux);
	Date dataA = string_to_date(dataA_aux);
	Date dataB = string_to_date(dataB_aux);

	GHashTable* rides = get_rides(rs);

	GHashTableIter iter;
	g_hash_table_iter_init(&iter, rides);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val)) {
		Ride r = (Ride) val;
	        date_ride = get_ride_date(r);
	        ride_city = get_ride_city(r);
	        if ((strcmp(city, ride_city) == 0) && (compare_date(date_ride,dataA) != 2) && (compare_date(date_ride,dataB) != 1)) { 
	                distancia_total += get_ride_distance(r);
	                nr_rides++;
	        }
	}
	if (nr_rides == 0) {
		strcpy(result, "");
		return result;
	}
	dist_media = distancia_total / nr_rides;
	snprintf(result, MAX_SIZE_OUTPUT, "%.3f\n", dist_media);
	free(city); free(dataA_aux); free(dataB_aux); free(ride_city);
	return result;
}

char* query7(char* token_line, Stats stats, Drivers ds, int n) {

	int c=1;
	char* city	= (char*) malloc(sizeof(char));
	sscanf(token_line, "%d %s\n",&c ,city);
	char* result	= (char*) calloc(100 * c, sizeof(char));
	char* aux       = (char*) calloc(100, sizeof(char));
	
	char* driver_name = NULL;

	Cities cities_struct = get_cities_stats(stats);

	City city_struct = NULL;
	if (g_hash_table_lookup(get_city_table(cities_struct), city))
		city_struct = (City) g_hash_table_lookup(get_city_table(cities_struct), city);
	else {
		strcpy(result, "");
		return result;
	}

	Driver_aval* drivers = get_all_city_driver_aval(city_struct);
	int nr_drivers = get_nr_drivers_city(city_struct);

	for (int i=0; i<c && i<nr_drivers; i++) { // j<c || j<nr
		Driver_aval driver = drivers[i];
		int id_driver_aval = get_driver_aval_id(driver);
		char* driver_name = get_driver_name(get_driver_by_id(ds,id_driver_aval));
		sprintf(aux, "%012d;%s;%.3f\n", id_driver_aval, driver_name, get_aval_driver(driver));
		strcat(result, aux);
	}
	
	free(driver_name); free(city); free(aux);
	return result;
}

char* query8(char* token_line, Rides rides, int n) {
	char* gender = (char*) malloc (sizeof(char));
	char* X_aux  = (char*) malloc (sizeof(char) * 10);
	sscanf(token_line, "%s %s\n", gender, X_aux);
	int X = atoi(X_aux);

	int nr_females = get_nr_female_rides(rides);
	int nr_males = get_nr_male_rides(rides);

	char* result = (char*) malloc(sizeof(char) * MAX_SIZE_OUTPUT * 
		(nr_females > nr_males ? nr_females : nr_males)); // TODO dynamic memory
	char* aux    = (char*) malloc(sizeof(char) * MAX_SIZE_OUTPUT);

	Date date_driver = init_date();
	Date date_user = init_date();

	if (gender[0] == 'F') {
		Ride* females = get_female_rides(rides);
		for (int i=0; i<nr_females; i++) {
			date_driver = get_ride_account_creation_driver(females[i]);
			date_user = get_ride_account_creation_user(females[i]);
			if (calculate_age(date_driver) >= X &&
				calculate_age(date_user) >= X) {
			snprintf(aux,MAX_SIZE_OUTPUT,"%012d;%s;%s;%s\n",
					get_ride_driver(females[i]),
					get_ride_driver_name(females[i]),
					get_ride_user(females[i]),
					get_ride_user_name(females[i]));
				strcat(result, aux);
			}
		}
	}
	if (gender[0] == 'M') {
		Ride* males = get_male_rides(rides);
		for (int i=0; i<nr_males; i++) {
			date_driver = get_ride_account_creation_driver(males[i]);
			date_user = get_ride_account_creation_user(males[i]);
			if (calculate_age(date_driver) >= X &&
				calculate_age(date_user) >= X) {
				snprintf(aux,MAX_SIZE_OUTPUT,"%012d;%s;%s;%s\n",
					get_ride_driver(males[i]),
					get_ride_driver_name(males[i]),
					get_ride_user(males[i]),
					get_ride_user_name(males[i]));
				strcat(result, aux);
			}
		}
	}
	//free_date(date_driver); free_date(date_user);
	free(gender); free(X_aux); free(aux);
	return result;
}


char* query9(char* token_line, Stats stats, int n) {

	Ride* rides = get_sorted_tip_rides_stats (stats);
	int nr_rides = get_sorted_tip_nr_rides(stats);

	char* result	= (char*) calloc(50 * nr_rides, sizeof(char));
	char* dataA_aux	= (char*) calloc(SIZE_DATE, sizeof(char));
	char* dataB_aux	= (char*) calloc(SIZE_DATE, sizeof(char));
	char* aux       = (char*) calloc(MAX_SIZE_OUTPUT, sizeof(char));

	sscanf(token_line, "%s %s\n", dataA_aux, dataB_aux);
	Date dataA = string_to_date(dataA_aux);
	Date dataB = string_to_date(dataB_aux);
	Date date_ride	= init_date();

	for(int i = 0; i < nr_rides; i++) {
		Ride r = rides[i];
	        date_ride = get_ride_date(r);

	        if ((compare_date(date_ride,dataA) != 2) && (compare_date(date_ride,dataB) != 1)) { 
	                sprintf(aux, "%012d;%s;%d;%s;%.3f\n", get_ride_id(r), date_to_string(date_ride), get_ride_distance(r), get_ride_city(r), get_ride_tip(r));
			strcat(result, aux);
	        }
	}

	free(dataA_aux); free(dataB_aux); free(aux);
	free_date(dataA); free_date(dataB); // free_date(date_ride);
	return result;
}
