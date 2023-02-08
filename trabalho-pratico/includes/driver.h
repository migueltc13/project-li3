#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <glib.h>
typedef struct driver *Driver;
typedef struct drivers *Drivers;
typedef struct driver_aval *Driver_aval;
typedef struct city *City;
typedef struct date *Date;

/**
 * @brief This function is used to initialize a new user with the given paramenters allocating memory
 * 
 * @param id 
 * @param name 
 * @param birth_date 
 * @param gender 
 * @param car_class 
 * @param city 
 * @param account_creation 
 * @param account_status 
 * @return Driver
 */
Driver init_driver(
	int id,
	char* name,
	Date birth_date,
	char gender,
	char car_class,
	Date account_creation,
	char account_status);

Driver init_empty_driver();

/**
 * @brief Frees the driver values and the struct drive itself 
 * 
 * @param void *ptr (aka Driver)
 */
void free_driver(void *ptr);

void parse_driver(char* buffer, Drivers drivers);

/**
 * @brief Gets the driver id 
 * 
 * @param Driver d 
 * @return char* 
 */
int get_driver_id(Driver d);


/**
 * @brief Gets the driver name 
 * 
 * @param Driver d 
 * @return char* 
 */
char* get_driver_name(Driver d);


/**
 * @brief Gets the driver birth date 
 * 
 * @param Driver d 
 * @return Date
 */
Date get_driver_birth_date(Driver d);


/**
 * @brief Gets the driver gender
 * 
 * @param Driver d 
 * @return char* 
 */
char get_driver_gender(Driver d);


/**
 * @brief Gets the driver car class 
 * 
 * @param Driver d 
 * @return char* 
 */
char get_driver_car_class(Driver d);


/**
 * @brief Gets the driver city 
 * 
 * @param Driver d 
 * @return char* 
 */
//char* get_driver_city(Driver d);


/**
 * @brief Gets the driver account creation date
 * 
 * @param Driver d 
 * @return Date 
 */
Date get_driver_account_creation(Driver d);


/**
 * @brief Gets the driver age 
 * 
 * @param Driver d 
 * @return int 
 */
int get_driver_age(Driver d);


/**
 * @brief This function copies a driver
 * 
 * @param Driver d
 * @return Driver
 */
Driver copy_driver(Driver d);

void add_total_made(Driver d, double price, double tip);
double get_total_made(Driver d);
void add_driver_score(Driver d, double score);
int get_driver_nr_rides(Driver d);
double get_driver_med_score(Driver d);
void update_driver_med_score(Driver d);
int get_most_recent_ride_id_driver(Driver d);
void insert_most_recent_ride_id_driver(Driver d, int id);
int is_driver_active(Driver d);

/**
 * @brief This function prints a driver
 *
 * @param Driver d 
 */
void print_driver(Driver d); // rm me later

// ---
Driver_aval init_driver_aval();
void free_driver_aval(void *driver);
Driver_aval create_driver_aval(int id, double aval, int index);
void insert_driver_aval_id(Driver_aval d_a, int id);
Driver_aval increment_driver_aval_total_aval(Driver_aval d_a, double aval);
double get_aval_driver(Driver_aval d_a);
int get_driver_aval_id(Driver_aval d_a);
int get_driver_aval_index(Driver_aval d_a);
GHashTable* get_driver_aval_table(City c);


#endif
