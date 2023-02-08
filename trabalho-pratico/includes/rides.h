#ifndef _RIDES_H_
#define _RIDES_H_

#include<glib.h>
typedef struct ride *Ride;
typedef struct rides *Rides;
typedef struct drivers *Drivers;
typedef struct users *Users;
typedef struct stats *Stats;
typedef struct date *Date;

Rides init_rides();
void free_rides(void *ptr);
void insert_ride(Rides rs, Ride ride);
GHashTable* get_rides(Rides rs);
Ride* get_all_rides(Rides rs);
Rides copy_rides(Rides rs);
int get_nr_rides(Rides rs);
int get_nr_male_rides(Rides rs);
int get_nr_female_rides(Rides rs);
Ride* get_male_rides(Rides rs);
Ride* get_female_rides(Rides rs);
void insert_male_rides(Rides rs, Ride* ms);
void insert_female_rides(Rides rs, Ride* fs);
Ride get_ride_by_id(Rides rs, int id);
void parse_rides(char* path, Rides rs, Drivers ds, Users users, Stats stats, FILE* fp);
void append_ride_by_gender(Rides rs, Ride r, Date d_driver, char* driver, Date d_user, char* user, char gender);
void print_rides(Rides rs);

#endif
