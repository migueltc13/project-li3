#ifndef _BATCH_H_
#define _BATCH_H_

typedef struct drivers *Drivers;
typedef struct users *Users;
typedef struct rides *Rides;
typedef struct stats *Stats;

void batch(char* path_csvs, char* path_input);

/**
 * @brief This function is used to open "inputs.txt" file and parses each line to handle function.
 * 
 * @param path 
 * @param s 
 * @return int 
 */
void parse_queries(char* path, Drivers ds, Users us, Rides rs, Stats s);

#endif
