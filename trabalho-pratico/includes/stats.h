#ifndef _STATS_H_
#define _STATS_H_

#define SIZE_ID 12

typedef struct stats *Stats;
typedef struct drivers *Drivers;
typedef struct driver *Driver;
typedef struct users *Users;
typedef struct user *User;
typedef struct ride *Ride;
typedef struct rides *Rides;
typedef struct cities *Cities;

/**
 * @brief This function is called to initialize the drivers the users
 * and the rides going forward. 
 * 
 * @return Stats 
 */
Stats init_stats();

/**
 * @brief Deallocates stats struct and all values inside  
 * 
 * @return Stats 
 */
void free_stats(Stats s);

// For query2
void sort_drivers_med_score(Drivers ds, Rides rides, Stats s);
Driver* get_sorted_drivers_med_score(Stats s);
int get_nr_drivers_stats(Stats s);

// For query3
void sort_users_distance(Users us, Rides rides, Stats s);
User* get_sorted_users_distance(Stats s);
int get_nr_users_stats(Stats s);

// For query4
void insert_cities_stats(Stats s, Cities cs);
Cities get_cities_stats(Stats s);

// For query7
int compare_driver_aval(const void *ptr1, const void *ptr2);
void sort_drivers_avaliation(Drivers ds, Rides rs, Stats stats);

// For query8
void sort_rides_male_age(Rides rides);
void sort_rides_female_age(Rides rides);
// For query9
void insert_rides_tip_stats(Stats stats, Ride store_ride);
void sort_tip_rides (Rides rides, Stats stats);
Ride* get_sorted_tip_rides_stats (Stats s);
int get_sorted_tip_nr_rides(Stats s);


#endif
