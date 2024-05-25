//
// Created by mzitr on 16.04.2024.
//

#ifndef BANK_FUNCTIONS_H
#define BANK_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank_structure.h"
#include "time.h"
#include <stdbool.h>
#include "windows.h"
#include <curl/curl.h>
#include "sha256.h"
#include "math.h"
#include <float.h>
#define BANK_ACCOUNT_NUMBER_LENGTH 16


//-------------------------------

//------ menu
void manage();


//------ check data
int is_unique_login(User* users, int users_count, const char* login); //check login repeating
int check_password(const char* password);//check password


//------ user basic structure
void read_user(User* users, unsigned int* users_count);//read user data
User* add_user(User* users, unsigned int* count_of_users);//add user to bfile


//------ database
void save_data(User* users, unsigned int* users_count);//save data
User* init_data(unsigned int* users_count);//init data
User* delete_user_from_index(User *users, unsigned int *users_count, unsigned int deleted_index);//delete by index


//----- panels
void login_panel(User *users,unsigned int*users_count);//login panel
void user_panel(User *user, unsigned int *users_count, int index);//user panel
void admin_panel(User* users,unsigned int *users_count,int index);//admin panel


//------ computations
float comission(card_info *balance, User *user, unsigned int *users_count, double transfer_value); //commission calculation
void change_currency(User *user,int index); //request and algorithm for changing currency
void generate_bank_account_number(char* bank_account_number, int length); //generate card number
int calculate_age(const char* birthday);//access by age
int is_valid_date(int day, int month, int year);
void generate_password(char *password);
void change_profile(User *user, int index);


//------ print
void print_formatted_number(const char* number);//print xxxx_xxxx_xxxx_xxxx
void print_user(User users);//print user
void print_all_users(User* users, unsigned int* users_count);//print all users & index's


//------ additional/optimization
int is_request_successful();


//------ password_recovery
void send_email(const char *to, const char *subject, const char *message);

//------ memory
void free_users(User* users, unsigned int count);
#endif //BANK_FUNCTIONS_H
