#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include"drivers.h"
#include"driver.h"

struct drivers {
	GHashTable* drivers;
	int nr_drivers;
};

Drivers init_drivers() {
	Drivers ds = (Drivers) malloc(sizeof(struct drivers));
	ds->drivers = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, free_driver);
	ds->nr_drivers = 0;
	return ds; 
}

void free_drivers(void *ptr) {
	Drivers ds = (Drivers) ptr;
	g_hash_table_destroy(ds->drivers);
	ds->nr_drivers = 0;
	free(ds);
}

void insert_driver(Drivers ds, Driver driver) {
	g_hash_table_insert(ds->drivers, GINT_TO_POINTER(get_driver_id(driver)), driver);
	(ds->nr_drivers)++;
}

Driver* get_all_drivers(Drivers ds) {
	
	int n = ds->nr_drivers, i = 0;
	Driver* r = (Driver*) malloc(n * sizeof(Driver));
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, ds->drivers);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val)){
		r[i] = (Driver) val;
		i++;
	}
	return r;
}

Drivers copy_drivers(Drivers ds) {
	Drivers r = (Drivers) malloc(sizeof(struct drivers));
	memcpy(r,ds,sizeof(struct drivers));
	return r;
}

int get_nr_drivers(Drivers ds) {
	int i = ds->nr_drivers;
	return i;
}

void parse_drivers(char* path, Drivers drivers, FILE* fp) {

	char* buffer = NULL;
	//int line_count = 0; // para indicar quantas linhas nao foram validadas
	size_t bufsize = 0;
	ssize_t line_size;
	line_size = getline(&buffer, &bufsize, fp); // remove csv header

	while((line_size = getline(&buffer, &bufsize, fp)) >= 0)
		parse_driver(buffer, drivers);

	printf("Number of drivers parsed: %d\n",get_nr_drivers(drivers));
	free(buffer);
}

Driver get_driver_by_id(Drivers ds, int id) {
	Driver d = g_hash_table_lookup(ds->drivers, GINT_TO_POINTER(id));
	return d;
}

// This functions calculates and updates the med_score for all drivers
void calculate_med_score_drivers(Drivers ds) {
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, ds->drivers);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val))
		update_driver_med_score((Driver) val);
}


void print_drivers(Drivers ds) {
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, ds->drivers);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val))
		print_driver((Driver) val);
}
