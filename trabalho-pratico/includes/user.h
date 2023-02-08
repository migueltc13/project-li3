#ifndef _USER_H_
#define _USER_H_

typedef struct user *User;
typedef struct users *Users;
typedef struct date *Date;

/**
 * @brief This function is used to initialize a new user with the given paramenters allocating memory
 * 
 * 
 * @param username 
 * @param name 
 * @param gender 
 * @param birth_date 
 * @param account_creation
 * @param account_status 
 * @return User 
 */
User init_user(
	char* username,
	char* name,
	char gender,
	Date birth_date,
	Date account_creation,
	char account_status);

User init_empty_user();

/**
 * @brief Frees the user values and the struct user itself 
 * 
 * @param User
 */
void free_user(void *ptr);

void parse_user(char* buffer, Users users);

/**
 * @brief Gets the username of the user 
 * 
 * @param u (user u)
 * @return char* 
 */
char* get_username(User u);


/**
 * @brief Gets the name of the user
 * 
 * @param u (user u)
 * @return char* 
 */
char* get_name(User u);


/**
 * @brief Gets the gender of the user
 * 
 * @param u (user u)
 * @return char* 
 */
char get_gender(User u);


/**
 * @brief Gets the birth date of the user
 * 
 * @param u (user u)
 * @return Date 
 */
Date get_birth_date(User u);


/**
 * @brief Gets the account creation date of the user
 * 
 * @param u (user u)
 * @return Date 
 */
Date get_account_creation(User u);


/**
 * @brief Gets the pay method option of the user
 * 
 * @param u (user u)
 * @return char* 
 */
char* get_pay_method(User u);

/**
 * @brief Gets the user age 
 * 
 * @param d 
 * @return int 
 */
int get_user_age(User u);

/**
 * @brief This function copies a user
 *
 * @param u
 * @return User
 */
User copy_user(User u);

void add_total_distance(User u, int distance);
int get_total_distance(User u);
void add_total_spent(User u, double price, double tip);
double get_total_spent(User u);
void add_user_score(User u, double score);
int get_user_nr_rides(User u);
double get_user_med_score(User u);
void update_user_med_score(User u);
void insert_most_recent_ride_id(User u, int id);
int get_most_recent_ride_id(User u);
int is_user_active(User u);

/**
 * @brief This function prints a user u
 * 
 * @param u (user u)
 */
void print_user(User u);

#endif
