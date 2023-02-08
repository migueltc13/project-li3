#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stats.h"
#include"user.h"
#include"users.h"
#include"driver.h"
#include"drivers.h"
#include"ride.h"
#include"rides.h"
#include"date.h"
#include"city.h"
#include"cities.h"

struct stats {
	// Query 2
	Driver* sorted_drivers_med_score;
	int nr_drivers;
	
	// Query 3
	User* sorted_users_distance;
	int nr_users;
	
	// Queries 4,7
	Cities cs;
	
	// Querie 9
	Ride* sorted_tip_rides;
	int nr_tip_rides;
};

Stats init_stats() {
	// TODO
	Stats s = (Stats) malloc(sizeof(struct stats));
	s->sorted_tip_rides = (Ride*) malloc(sizeof(Ride));
	s->nr_tip_rides=0;	
	//active_users = 0;
	//active_drivers = 0;
	//s->sorted_unames_distance = (char**) malloc(sizeof(struct))
	/*
	s->nr_cities = 0;
	s->city_names = (char**) malloc(NR_CITIES * sizeof(char*));
	for (int i=0; i<NR_CITIES; i++)
		s->city_names[i] = (char*) malloc(SIZE_CITY * sizeof(char));
	s->city_nr_rides = (int*) malloc(NR_CITIES * sizeof(int));
	*/
	return s;
}

void free_stats(Stats s) {
	free(s->sorted_drivers_med_score);
	free(s->sorted_users_distance);
	free(s->sorted_tip_rides);
	s->nr_drivers = 0;
	s->nr_users = 0;
	s->nr_tip_rides = 0;
	free_cities(s->cs);
	free(s);
}

Driver* get_sorted_drivers_med_score(Stats s) {
	Driver* ds = s->sorted_drivers_med_score;
	return ds;
}

int get_nr_drivers_stats(Stats s) {
	int n = s->nr_drivers;
	return n;
}

User* get_sorted_users_distance(Stats s) {
	User* us = s->sorted_users_distance;
	return us;
}

int get_nr_users_stats(Stats s) {
	int n = s->nr_users;
	return n;
}

void insert_cities_stats(Stats s, Cities cs) {
	s->cs = cs;
} 

Cities get_cities_stats(Stats s) {
	Cities cs = s->cs;
	return cs;
}

void insert_rides_tip_stats(Stats stats, Ride store_ride){
	stats->sorted_tip_rides = (Ride*) realloc(stats->sorted_tip_rides, sizeof(Ride) * (stats->nr_tip_rides+1)); 
	stats->sorted_tip_rides[stats->nr_tip_rides] = store_ride;	
	(stats->nr_tip_rides)++;
}

Ride* get_sorted_tip_rides_stats(Stats s) {
	return s->sorted_tip_rides;
}

int get_sorted_tip_nr_rides(Stats s) {
	return s->nr_tip_rides;
}

void swap_users(User* u1, User* u2) {
	User t = *u1;
	*u1 = *u2;
	*u2 = t;
}

void swap_drivers(Driver* d1, Driver* d2) {
	Driver t = *d1;
	*d1 = *d2;
	*d2 = t;
}

void swap_rides(Ride* r1, Ride* r2) {
	Ride t = *r1;
	*r1 = *r2;
	*r2 = t;	
}

void swap_drivers_aval(Driver_aval* d1, Driver_aval* d2) {
	Driver_aval t = *d1;
	*d1 = *d2;
	*d2 = t;
}

int partition_q2(void* arr, void* rides, int low, int high) {

	Driver* drivers = (Driver*) arr;
	Driver d = drivers[high];
	double pivot = get_driver_med_score(d);
	int r_id = get_most_recent_ride_id_driver(d);
	if (r_id == 0)
		return -1; // TODO driver with no rides 
	
	Ride r = get_ride_by_id((Rides) rides, r_id);
	Date pivot_date = get_ride_date(r);
	int pivot_id = get_driver_id(d);

	int i = low - 1;
	for (int j = low; j < high; j++) {
		double med_score = get_driver_med_score(drivers[j]);

		if (med_score < pivot) {
			i++; swap_drivers(&drivers[i], &drivers[j]);
		}

		if (med_score == pivot) {
			int j_id = get_most_recent_ride_id_driver(drivers[j]);
			if (j_id != 0 && r_id != 0) {
				Date date = get_ride_date(get_ride_by_id((Rides) rides, j_id));
				if (compare_date(date, pivot_date) == 2) {
					i++; swap_drivers(&drivers[i], &drivers[j]);
				}

				if (compare_date(date, pivot_date) == 0) {

					if (get_driver_id(drivers[j]) <= pivot_id) {
						i++; swap_drivers(&drivers[i], &drivers[j]);
					}
				}
			}
			else {
				if (get_driver_id(drivers[j]) <= pivot_id) {
					i++; swap_drivers(&drivers[i], &drivers[j]);
				}
			}
		}
	}
	swap_drivers(&drivers[i+1], &drivers[high]);
	return i+1;
}

