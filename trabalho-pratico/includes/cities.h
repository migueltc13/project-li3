#ifndef _CITIES_H_
#define _CITIES_H_

#include<glib.h>
typedef struct cities *Cities;
typedef struct city *City;
typedef struct driver *Driver;

Cities init_cities();
void free_cities(void* ptr);
City insert_city(Cities cs, char* city_name, double price, Driver d);
Cities update_cities(Cities cs, City c, int index);
City get_city_by_index(Cities cs, int index);
int get_nr_cities(Cities cs);
City* get_all_cities(Cities cs);
GHashTable* get_city_table(Cities cs);
double get_med_price_by_city(Cities cs, char* city_name);

#endif
