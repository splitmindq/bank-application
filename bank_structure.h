//
// Created by mzitr on 16.04.2024.
//

#ifndef BANK_BANK_STRUCTURE_H
#define BANK_BANK_STRUCTURE_H


typedef struct {
    char card_number[16]; // Номер счёта
    float balance; // Баланс
    char currency[3]; // Текущая валюта(USD, BYN, JPY, ...)
}card_info;

typedef struct {
    char login[50];
    char* password;
    char* email;

}Credentials;


typedef struct {
    char* fullname; // ФИО
    char* birthday; // Дата рождения
    Credentials user_data; // Данные авторизации
    card_info card; // Данные счёта

}User;



#endif //BANK_BANK_STRUCTURE_H

