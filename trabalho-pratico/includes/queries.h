#ifndef _QUERIES_H_
#define _QUERIES_H_

#define MAX_SIZE_OUTPUT 300

typedef struct drivers *Drivers;
typedef struct users *Users;
typedef struct rides *Rides;
typedef struct stats *Stats;
typedef struct date *Date;

char* query1(char* token_line, Drivers ds, Users us, Rides rs, int n);
char* query2(char* token_line, Stats stats, int n);
char* query3(char* token_line, Stats stats, int n);
char* query4(char* token_line, Stats stats, int n);
char* query5(char* token_line, Drivers ds, Rides rs, int n);
char* query6(char* token_line, Rides rs, int n);
char* query7(char* token_line, Stats stats,Drivers ds, int n);
char* query8(char* token_line, Rides rides, int n);
char* query9(char* token_line, Stats stats, int n);

#endif
