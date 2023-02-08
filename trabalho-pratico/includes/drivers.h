#ifndef _DRIVERS_H_
#define _DRIVERS_H_

typedef struct drivers *Drivers;
typedef struct driver *Driver;

/**
 * @brief This function is used to initialize the Drivers Structure
 * 
 * @return Drivers 
 */
Drivers init_drivers();

/**
 * @brief Deallocates memory for all drivers struct values and the struct itself  
 * 
 */
void free_drivers(void *ptr);

/**
 * @brief This function is used to insert a Driver in the struct Drivers
 * 
 * @param d 
 * @param driver 
 * @return void 
 */
void insert_driver(Drivers ds, Driver driver);

/**
 * @brief This function is used to convert a Struct Drivers to a list of Driver
 *  using the copy_drivers function
 * 
 * @param d 
 * @return Driver* 
 */
Driver* get_all_drivers(Drivers ds);

/**
 * @brief This function copys all drivers to another drivers struct
 * 
 * @param d 
 * @return Drivers 
 */
Drivers copy_drivers(Drivers ds);

/**
 * @brief Gets the number of drivers 
 * 
 * @param d 
 * @return int 
 */
int get_nr_drivers(Drivers ds);

/**
 * @brief 
 * 
 * @param path 
 * @param stats 
 * @param BUFFER_SIZE 
 * @return Stats 
 */
void parse_drivers(char* path, Drivers drivers, FILE* fp);
Driver get_driver_by_id(Drivers ds, int id);
void calculate_med_score_drivers(Drivers ds);
void print_drivers(Drivers ds);

#endif
