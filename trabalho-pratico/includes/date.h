#ifndef _DATE_H_
#define _DATE_H_

#define SIZE_DATE 10

#define CUR_YEA 2022
#define CUR_MON 10
#define CUR_DAY 9

typedef struct date *Date;

Date copy_date(Date d);
Date init_date();
void free_date(Date d);
Date parse_date(char* str);
Date string_to_date(char* str);
char* date_to_string(Date d);
int compare_date(Date d1, Date d2);
int is_valid_date(Date d);
int calculate_age(Date d);
void print_date(Date d);

#endif
