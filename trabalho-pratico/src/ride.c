#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include"ride.h"
#include"rides.h"
#include"user.h"
#include"users.h"
#include"driver.h"
#include"drivers.h"
#include"stats.h"
#include"city.h"
#include"cities.h"
#include"date.h"
#include"valid.h"

#define REGEX_RIDE "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]"

struct ride {
	unsigned int id;
	Date date;
	unsigned int driver;
	char* user;
	char* city;
	unsigned int distance;
	unsigned int score_user;
	unsigned int score_driver;
	double tip;
	//char* comment;
	double price;

	// query 7
	Date account_creation_user;
	Date account_creation_driver;
	char* user_name;
	char* driver_name;
};

Ride init_ride(
	int id,
	Date date,
	int driver,
	char* user,
	char* city,
	int distance,
	int score_user,
	int score_driver,
	double tip)
{
	//int aux_id = id;
	//int aux_driver = driver;
	//int aux_distance = distance;
	//double aux_score_user = score_user;
	//double aux_score_driver = score_driver;
	//double aux_tip = tip;
	Ride r = (Ride) malloc(sizeof(struct ride));
	r->id		= id;
	r->date		= copy_date(date);
	r->driver	= driver;
	r->user		= strdup(user);
	r->city		= strdup(city);
	r->distance	= distance;
	r->score_user	= score_user;
	r->score_driver	= score_driver;
	r->tip		= tip;
	return r;
}

Ride create_partial_ride(Ride r, Date d_driver, char* driver, Date d_user, char* user) {
	Ride res = (Ride) malloc(sizeof(struct ride));
	res->id	    = r->id; // free
	res->user   = r->user;
	res->driver = r->driver;
	res->account_creation_user   = d_user;   // free
	res->account_creation_driver = d_driver; // free
	res->user_name = user;
	res->driver_name = driver;
	return res;
}

void free_ride(void *ptr) {
	Ride r = (Ride) ptr;
	free_date(r->date);
	free(r->user);
	free(r->city);
	r->id		= 0;
	r->driver	= 0;
	r->distance	= 0;
	r->score_user	= 0;
	r->score_driver	= 0;
	r->tip		= 0;
	free(r);
}

void parse_ride(char* buffer, Rides rides, Drivers drivers, Users users, Stats stats, Cities cities, GHashTable* htable_users) {

	Ride store_ride = NULL;

	char* aux = buffer;
	char* temp_id		= strsep(&aux,";");
	Date date		= parse_date(strsep(&aux,";"));
	char* temp_driver	= strsep(&aux,";");
	char* user		= strsep(&aux,";");
	char* city		= strsep(&aux,";");
	char* temp_distance	= strsep(&aux,";");
	char* temp_score_user	= strsep(&aux,";");
	char* temp_score_driver	= strsep(&aux,";");
	char* temp_tip 		= strsep(&aux,";");
	strsep(&aux,"\n"); // comment

	int valid = 1;

	// Data validation
	if (strlen(temp_id) == 0 || strlen(temp_driver) == 0 || strlen(user) == 0 || strlen(city) == 0
		|| is_valid_date(date) != 0 || is_valid_int(temp_distance) != 0
		|| is_valid_int(temp_score_user) != 0 || is_valid_int(temp_score_driver) != 0
		|| is_valid_double(temp_tip) != 0) 
		valid = 0;

	if (valid) {
		int id = atoi(temp_id);
		int driver = atoi(temp_driver);
		int distance = atoi(temp_distance);
		int score_user = atoi(temp_score_user);
		int score_driver = atoi(temp_score_driver);
		double tip = atof(temp_tip);

		store_ride = init_ride(id,date,driver,user,city,distance,score_user,score_driver,tip);

		Driver d = get_driver_by_id(drivers, driver);
		User u = g_hash_table_lookup(htable_users, get_ride_user(store_ride));

		// Calculate ride price
		char car_class = get_driver_car_class(d);
		double price = calculate_ride_price(store_ride, car_class);
		insert_ride_price(store_ride, price);

		// Q1 Calculate total_price_tip
		add_total_spent(u, price, tip);
		add_total_made(d, price, tip);

		// Q1 Calculate med score
		add_user_score(u, score_user); // Q2
		add_driver_score(d, score_driver);

		// Q3 Calculate total distance (users)
		add_total_distance(u, distance);

		// Q4 Calculate med price for each city + Q7 add driver
		City city_struct = insert_city(cities, city, price, d);

		// Q8 Parse male/female rides
		if (get_gender(u) == get_driver_gender(d) && is_user_active(u) && is_driver_active(d)) {
			append_ride_by_gender(rides, store_ride,
				get_driver_account_creation(d),
				get_driver_name(d),
				get_account_creation(u),
				get_name(u),
				get_gender(u));
		}

		// Calculate most recent ride for user -> TODO OPTIMIZE
		int recent_ride_id = get_most_recent_ride_id(u);
		if (recent_ride_id == 0)
			insert_most_recent_ride_id(u,id);
		else {
			Ride recent_ride = get_ride_by_id(rides, recent_ride_id);
			Date date2 = get_ride_date(recent_ride);
			if (compare_date(date, date2) == 1)
				insert_most_recent_ride_id(u,recent_ride_id);
		}

		// Calculate most recent ride for driver -> TODO OPTIMIZE
		recent_ride_id = get_most_recent_ride_id_driver(d);
		if (recent_ride_id == 0)
			insert_most_recent_ride_id_driver(d,id);
		else {
			Ride recent_ride = get_ride_by_id(rides, recent_ride_id);
			Date date2 = get_ride_date(recent_ride);
			if (compare_date(date, date2) == 1)
				insert_most_recent_ride_id_driver(d,recent_ride_id);
		}

		//Q7
		if (is_driver_active(d))
			insert_driver_aval(city_struct, driver, score_driver);

		//Q9
		double tip_ride_temp = get_ride_tip(store_ride);
        	if (tip_ride_temp != 0) {
			insert_rides_tip_stats(stats, store_ride);
		}
		insert_ride(rides, store_ride);

		//print_ride(store_ride);
		/* or */
		//print_ride(get_ride_by_id(rides, id));
	}
	free_date(date);
	//score_user = 0; score_driver = 0; tip = 0;
	//free(user); free(city);
}

