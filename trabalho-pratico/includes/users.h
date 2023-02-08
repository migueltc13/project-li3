#ifndef _USERS_H_
#define _USERS_H_

#include<glib.h>
typedef struct users *Users;
typedef struct user *User;

Users init_users();
void free_users(void *ptr);
void insert_user(Users us, User user);
User* get_all_users(Users us);
Users copy_users(Users us);
int get_nr_users(Users us);
void parse_users(char* path, Users us, FILE* fp);
User get_user_by_username(Users us, char* username);
GHashTable* get_htable_users(Users us);
void calculate_med_score_users(Users us);
void print_users(Users us);

#endif
