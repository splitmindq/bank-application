//
// Created by mzitr on 16.04.2024.
//

#ifndef BANK_BANK_STRUCTURE_H
#define BANK_BANK_STRUCTURE_H


typedef struct {
    char card_number[16];
    float balance;
    char currency[3];
}card_info;

typedef struct {
    char login[50];
    char* password;
    char* email;

}Credentials;


typedef struct {
    char* fullname;
    char* birthday;
    Credentials user_data;
    card_info card;

}User;



#endif //BANK_BANK_STRUCTURE_H

