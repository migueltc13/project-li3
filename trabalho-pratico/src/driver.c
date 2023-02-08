#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"driver.h"
#include"drivers.h"
#include"date.h"
#include"valid.h"

#define REGEX_DRIVER "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]"

struct driver {
	unsigned int id;
	char* name;
	Date birth_date;
	unsigned char gender;
	unsigned char car_class;
	//char* license_plate;
	//char* city;
	Date account_creation;
	unsigned char account_status;  

	double total_made; // tip included
	unsigned int nr_rides;
	double total_score;
	double med_score;
	unsigned int most_recent_ride_id;
};

Driver init_driver(
	int id,
	char* name,
	Date birth_date,
	char gender,
	char car_class,
	Date account_creation,
	char account_status)
{
	int aux_id = id;
	char aux_gender = gender;
	char aux_car_class = car_class;
	char aux_account_status = account_status;
	Driver d = (Driver) malloc(sizeof(struct driver));
	d->id			= aux_id;
	d->name			= strdup(name);
	d->birth_date		= copy_date(birth_date);
	d->gender		= aux_gender;
	d->car_class		= aux_car_class;
	//d->city		= strdup(city);
	d->account_creation	= copy_date(account_creation);
	d->account_status	= aux_account_status;
	d->total_made		= 0;
	d->nr_rides		= 0;
	d->total_score		= 0;
	d->med_score		= 0;
	d->most_recent_ride_id	= 0;
	return d;
}

Driver init_empty_driver() {
	Driver d = (Driver) malloc(sizeof(struct driver));
	d->id			= 0;
	d->name			= NULL;
	d->birth_date		= NULL;
	d->gender		= ' ';
	d->car_class		= ' ';
	//d->city		= strdup(city);
	d->account_creation	= NULL;
	d->account_status	= ' ';
	d->total_made		= 0;
	d->nr_rides		= 0;
	d->total_score		= 0;
	d->med_score		= 0;
	d->most_recent_ride_id	= 0;
	return d;
}

void free_driver(void *ptr) {
	Driver d = (Driver) ptr;
	free(d->name);
	free_date(d->birth_date);
	free_date(d->account_creation);
	d->account_status = ' ';
	d->gender	= ' ';
	d->car_class	= ' ';
	d->id		= 0;
	d->total_made	= 0; 
	d->nr_rides	= 0;
	d->total_score	= 0;
	d->med_score	= 0;
	d->most_recent_ride_id = 0;
	free(d);
}

Driver copy_driver(Driver d) {
	Driver r = (Driver) malloc(sizeof(struct driver));
	memcpy(r,d,sizeof(struct driver));
	return r;
}

void parse_driver(char* buffer, Drivers drivers) {

	Driver store_driver = NULL;

	char* aux = buffer;
	char* id		= strsep(&aux,";");
	char* name		= strsep(&aux,";");
	Date birth_date		= parse_date(strsep(&aux,";"));
	char* gender		= strsep(&aux,";");
	char* car_class		= strsep(&aux,";");
	char* license_plate	= strsep(&aux,";");
	char* city 		= strsep(&aux,";");
	Date account_creation	= parse_date(strsep(&aux,";"));
	char* account_status	= strsep(&aux,"\n");

	int valid = 1;

	// Data validation
	if (strlen(id) == 0 || strlen(name) == 0 || strlen(gender) == 0 || strlen(city) == 0 || strlen(license_plate) == 0
		|| is_valid_date(account_creation) != 0 || is_valid_date(birth_date) != 0
		|| is_valid_car_class(car_class) != 0 || is_valid_status(account_status) != 0)
		valid = 0;

	if (valid) {
		store_driver = init_driver(atoi(id),name,birth_date,gender[0],car_class[0],account_creation,account_status[0]);
		insert_driver(drivers, store_driver);
	}
}

int get_driver_id(Driver d) {
	int n = d->id;
	return n;
}

char* get_driver_name(Driver d) {
	return strdup(d->name);
}

Date get_driver_birth_date(Driver d) {
	return d->birth_date;
}

char get_driver_gender(Driver d) {
	char r = d->gender;
	return r;
}

char get_driver_car_class(Driver d) {
	char r = d->car_class;
	return r;
}

/*
char* get_driver_city(Driver d) {
	return strdup(d->city);
}
*/

Date get_driver_account_creation(Driver d) {
	return d->account_creation;
}

int get_driver_age(Driver d) {
	int age = calculate_age(d->birth_date);
	return age;
}

void add_total_made(Driver d, double price, double tip) {
	d->total_made += price + tip;
}

double get_total_made(Driver d) {
	double f = d->total_made;
	return f;
}

void add_driver_score(Driver d, double score) {
	d->total_score += score;
	(d->nr_rides)++;
}

int get_driver_nr_rides(Driver d) {
	int n = d->nr_rides;
	return n;
}

double get_driver_med_score(Driver d) {
	double f = d->med_score;
	return f;
}

void update_driver_med_score(Driver d) {
	double f = d->total_score / d->nr_rides;
	d->med_score = f;
	if (d->nr_rides == 0)
		d->med_score = 0;
}

int get_most_recent_ride_id_driver(Driver d) {
	int id = d->most_recent_ride_id;
	return id;
}

void insert_most_recent_ride_id_driver(Driver d, int id) {
	int t = id;
	d->most_recent_ride_id = t;
}

int is_driver_active(Driver d) {
	return d->account_status == 'a';
}

void print_driver(Driver d) {
	printf("%012d;%s;%s;%c;%c;%s;%c\n",
		d->id,
		d->name,
		date_to_string(d->birth_date),
		d->gender,
		d->car_class,
		date_to_string(d->account_creation),
		d->account_status);
}

struct driver_aval {
	int id;
	double total_aval;
	int nr_rides;
	int index;
};

void insert_driver_aval_id(Driver_aval d_a, int id){
	(d_a->id) = id;
}

Driver_aval increment_driver_aval_total_aval(Driver_aval d_a, double aval){
	(d_a->nr_rides)++;
	d_a->total_aval += aval;
	return d_a;
}

double get_aval_driver(Driver_aval d_a){
	double aval_total = d_a->total_aval;
	int nrides = d_a->nr_rides;
	return aval_total/nrides;
}

int get_driver_aval_id(Driver_aval d_a){
	int id = d_a->id;
	return id;
}

int get_driver_aval_index(Driver_aval d_a){
	int r = d_a->index;
	return r;
}

Driver_aval init_driver_aval(){
	Driver_aval d = (Driver_aval) malloc(sizeof(struct driver_aval));
	return d;
}

void free_driver_aval(void *driver){
	Driver_aval d_a = (Driver_aval) driver;
	d_a->id = 0;
	d_a->total_aval = 0;
	d_a->nr_rides = 0;
	d_a->index = 0;
	free(d_a);
}


Driver_aval create_driver_aval(int id, double aval, int index) {
	Driver_aval driver = init_driver_aval();
	driver->id = id;
	driver->total_aval = aval;
	driver->nr_rides = 1;
	driver->index = index;
	return driver;
}
