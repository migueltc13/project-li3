#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

struct date {
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

Date copy_date(Date d) {
	Date r = (Date) malloc(sizeof(struct date));
	memcpy(r,d,sizeof(struct date));
	return r;
}

Date init_date() {
	Date d = (Date) malloc(sizeof(struct date));
	d->day   = 0;
	d->month = 0;
	d->year  = 0;
	return d;
}

void free_date(Date d) {
	d->day   = 0;
	d->month = 0;
	d->year  = 0;
	free(d);
}

Date parse_date(char* str) {
	Date d = (Date) malloc(sizeof(struct date));

	if (!str || atoi(str) == 0) return string_to_date("00/00/00");

	char* day = strsep(&str,"/");
	if (day) d->day = atoi(day);
	else return string_to_date("00/00/00");
	
	char* month = strsep(&str,"/");
	if (month) d->month = atoi(month);
	else return string_to_date("00/00/00");

	char* year = strsep(&str,"\0");
	if (year) d->year = atoi(year);
	else return string_to_date("00/00/00");
	//printf("day:%d month:%d year:%d\n", d->day, d->month, d->year);

	return d;
}

Date string_to_date(char* str) {
	Date d = (Date) malloc(sizeof(struct date));
	char* aux = strdup(str);
	d->day   = atoi(strsep(&aux,"/"));
	d->month = atoi(strsep(&aux,"/"));
	d->year  = atoi(strsep(&aux,"\0"));
	return d;
}

char* date_to_string(Date d) {
	char str[SIZE_DATE + 1];
	snprintf(str, SIZE_DATE + 1, "%02d/%02d/%04d", d->day, d->month, d->year);
	return strdup(str);
}

int is_valid_date(Date d) {
	if (!(1 <= d->day && d->day <= 31))
		return 1;
	else if (!(1 <= d->month && d->month <= 12))
		return 1;
	else if (d->year==0)
		return 1;
	return 0;
}

/*
 0 -> date1 = date2
 1 -> date1 > date2 (most recent is date1)
 2 -> date1 < date2 (most recent is date2)
*/
int compare_date(Date d1, Date d2) {
	if (d1->year > d2->year) return 1;
	if (d1->year < d2->year) return 2;
	
	if (d1->month > d2->month) return 1;
	if (d1->month < d2->month) return 2;
	
	if (d1->day > d2->day) return 1;
	if (d1->day < d2->day) return 2;
	return 0; 
}

int calculate_age(Date d) {
	int age = CUR_YEA - d->year;
	if ((CUR_MON < d->month) || (CUR_MON == d->month && CUR_DAY < d->day)) 
		age--;
	return age;
}

void print_date(Date d) {
	printf("%d/%d/%d\n", d->day, d->month, d->year);
}
