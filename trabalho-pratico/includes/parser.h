#ifndef _PARSER_H_
#define _PARSER_H_

typedef struct drivers *Drivers;
typedef struct users *Users;
typedef struct rides *Rides;
typedef struct stats *Stats;

void data_parser(char *path, Drivers drivers, Users users, Rides rides, Stats stats);

#endif
