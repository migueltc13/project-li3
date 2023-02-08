#ifndef _CITY_H_
#define _CITY_H_

typedef struct city *City;
typedef struct driver_aval *Driver_aval;

City init_city();

City create_city(char* city_name, double price);
void free_city(void *ptr);
char* get_city_name(City c);
void increment_price_city(City c, double price);
double calc_med_price_city(City c);
int get_nr_drivers_city(City c);

void insert_driver_aval(City c,int id, double aval);
City insert_Drivers_aval_in_city(Driver_aval* drivers, City c);
Driver_aval* get_all_city_driver_aval(City c);

#endif
