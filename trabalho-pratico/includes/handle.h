#ifndef _HANDLE_H_
#define _HANDLE_H_

typedef struct drivers *Drivers;
typedef struct users *Users;
typedef struct rides *Rides;
typedef struct stats *Stats;

/**
 * @brief This function is used to see what query is going to be used on the inputs.
 * 
 * @param buffer
 * @param drivers
 * @param users
 * @param rides
 * @param stats
 * @param n
 * @param mode 
 *  
 */
void handle(char* buffer, Drivers drivers, Users users, Rides rides, Stats stats, int n, int mode);

#endif
