#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"user.h"
#include"users.h"
#include"date.h"
#include"valid.h"

#define REGEX_USER "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]"

struct user {
	char* username;
	char* name;
	unsigned char gender;
	Date birth_date;
	Date account_creation;
	//char* pay_method;
	unsigned char account_status;
	
	//unsigned int age;
	unsigned int total_distance;
	double total_spent; // tip included
	unsigned int nr_rides;
	double total_score;
	unsigned int most_recent_ride_id;
	double med_score;
};

User init_user(
	char* username,
	char* name,
	char gender,
	Date birth_date,
	Date account_creation,
	char account_status)
{
	char aux_gender = gender;
	char aux_account_status = account_status;
	User u = (User) malloc(sizeof(struct user));
	u->username		= strdup(username);
	u->name			= strdup(name);
	u->gender		= aux_gender;
	u->birth_date		= birth_date;
	u->account_creation	= account_creation;
	u->account_status	= aux_account_status;
	u->total_distance	= 0;
	u->total_spent		= 0;
	u->most_recent_ride_id	= 0;
	u->med_score		= 0;
	return u;
}

User init_empty_user() {
	User u = (User) malloc(sizeof(struct user));
	u->username		= NULL;
	u->name			= NULL;
	u->gender		= ' ';
	u->birth_date		= string_to_date("00/00/00");
	u->account_creation	= string_to_date("00/00/00");
	u->account_status	= ' ';
	u->total_distance	= 0;
	u->total_spent		= 0;
	u->most_recent_ride_id	= 0;
	u->med_score		= 0;
	return u;
}

void free_user(void *ptr) {
	User u = (User) ptr;
	free(u->username);
	free(u->name);
	free_date(u->birth_date);
	free_date(u->account_creation);
	u->gender = ' ';
	u->account_status = ' ';
	u->total_distance	= 0;
	u->total_spent		= 0;
	u->most_recent_ride_id	= 0;
	u->med_score		= 0;
	free(u);
}

User copy_user(User u) {
	User r = (User) malloc(sizeof(struct user));
	memcpy(r,u,sizeof(struct user));
	return r;
}

void parse_user(char* buffer, Users users) {

	User store_user = NULL;

	char* aux = buffer;	
	char* username		= strsep(&aux,";");
	char* name		= strsep(&aux,";");
	char* gender		= strsep(&aux,";");
	Date birth_date		= parse_date(strsep(&aux,";"));
	Date account_creation	= parse_date(strsep(&aux,";"));
	char* pay_method 	= strsep(&aux,";");
	char* account_status	= strsep(&aux,"\n");

	int valid = 1;

	// Data validation
	if (strlen(username) == 0 || strlen(name) == 0 || strlen(gender) == 0 || strlen(pay_method) == 0
		 || is_valid_date(account_creation) != 0 || is_valid_date(birth_date) != 0
		 || is_valid_status(account_status) != 0)
		valid = 0;

	/* printf("VALID: %d\n", valid);
	print_date(birth_date);
	print_date(account_creation);
	printf("is_valid_date(birth_date) == %d\n", is_valid_date(birth_date));
	printf("is_valid_date(account_creation) == %d\n", is_valid_date(account_creation));
	printf("is_valid_status(account_status) == %d\n", is_valid_status(account_status)); */

	if (valid) {
		store_user = init_user(username,name,gender[0],birth_date,account_creation,account_status[0]);
		insert_user(users, store_user);
		//print_user(store_user);
	}
}

// Functions to get a single specific field
char* get_username(User u) {
	return strdup(u->username);
}

char* get_name(User u) {
	return strdup(u->name);
}

char get_gender(User u) {
	char r = u->gender;
	return r;
}

Date get_birth_date(User u) {
	return u->birth_date;
}

Date get_account_creation(User u) {
	return u->account_creation;
}

int get_user_age(User u) {
	int age = calculate_age(u->birth_date);
	return age;
}

void add_total_distance(User u, int distance) {
	u->total_distance += distance;
}

int get_total_distance(User u) {
	int n = u->total_distance;
	return n;
}

void add_total_spent(User u, double price, double tip) {
	u->total_spent += price + tip;
}

double get_total_spent(User u) {
	double d = u->total_spent;
	return d;
}

void add_user_score(User u, double score) {
	u->total_score += score;
	(u->nr_rides)++;
}

int get_user_nr_rides(User u) {
	int n = u->nr_rides;
	return n;
}

void insert_most_recent_ride_id(User u, int id) {
	int t = id;
	u->most_recent_ride_id = t;
}

int get_most_recent_ride_id(User u) {
	int id = u->most_recent_ride_id;
	return id;
}

int is_user_active(User u) {
	return u->account_status == 'a';
}

double get_user_med_score(User u) {
	double d = u->med_score;
	return d;
}

void update_user_med_score(User u) {
	double d = u->total_score / u->nr_rides;
	u->med_score = d;
}

// Other functions

void print_user(User u) {
	printf("%s;%s;%c;%s;%s;%c\n",
		u->username,
		u->name,
		u->gender,
		date_to_string(u->birth_date),
		date_to_string(u->account_creation),
		u->account_status);
}