int partition_q3(void* arr, void* rides, int low, int high) {

	User* users = (User*) arr;
	User u = users[high];
	int pivot = get_total_distance(u);
	int r_id = get_most_recent_ride_id(u);
	if (r_id == 0)
		return -1; // TODO user with no rides 

	Ride r = get_ride_by_id((Rides) rides, r_id);
	Date pivot_date = get_ride_date(r);
	char* pivot_uname = get_username(u);
	char* uname = NULL;

	int i = low - 1;
	for (int j = low; j < high; j++) {
		int total_distance = get_total_distance(users[j]);

		if (total_distance < pivot) {
			i++; swap_users(&users[i], &users[j]);
		}

		if (total_distance == pivot) {
			int j_id = get_most_recent_ride_id(users[j]);
			if (j_id != 0 && r_id != 0) {
				Date date = get_ride_date(get_ride_by_id((Rides) rides, j_id));
				if (compare_date(date, pivot_date) == 1) {
					i++; swap_users(&users[i], &users[j]);
				}

				if (compare_date(date, pivot_date) == 0) {
					uname = get_username(users[j]);
					if (strcmp(uname, pivot_uname) <= 0) {
						i++; swap_users(&users[i], &users[j]);
					}
				}
			}
			else {
				uname = get_username(users[j]);
				if (strcmp(uname, pivot_uname) <= 0) {
					i++; swap_users(&users[i], &users[j]);
				}
			}
		}
	}
	swap_users(&users[i+1], &users[high]);
	
	free(pivot_uname); free(uname);
	return i+1;
}

int partition_q7(void* ds, void* null, int low, int high) {

	Driver_aval* drivers = (Driver_aval*) ds;
	Driver_aval d_a = drivers[high];

	double pivot_driver = get_aval_driver(d_a);
	int pivot_id = get_driver_aval_id(d_a);

	int i = low - 1;
	for (int j = low; j < high; j++) {
		double driver_aval = get_aval_driver(drivers[j]);

		if (driver_aval>pivot_driver) {
			i++; swap_drivers_aval(&drivers[i], &drivers[j]);
		}

		if (driver_aval == pivot_driver) {
			int driver_id = get_driver_aval_id(drivers[j]);
			if(driver_id > pivot_id){
				i++; swap_drivers_aval(&drivers[i], &drivers[j]);
			}
		}
	}
	swap_drivers_aval(&drivers[i+1], &drivers[high]);
	return i+1;
}

int partition_q8(void* rs, void* null, int low, int high) {

	Ride* rides = (Ride*) rs;
	Ride r = rides[high];

	Date pivot_driver = get_ride_account_creation_driver(r);
	Date date_driver = NULL;

	Date pivot_user = get_ride_account_creation_user(r);
	Date date_user = NULL;
	
	int pivot_id = get_ride_id(r);

	int i = low - 1;
	for (int j = low; j < high; j++) {
		date_driver = get_ride_account_creation_driver(rides[j]);

		if (compare_date(date_driver,pivot_driver) == 2) {
			i++; swap_rides(&rides[i], &rides[j]);
		}

		if (compare_date(date_driver,pivot_driver) == 0) {
			date_user = get_ride_account_creation_user(rides[j]);
			if (compare_date(date_user, pivot_user) == 2) {
				i++; swap_rides(&rides[i], &rides[j]);
			}

			if (compare_date(date_user, pivot_user) == 0) {
				if (get_ride_id(rides[j]) - pivot_id <= 0) {
					i++; swap_rides(&rides[i], &rides[j]);
				}
			}
		}
	}
	//free_date(date_driver); free_date(date_user);
	//free_date(pivot_driver); free_date(pivot_user);
	swap_rides(&rides[i+1], &rides[high]);
	return i+1;
}

void quicksort(void* arr, void* rides, int low, int high, int (*partitionFunc)(void* arr, void* rides, int low, int high)) {
	if (low < high) {
		int i = partitionFunc(arr, (Rides) rides, low, high);
		if (i != -1) {
			quicksort(arr, (Rides) rides, low, i-1, partitionFunc);
			quicksort(arr, (Rides) rides, i+1, high, partitionFunc);
		}
	}
}

