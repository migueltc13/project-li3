#ifndef _RIDE_H_
#define _RIDE_H_

#include<glib.h>
typedef struct ride *Ride;
typedef struct rides *Rides;
typedef struct drivers *Drivers;
typedef struct users *Users;
typedef struct stats *Stats;
typedef struct cities *Cities;
typedef struct date *Date;

/**
 * @brief This function is used to initialize a new ride with the given paramenters allocating memory
 * 
 * @param id 
 * @param date 
 * @param driver 
 * @param user 
 * @param city 
 * @param distance 
 * @param score_user 
 * @param score_driver 
 * @param tip 
 * @return Ride 
 */
Ride init_ride(
	int id,
	Date date,
	int driver,
	char* user,
	char* city,
	int distance,
	int score_user,
	int score_driver,
	double tip);

/**
 * @brief Frees the ride values and the struct ride itself 
 * 
 * @param Ride
 */
void free_ride(void *ptr);

void parse_ride(char* buffer, Rides rides, Drivers drivers, Users users, Stats stats, Cities cities, GHashTable* htable_users);

/**
 * @brief Gets the ride id 
 * 
 * @param Ride 
 * @return int
 */
int get_ride_id(Ride r);

/**
 * @brief Gets the ride date 
 * 
 * @param Ride 
 * @return Date
 */
Date get_ride_date(Ride r);

/**
 * @brief Gets the ride driver 
 * 
 * @param Ride 
 * @return int 
 */
int get_ride_driver(Ride r);

/**
 * @brief Gets the ride user 
 * 
 * @param Ride 
 * @return char* 
 */
char* get_ride_user(Ride r);

/**
 * @brief Gets the ride city 
 * 
 * @param Ride 
 * @return char* 
 */
char* get_ride_city(Ride r);

/**
 * @brief Gets the ride distance 
 * 
 * @param Ride 
 * @return int
 */
int get_ride_distance(Ride r);

/**
 * @brief Gets the ride score user 
 * 
 * @param Ride 
 * @return int 
 */
int get_ride_score_user(Ride r);

/**
 * @brief Gets the ride score driver 
 * 
 * @param Ride 
 * @return int
 */
int get_ride_score_driver(Ride r);

/**
 * @brief Gets the ride tip 
 * 
 * @param Ride 
 * @return double 
 */
double get_ride_tip(Ride r);

/**
 * @brief Calculates the ride cost based on the first char of a driver car class 
 * 
 * @param Ride
 * @param char
 * @return float 
 */
double calculate_ride_price(Ride r, char car_class);

double get_ride_price(Ride r);
void insert_ride_price(Ride r, double f);

/**
 * @brief This function copies a ride
 * 
 * @param Ride
 * @return Ride
 */
Ride copy_ride(Ride r);

/**
 * @brief This function prints a ride
 * 
 * @param Ride 
 */
void print_ride(Ride r); // remove me later

Ride create_partial_ride(Ride r, Date d_driver, char* driver, Date d_user, char* user);
char* get_ride_driver_name(Ride r);
char* get_ride_user_name(Ride r);
Date get_ride_account_creation_user(Ride r);
Date get_ride_account_creation_driver(Ride r);

#endif