int get_ride_id(Ride r) {
	int n = r->id;
	return n;
}

Date get_ride_date(Ride r) {
	return r->date;
}

int get_ride_driver(Ride r) {
	int n = r->driver;
	return n;
}

char* get_ride_user(Ride r) {
	return strdup(r->user);
}

char* get_ride_city(Ride r) {
	return strdup(r->city);
}

int get_ride_distance(Ride r) {
	int n = r->distance;
	return n;
}

int get_ride_score_user(Ride r) {
	int s = r->score_user;
	return s;
}

int get_ride_score_driver(Ride r) {
	int s = r->score_driver;
	return s;
}

double get_ride_tip(Ride r) {
	double res = r->tip;
	return res;
}

double get_ride_price(Ride r) {
	double f = r->price;
	return f;
}

void insert_ride_price(Ride r, double f) {
	r->price = f;
}

double calculate_ride_price(Ride r, char car_class) {
	
	int distance = r->distance;
	double price = 0;
	
	if (car_class == 'b') {
		price = 3.25 + (0.62 * distance);
	}
	else if (car_class == 'g') {
		price = 4.00 + (0.79 * distance);
	}
	else price = 5.20 + (0.94 * distance); // car_class = 'p'
	return price;
}

// TODO DUVIDA
Ride copy_ride(Ride r) {
	Ride res = (Ride) malloc(sizeof(struct ride));
	//memcpy(res,r,sizeof(struct ride));
	//int aux_id = r->id;
	//int aux_driver = r->driver;
	//int aux_distance = r->distance;
	//double aux_score_user = r->score_user;
	//double aux_score_driver = r->score_driver;
	//double aux_tip = r->tip;
	res->id			= r->id;
	res->date		= copy_date(r->date);
	res->driver		= r->driver;
	res->user		= strdup(r->user);
	res->city		= strdup(r->city);
	res->distance		= r->distance;
	res->score_user		= r->score_user;
	res->score_driver	= r->score_driver;
	res->tip		= r->tip;
	return res;
}

// TODO check an alternative for better memory usage (dont copy with strdup) 
char* get_ride_driver_name(Ride r) {
	return strdup(r->driver_name);
}

char* get_ride_user_name(Ride r) {
	return strdup(r->user_name);
}

Date get_ride_account_creation_user(Ride r) {
	Date d = r->account_creation_user;
	return d;
}

Date get_ride_account_creation_driver(Ride r) {
	Date d = r->account_creation_driver;
	return d;
}

// Other functions
void print_ride(Ride r) {
	printf("%012d;%s;%012d;%s;%s;%d;%d;%d;%.2f\n",
		r->id,
		date_to_string(r->date),
		r->driver,
		r->user,
		r->city,
		r->distance,
		r->score_user,
		r->score_driver,
		r->tip);
}
