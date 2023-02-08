#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include"user.h"
#include"users.h"
#include"driver.h"
#include"drivers.h"
#include"ride.h"
#include"rides.h"
#include"stats.h"
#include"date.h"
#include"cities.h"
#include"city.h"

struct rides {
	GHashTable* rides;
	int nr_rides;

	// query 7
	Ride* males;
	int nr_male_rides;
	
	Ride* females;
	int nr_female_rides;
};

Rides init_rides() {
	Rides rs = (Rides) malloc(sizeof(struct rides));
	rs->rides = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, free_ride);
	rs->nr_rides = 0;
	rs->males = (Ride*) malloc(sizeof(Ride));
	rs->nr_male_rides = 0;
	rs->females = (Ride*) malloc(sizeof(Ride));
	rs->nr_female_rides = 0;
	return rs;
}

void free_rides(void *ptr) {
	Rides rs = (Rides) ptr;
	g_hash_table_destroy(rs->rides);
	rs->nr_rides = 0;
	for (int i=0; i<rs->nr_male_rides; i++)
		free(rs->males[i]);
	for (int i=0; i<rs->nr_female_rides; i++)
		free(rs->females[i]);
	free(rs->males);
	rs->males = NULL;
	free(rs->females);
	rs->females = NULL;
	rs->nr_male_rides = 0;
	rs->nr_female_rides = 0;
	free(rs);
}

void insert_ride(Rides rs, Ride ride) {
	g_hash_table_insert(rs->rides, GINT_TO_POINTER(get_ride_id(ride)), ride);
	(rs->nr_rides)++;
}

GHashTable* get_rides(Rides rs) {
	return rs->rides;
}

Ride* get_all_rides(Rides rs) {
	
	int n = rs->nr_rides, i = 0;
	Ride* r = (Ride*) malloc(n * sizeof(Ride));
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, rs->rides);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val)){
		r[i] = (Ride) val;
		i++;
	}
	return r;
}

Rides copy_rides(Rides rs) {
	Rides rides = (Rides) malloc(sizeof(struct rides));
	memcpy(rides,rs,sizeof(struct rides));
	return rides;
}

int get_nr_rides(Rides rs) {
	int i = rs->nr_rides;
	return i;
}

Ride get_ride_by_id(Rides rs, int id) {
	Ride r = g_hash_table_lookup(rs->rides, GINT_TO_POINTER(id));
	return r;
}

int get_nr_male_rides(Rides rs) {
	int i = rs->nr_male_rides;
	return i;
}

int get_nr_female_rides(Rides rs) {
	int i = rs->nr_female_rides;
	return i;
}

Ride* get_male_rides(Rides rs) {
	Ride* ms = rs->males;
	return ms;
}

Ride* get_female_rides(Rides rs) {
	Ride* fs = rs->females;
	return fs;
}

void insert_male_rides(Rides rs, Ride* ms) {
	rs->males = ms;
}

void insert_female_rides(Rides rs, Ride* fs) {
	rs->females = fs;
}

void append_ride_by_gender(Rides rs, Ride r, Date d_driver, char* driver, Date d_user, char* user, char gender) {
	Ride new = create_partial_ride(r, d_driver, driver, d_user, user);
	if (gender == 'M') {
		rs->males = realloc(rs->males, sizeof(Ride) * (rs->nr_male_rides+1));
		rs->males[rs->nr_male_rides] = new;
		(rs->nr_male_rides)++;
	}
	else if (gender == 'F') {
		rs->females = realloc(rs->females, sizeof(Ride) * (rs->nr_female_rides+1));
		rs->females[rs->nr_female_rides] = new;
		(rs->nr_female_rides)++;
	}
}

void parse_rides(char* path, Rides rides, Drivers drivers, Users users, Stats stats, FILE* fp) {

	GHashTable* htable_users = get_htable_users(users);
	Cities cities = init_cities();

	char* buffer = NULL;
	//int line_count = 0; // para indicar quantas linhas nao foram validadas
	size_t bufsize = 0;
	ssize_t line_size;
	line_size = getline(&buffer, &bufsize, fp); // remove csv header
	while((line_size = getline(&buffer, &bufsize, fp)) >= 0)
		parse_ride(buffer, rides, drivers, users, stats, cities, htable_users);

	insert_cities_stats(stats, cities);
	printf("Number of rides parsed: %d\n", get_nr_rides(rides));
	free(buffer);

}

// Other functions
void print_rides(Rides rs) {
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, rs->rides);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val))
		print_ride((Ride) val);
}
