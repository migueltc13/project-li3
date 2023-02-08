#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include"cities.h"
#include"city.h"

struct cities {
	City* cities;
	GHashTable* city_table;
	int nr_cities;
};

Cities init_cities() {
	Cities cs = (Cities) malloc(sizeof(struct cities));
	cs->city_table = g_hash_table_new(g_str_hash, g_str_equal);
	cs->cities = (City*) malloc(sizeof(City));
	cs->nr_cities = 0;
	return cs;
}

void free_cities(void* ptr) {
	Cities cs = (Cities) ptr;
	g_hash_table_destroy(cs->city_table);
	for (int i=0; i<cs->nr_cities; i++)
		free_city(cs->cities[i]);
	cs->nr_cities = 0;
	free(cs->cities);
	free(cs);
}

City insert_city(Cities cs, char* city_name, double price, Driver d) {

	City c = (City) g_hash_table_lookup(cs->city_table, city_name);
	if (c == NULL) {
		c = create_city(city_name, price);
		g_hash_table_insert(cs->city_table, get_city_name(c), c);
		cs->cities = (City *) realloc(cs->cities, sizeof(City) * (cs->nr_cities+1));
		cs->cities[cs->nr_cities++] = c;
	}
	else {
		increment_price_city(c, price);
	}
	return c;
}

Cities update_cities(Cities cs, City c, int index){
	cs->cities[index] = c;
	return cs;
}

City get_city_by_index(Cities cs, int index) {
	City c = cs->cities[index];
	return c;
}

int get_nr_cities(Cities cs) {
	int i = cs->nr_cities;
	return i;
}

City* get_all_cities(Cities cs) {
	City* c = cs->cities;
	return c;
}

GHashTable* get_city_table(Cities cs) {
	GHashTable* city_table = cs->city_table;
	return city_table;
}

double get_med_price_by_city(Cities cs, char* city_name) {

	char* c_name = (char*) malloc(sizeof(char));
	double med_price = 0;

	for (int i=0; i<cs->nr_cities; i++) {
		City c = cs->cities[i];
		c_name = get_city_name(c);
		if (strcmp(city_name, c_name) == 0) {
			med_price = calc_med_price_city(c);
			free(c_name);
			return med_price;
		}
	}
	return -1;
}