// Query 2
void sort_drivers_med_score(Drivers ds, Rides rides, Stats s) {
	int n = get_nr_drivers(ds);

	Driver* drivers = get_all_drivers(ds);
	quicksort(drivers, rides, 0, n-1, partition_q2);

	s->sorted_drivers_med_score = drivers;
	s->nr_drivers = get_nr_drivers(ds);
}

// Query 3
void sort_users_distance(Users us, Rides rides, Stats s) {
	int n = get_nr_users(us);
	User* users = get_all_users(us);
	quicksort(users, rides, 0, n-1, partition_q3);
	/*
	for (int i=0; users[i]; i++) {
		printf("%d:",i); print_user(users[i]);
	}
	*/
	s->sorted_users_distance = users;
	s->nr_users = get_nr_users(us); // TODO use struct users instead
}

// Query 7
int compare_driver_aval(const void *ptr1, const void *ptr2){
	Driver_aval driver1 = (Driver_aval) ptr1;
	Driver_aval driver2 = (Driver_aval) ptr2;
	if(get_aval_driver(driver1)>get_aval_driver(driver2)) return -1;
	else if(get_aval_driver(driver1)<get_aval_driver(driver2)) return 1;

	if ((get_driver_aval_id(driver1)) > (get_driver_aval_id(driver2))) return -1;
	return 1;   
}

void sort_drivers_avaliation(Drivers drivers, Rides rs, Stats stats) {
	City* list_cities = get_all_cities(get_cities_stats(stats));
	int m = get_nr_cities(get_cities_stats(stats));

	for (int y = 0; y<m ; y++){
		Driver_aval* drivers = get_all_city_driver_aval(list_cities[y]);
		int nr_drivers = get_nr_drivers_city(list_cities[y]);
		quicksort(drivers, NULL, 0, nr_drivers-1, partition_q7);
		list_cities[y] = insert_Drivers_aval_in_city(drivers, list_cities[y]);
		stats->cs = update_cities(stats->cs, list_cities[y], y);
	}
}

// Query 8
void sort_rides_male_age(Rides rides) {
	int nr_males = get_nr_male_rides(rides);
	Ride* males = get_male_rides(rides);

	quicksort(males, NULL, 0, nr_males-1, partition_q8);

	insert_male_rides(rides, males);
}


void sort_rides_female_age(Rides rides) {

	int nr_females = get_nr_female_rides(rides);
	Ride* females = get_female_rides(rides);

	quicksort(females, NULL, 0, nr_females-1, partition_q8);

	/*for (int i=0; females[i] && i<nr_females; i++) {
		if (calculate_age(get_ride_account_creation_driver(females[i])) > 12 &&
			calculate_age(get_ride_account_creation_user(females[i])) > 12)
			printf("%s;%s;%012d;%012d;%s;%s;%s\n",
				date_to_string(get_ride_account_creation_driver(females[i])),
				date_to_string(get_ride_account_creation_user(females[i])),
				get_ride_id(females[i]),
				get_ride_driver(females[i]),
				get_ride_driver_name(females[i]),
				get_ride_user(females[i]),
				get_ride_user_name(females[i]));
	}*/
	insert_female_rides(rides, females);
}

// Query 9
Rides tip_rides_list(Rides rs) {
	
	Rides tip_rides = init_rides();
	tip_rides = copy_rides(rs);
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, get_rides(tip_rides));
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val)) {
		Ride r = (Ride) val;
		double tip_ride_temp = get_ride_tip(r);
	        if (tip_ride_temp == 0) {
			g_hash_table_remove(get_rides(tip_rides), GINT_TO_POINTER(get_ride_id(r)));
		}        
	}

	return tip_rides;
}

int compare_ride(const void * ptr1, const void * ptr2) {
	Ride *r1 = (Ride*) ptr1;
	Ride *r2 = (Ride*) ptr2;

	if (get_ride_distance(*r1) > get_ride_distance(*r2)) return -1;
	if (get_ride_distance(*r1) < get_ride_distance(*r2)) return 1;
	if (compare_date(get_ride_date(*r1),get_ride_date(*r2)) == 1) return -1;
	if (compare_date(get_ride_date(*r1),get_ride_date(*r2)) == 2) return 1;
	if (get_ride_id(*r1) > get_ride_id(*r2)) return -1;
	return 1;
	
}

Ride* array_ghash;
int *b;
void g_hash_to_array(gpointer key, gpointer value, gpointer user_data) {
	array_ghash[*b] = value;
	(*b)++;
}

void sort_tip_rides(Rides rides, Stats stats) {
	//usar o get tip rides e fazer uma duplicada
	b = malloc(sizeof(int));
	*b = stats->nr_tip_rides;
	qsort(stats->sorted_tip_rides,*b,sizeof(Ride) ,compare_ride);
	//stats->sorted_tip_rides = array_ghash;
	free(b);
}
