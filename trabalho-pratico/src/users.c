#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include"user.h"
#include"users.h"

struct users {
	GHashTable* users;
	int nr_users;
};

Users init_users() {
	Users r = (Users) malloc(sizeof(struct users));
	r->users = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_user);
	r->nr_users = 0;
	return r;
}

void free_users(void *ptr) {
	Users us = (Users) ptr;
	g_hash_table_destroy(us->users);
	us->nr_users = 0;
	free(us);
}

void insert_user(Users us, User user) {
	g_hash_table_insert(us->users, g_strdup(get_username(user)), user);
	(us->nr_users)++;
}

User* get_all_users(Users us) {
	
	int n = us->nr_users, i = 0;
	User* r = (User*) malloc(n * sizeof(User));
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, us->users);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val)){
		r[i] = (User) val;
		i++;
	}
	return r;
}

Users copy_users(Users us) {
	Users r = (Users) malloc(sizeof(struct users));
	memcpy(r,us,sizeof(struct users));
	return r;
}

int get_nr_users(Users us) {
	int i = us->nr_users;
	return i;
}

void parse_users(char* path, Users users, FILE* fp) {

	char* buffer = NULL;
	//int line_count = 0; // para indicar quantas linhas nao foram validadas
	size_t bufsize = 0; 
	ssize_t line_size;
	line_size = getline(&buffer, &bufsize, fp); // remove csv header
	while((line_size = getline(&buffer, &bufsize, fp)) >= 0)
		parse_user(buffer, users);

	printf("Number of users parsed:  %d\n", get_nr_users(users));
	free(buffer);
}

/* Teste ao encapsulamento
printf("%s\n",get_username(store_user));
store_user->username = "PWN";
printf("%s\n",get_username(store_user)); 
*/

User get_user_by_username(Users us, char* username) {
	User u = g_hash_table_lookup(us->users, username);
	return u;
}

GHashTable* get_htable_users(Users us) {
	GHashTable* r = us->users;
	return r;
}

// This functions calculates and updates the med_score for all users
void calculate_med_score_users(Users us) {
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, us->users);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val))
		update_user_med_score((User) val);
}

void print_users(Users us) {
	GHashTableIter iter;
	g_hash_table_iter_init(&iter, us->users);
	void *val = NULL;
	while(g_hash_table_iter_next(&iter, NULL, &val))
		print_user((User) val);
}
