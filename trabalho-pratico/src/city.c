#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include"city.h"
#include"driver.h"

struct city {
	char* city_name; 
	// query 4
	int total_rides;
	double total_price; // no tips included
	// query 7 
	GHashTable* driver_aval_table;
	Driver_aval* drivers; // better id and av_med only
	int nr_drivers_city;
};

City init_city() {
	City c = (City) malloc(sizeof(struct city));
	c->total_rides = 0;
	c->total_price = 0;
	c->driver_aval_table = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, free_driver_aval);
	c->drivers = malloc(sizeof(Driver_aval));
	c->nr_drivers_city = 0;
	return c;
}

void free_city(void *ptr) {
	City c = (City) ptr;
	free(c->city_name);
	c->total_rides = 0;
	c->total_price = 0;
	g_hash_table_destroy(c->driver_aval_table);
	//for (int i=0; i<c->nr_drivers_city; i++) 
	//	free_driver_aval(c->drivers);
	free(c->drivers);
	c->nr_drivers_city = 0;
	free(c);
}

City create_city(char* city_name, double price) {
	City c = init_city();
	c->city_name = strdup(city_name);
	c->total_price = price;
	c->total_rides = 1;
	return c;
}

char* get_city_name(City c) {
	return strdup(c->city_name);
}

void increment_price_city(City c, double price) {
	(c->total_rides)++;
	c->total_price += price;
}

double calc_med_price_city(City c) {
	double med_price = c->total_price / c->total_rides;
	return med_price;
}

int get_nr_drivers_city(City c) {
	int nr_city = c->nr_drivers_city;
	return nr_city;
}

// Driver aval

void insert_driver_aval(City c, int id, double aval){
	Driver_aval driver = g_hash_table_lookup(c->driver_aval_table, &id);

	if (driver) {
		int index = get_driver_aval_index(driver);
		c->drivers[index] = increment_driver_aval_total_aval(driver, aval);
	}
	else {
		Driver_aval new_driver = create_driver_aval(id, aval, c->nr_drivers_city);
		g_hash_table_insert(c->driver_aval_table, &id, new_driver);
		c->drivers = realloc(c->drivers, sizeof(Driver_aval) * ((get_nr_drivers_city(c))+1));
		c->drivers[get_nr_drivers_city(c)] = new_driver;
		c->nr_drivers_city++;
	}
}

City insert_Drivers_aval_in_city(Driver_aval* drivers, City c){
	c->drivers = drivers;
	return c;	
}


Driver_aval* get_all_city_driver_aval(City c){
	Driver_aval* d_a = c->drivers;
	return d_a;
}

GHashTable* get_driver_aval_table(City c) {
	GHashTable* t = c->driver_aval_table;
	return t;
}
