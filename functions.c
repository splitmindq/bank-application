// Created by mzitr on 16.04.2024.
//
// path :   C:\Users\mzitr\OneDrive\Рабочий стол\bank_app\cmake-build-debug

#include "functions.h"

float  comission(card_info *balance, User *user, unsigned int *users_count, double transfer_value) {

    float commission_rate = 0.03;
    float commission = transfer_value * commission_rate;
    float total_cost = transfer_value + commission;


    printf("Комиссия за транзакцию: %.2f\n", commission);
    printf("Итоговая сумма транзакции с комиссией: %.2f\n", total_cost);
    return commission;
}

void generate_bank_account_number(char* bank_account_number, int length) {

    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        int digit = rand() % 10;
        bank_account_number[i] = '0' + digit;
    }
    bank_account_number[length] = '\0';
}

void generate_password(char *password) {
    size_t length = 8;
    const char *special_chars = "!@#$%^&*()_=[]{}|;:<>?";
    const char *lower_chars = "abcdefghijklmnopqrstuvwxyz";
    const char *upper_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *digits = "0123456789";

    size_t total_chars_length = strlen(special_chars) + strlen(lower_chars) + strlen(upper_chars) + strlen(digits);
    char all_chars[total_chars_length + 1];

    snprintf(all_chars, sizeof(all_chars), "%s%s%s%s", special_chars, lower_chars, upper_chars, digits);

    srand(time(NULL));

    int has_special = 0;
    int has_upper = 0;
    int has_digit = 0;

    for (size_t i = 0; i < length; ++i) {
        char random_char = all_chars[rand() % total_chars_length];
        password[i] = random_char;

        if (strchr(special_chars, random_char)) has_special = 1;
        if (strchr(upper_chars, random_char)) has_upper = 1;
        if (strchr(digits, random_char)) has_digit = 1;
    }

     if (!has_special) {
        password[rand() % length] = special_chars[rand() % strlen(special_chars)];
    }
    if (!has_upper) {
        password[rand() % length] = upper_chars[rand() % strlen(upper_chars)];
    }
    if (!has_digit) {
        password[rand() % length] = digits[rand() % strlen(digits)];
    }

    password[length] = '\0';
}

void print_formatted_number(const char* number) {
    int length = strlen(number);
    for (int i = 0; i < length; i++) {
        printf("%c", number[i]);
        if ((i + 1) % 4 == 0 && i < length - 1) {
            printf(" ");
        }
    }
}

int is_unique_login(User* users, int users_count, const char* login) {
    bool error_flag = false;
    for (int i = 0; i < users_count; i++) {
        if (strcmp(users[i].user_data.login, login) == 0) {
            return 0;
        }
    }
    int lenght = strlen(login);
    if (lenght < 6) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
        GetConsoleScreenBufferInfo(handle, &originalAttributes);
        puts("Размер логина должен превышать 5 символов");
        SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
        error_flag = true;
    }
    int numbers = 0;
    for (int i = 0; i < lenght; i++) {
        if (login[i] >= '0' && login[i] <= '9') {
            ++numbers;
        }
    }
    if (numbers == lenght) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
        GetConsoleScreenBufferInfo(handle, &originalAttributes);
        puts("Логин не должен состоять только из цифр");
        SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
        error_flag = true;
    }
    if(error_flag){
        return 0;
    }
    return 1;
}

int check_password(const char* password) {
    int upper_case_check_count = 0;
    int signs_check_count = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            upper_case_check_count++;
        }
        if (password[i] >= 33 && password[i] <=47 && password[i] != 43 || (password[i] >= 58 && password[i] < 65) || (password[i]>=91 && password[i]<96) || (password[i]>=123 && password[i]<=126) ) { //add text/binary file with all symbols;
            signs_check_count++;
        }
    }

    int password_size = strlen(password);
    int error_flag = 0;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
    GetConsoleScreenBufferInfo(handle, &originalAttributes);

    if (upper_case_check_count == 0) {
        SetConsoleTextAttribute(handle, FOREGROUND_RED);
        puts("Заглавные буквы обязательны.");
        SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
        error_flag = 1;
    }

    if (signs_check_count == 0) {
        SetConsoleTextAttribute(handle, FOREGROUND_RED);
        puts("Использование хотя бы одного символа обязательно.");
        SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
        error_flag = 1;
    }

    if (password_size < 8) {
        SetConsoleTextAttribute(handle, FOREGROUND_RED);
        puts("Длина пароля не должна быть меньше 8 символов.");
        SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
        error_flag = 1;
    }

    if (error_flag) {
        return 0;
    }


    return 1;
}
int is_valid_date(int day, int month, int year) {
    time_t now = time(NULL);

    if (now == -1) {
        perror("Failed to get the current time");
        return 1;
    }

    struct tm* local_time = localtime(&now);

    if (local_time == NULL) {
        perror("Failed to convert to local time");
        return 1;
    }

    int current_year = local_time->tm_year + 1900;

    if (year < 1900 || year > current_year) {
        return 0;
    }

    if (month < 1 || month > 12) {
        return 0;
    }

    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        days_in_month[1] = 29;
    }

    if (day < 1 || day > days_in_month[month - 1]) {
        return 0;
    }

    return 1;
}

int calculate_age(const char* birthday) {
    struct tm user_tm;
    time_t now = time(NULL);
    struct tm* current_time = localtime(&now);
    int day, month, year, c_year;
    sscanf_s(birthday, "%d.%d.%d", &day, &month, &year);

    if (!is_valid_date(day, month, year)) {
        return -1; // Invalid date
    }

    c_year = current_time ->tm_year + 1900;
    int age;
    int adulthood_flag;

    if(c_year == (year + 18)) {
        user_tm.tm_year = year - 1900;
        user_tm.tm_mon = month - 1;
        user_tm.tm_mday = day;
        user_tm.tm_hour = 0;
        user_tm.tm_min = 0;
        user_tm.tm_sec = 0;

        time_t user_time = mktime(&user_tm);
        double seconds_per_year = 365.25 * 24 * 60 * 60;
        double age_seconds = difftime(now, user_time);
        age = (int)(age_seconds / seconds_per_year);
        if(age < 18) {
            adulthood_flag = 0;
        } else {
            adulthood_flag = 1;
        }
    } else if(c_year > (year + 18)) {
        adulthood_flag = 1;
    } else {
        adulthood_flag = 0;
    }

    return adulthood_flag;
}

void read_user(User* users, unsigned int* users_count) {
    printf("\t -> Создайте свою банковскую учетную запись <-\n");

    printf("Введите ваши полные имя и фамилию на английском языке: ");
    char fullname[100];
    scanf("%*['\n']");
    scanf("%99[^\n]", fullname); // Ensuring we do not overflow the buffer
    users[*users_count - 1].fullname = malloc(strlen(fullname) + 1);
    if (users[*users_count - 1].fullname == NULL) {
        perror("Failed to allocate memory for fullname");
        return;
    }
    strcpy(users[*users_count - 1].fullname, fullname);

    char birthday[100];
    bool is_adult = true;
    while (is_adult) {
        int adult_flag;
        while (1) {
            printf("\t -> Введите вашу дату рождения. Формат (дд.мм.гггг) <-\n");
            scanf("%*['\n']");
            scanf("%99[^\n]", birthday); // Ensuring we do not overflow the buffer
            int adulthood_flag = calculate_age(birthday);

            if (adulthood_flag == -1) {
                printf("\nIncorrect input, try again.\n");
            } else {
                adult_flag = adulthood_flag;
                break;
            }
        }
        if (adult_flag == 0) {
            printf("Доступ в банк предоставляется лицам старше 18 лет.\n");
            users = delete_user_from_index(users, users_count, (*users_count) - 1);
            save_data(users, users_count);
            return;
        } else {
            is_adult = false;
        }
    }
    users[*users_count - 1].birthday = malloc(strlen(birthday) + 1);
    if (users[*users_count - 1].birthday == NULL) {
        perror("Failed to allocate memory for birthday");
        free(users[*users_count - 1].fullname);
        return;
    }
    strcpy(users[*users_count - 1].birthday, birthday);

    char login[100];
    char password[100];

    bool is_actual = 1;
    while (is_actual) {
        puts("\t -> Введите логин для своего аккаунта <-");
        scanf("%*['\n']");
        scanf("%99[^\n]", login); // Ensuring we do not overflow the buffer
        if (is_unique_login(users, *users_count, login)) {
            strcpy(users[*users_count - 1].user_data.login, login);
            is_actual = 0;
        } else {
            puts("Такой логин уже существует.");
        }
    }

    is_actual = 1;
    while (is_actual) {


        puts("\t -> Введите пароль для своего аккаунта <-\n");
        puts("\nЗаглавные буквы обязательны.");
        puts("\nИспользование хотя бы одного символа обязательно.");
        puts("\nДлина пароля не должна быть меньше 8 символов.\n");

        scanf("%99s", password);
        if (check_password(password)) {
            struct sha256 sha;
            char hash_hex[65];
            sha256_init(&sha);
            sha256_append(&sha, password, strlen(password));
            sha256_finalize_hex(&sha, hash_hex);
            hash_hex[strcspn(hash_hex, "\n")] = 0;
            users[*users_count -1].user_data.password = malloc(65*sizeof(char));
            strcpy(users[*users_count - 1].user_data.password, hash_hex);
            is_actual = 0;
        } else {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
            GetConsoleScreenBufferInfo(handle, &originalAttributes);
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
            puts("Попробуйте еще раз!");
            SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
        }
    }

    printf("\nВведите ваш email : ");
    char email[100];
    scanf("%99s", email);
    users[*users_count - 1].user_data.email = malloc(strlen(email) + 1);
    if (users[*users_count - 1].user_data.email == NULL) {
        perror("Failed to allocate memory for email");
        free(users[*users_count - 1].fullname);
        free(users[*users_count - 1].birthday);
        return;
    }
    strcpy(users[*users_count - 1].user_data.email, email);

    printf("\nНомер вашего банковского счета :  ");
    char bank_account_number[16];
    generate_bank_account_number(bank_account_number, BANK_ACCOUNT_NUMBER_LENGTH);
    print_formatted_number(bank_account_number);
    strcpy(users[*users_count - 1].card.card_number, bank_account_number);

    printf("\nВведите начальный депозит USD : ");
    float dep;
    while (1) {
        scanf("%f", &dep);
        if (dep < 1 || isinf(dep) || dep > FLT_MAX) {
            printf("\nНедопустимое значение. Попробуйте снова!\n");
        } else {
            break;
        }
    }
    users[*users_count - 1].card.balance = dep;

    if (users[*users_count - 1].card.balance != 0) {
        puts("\nПервый депозит одобрен!");
    }
    strcpy(users[*users_count - 1].card.currency, "USD");

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
    GetConsoleScreenBufferInfo(handle, &originalAttributes);
    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
    printf("Ваша регистрация прошла успешно!");
    SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
    while (getchar() != '\n');
}


User* add_user(User* users, unsigned int* count_of_users) {
    (*count_of_users)++;
    users = realloc(users, (*count_of_users) * sizeof(User));
    read_user(users, count_of_users);
    return users;
}
void admin_info(User* user,int index){

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
    GetConsoleScreenBufferInfo(handle, &originalAttributes);
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    printf("------------------------------------------------");
    printf("\n\tДобро пожаловать %s\n", user[index].fullname);
    printf("\n    Номер вашего счёта : ");
    user[index].card.card_number[16] = '\0';
    print_formatted_number(user[index].card.card_number);
    printf("\n");
    printf("\n    Адрес Электронной почты : %s ",user[index].user_data.email);
    printf("\n");
    printf("\n\t\t  Admin Panel\n");
    printf("------------------------------------------------");
    SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
}

void admin_panel(User* user,unsigned int *users_count,int index) {

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
    GetConsoleScreenBufferInfo(handle, &originalAttributes);
    int flag = 1;
    int menu = 1;

    while (flag) {
        menu = 1;
        admin_info(user,index);

        while (menu) {
            int option;
            printf("\n0-Просмотреть баланс\n1-Отправить деньги\n2-Сменить валюту баланса\n3-Изменить информацию аккаунта\n4-Показать всех клиентов\n5-Удалить клиента\n6-Выйти из аккаунта\n");
            printf("Введите действие: ");
            scanf("%d", &option);
            int del_index = -1;
            switch (option) {
                case 0:
                    system("cls");
                    printf("\nБаланс вашего счёта : %.2f %s\n", user[index].card.balance, user[index].card.currency);
                    break;

                case 1:
                    system("cls");
                    printf("1-Отправить по номеру карты, 2-Назад\n");// 2-Отправить по ФИО держателя карты - inactive
                    int send_option;
                    printf("Ваш выбор : ");
                    scanf("%d", &send_option);
                    if (send_option == 1) {
                        char buffer[50];
                        system("cls");
                        printf("Введите номер карты: ");
                        scanf("%*[\n]");
                        scanf("%[^\n]", buffer);
                        int trader_index;
                        for (int j = 0; j < *users_count; j++) {
                            if (j == index) {
                                continue;
                            }
                            if (strcmp(user[j].card.card_number, buffer) == 0) {
                                float transfer_value;
                                printf("Введите сумму денег, которую вы хотите перевести %s\n", user[j].fullname);
                                scanf("%f", &transfer_value);

                                if (strcmp(user[j].card.currency, user[index].card.currency) == 0) {
                                    float commission = comission(&user[index].card, user, users_count, transfer_value);

                                    if (user[index].card.balance < (transfer_value + commission)) {
                                        puts("Недостаточно средств");
                                        return;
                                    }

                                    user[index].card.balance -= (transfer_value + commission);
                                    user[j].card.balance += transfer_value;
                                } else {
                                    float commission = comission(&user[index].card, user, users_count, transfer_value);
                                    printf("\nКомиссионный сбор при переводе средств на счет в другой валюте составит :%.2f\n",
                                           commission);
                                    printf("Желаете продолжить? 1-Да, 2-Нет: ");
                                    int chose;
                                    scanf("%d", &chose);
                                    float unchanged_value;
                                    switch (chose) {
                                        case 1:
                                            if (user[index].card.balance < (transfer_value + commission)) {
                                                puts("Недостаточно средств");
                                                break;
                                            }
                                            unchanged_value = transfer_value + commission;
                                            break;
                                        case 2:

                                            return;
                                        default:
                                            printf("Incorrect input. Try again!\n");
                                            break;
                                    }

                                    const char *command = "curl -s -X GET https://api.exchangerate-api.com/v4/latest/USD -o response.json";
                                    int result = system(command);
                                    if (result == 0) {
                                        FILE *file_1 = fopen("response.json", "r");
                                        if (file_1) {
                                            fseek(file_1, 0, SEEK_END);
                                            long fileSize = ftell(file_1);
                                            fseek(file_1, 0, SEEK_SET);

                                            char *buffer = malloc(fileSize + 1);
                                            if (buffer) {
                                                fread(buffer, 1, fileSize, file_1);
                                                buffer[fileSize] = '\0';
                                                char currency[4];
                                                strcpy(currency, user[index].card.currency);

                                                char query[10];
                                                sprintf(query, "\"%s\":", currency);
                                                char *start = strstr(buffer, query);
                                                if (start) {
                                                    start += strlen(query);
                                                    char *end = strchr(start, ',');
                                                    if (end) {
                                                        *end = '\0';
                                                        float rate = atof(start);
                                                        transfer_value /= rate;
                                                    }
                                                }
                                                free(buffer);
                                            }
                                            fclose(file_1);
                                        }

                                        FILE *file_2 = fopen("response.json", "r");
                                        if (file_2) {
                                            fseek(file_2, 0, SEEK_END);
                                            long fileSize = ftell(file_2);
                                            fseek(file_2, 0, SEEK_SET);
                                            char *buffer_1 = malloc(fileSize + 1);
                                            if (buffer_1) {
                                                fread(buffer_1, 1, fileSize, file_2);
                                                buffer_1[fileSize] = '\0';
                                                char currency[4];
                                                strcpy(currency, user[j].card.currency);

                                                char query[10];
                                                sprintf(query, "\"%s\":", currency);
                                                char *start = strstr(buffer_1, query);
                                                if (start) {
                                                    start += strlen(query);
                                                    char *end = strchr(start, ',');
                                                    if (end) {
                                                        *end = '\0';
                                                        float rate = atof(start);
                                                        transfer_value *= rate;
                                                    }
                                                }
                                                free(buffer_1);
                                            }
                                            fclose(file_2);
                                        }
                                    }

                                    user[index].card.balance -= unchanged_value;
                                    user[j].card.balance += transfer_value;
                                }
                            }
                        }
                    }
                    else if(send_option == 2){
                        system("cls");
                        break;
                    }
                    else{
                        printf("Некорректный ввод. Попробуйте снова!");
                        Sleep(1000);
                        system("cls");
                        break;
                    }
                    break;
                case 2:
                    system("cls");
                    change_currency(user,index);
                    break;

                case 3:
                    system("cls");
                    change_profile(user,index);
                    break;

                case 4:
                    system("cls");
                    print_all_users(user,users_count);
                    break;

                case 5:
                    while(del_index < 0 || del_index > *users_count-1) {
                        printf("Введите номер клиента: ");
                        scanf("%d", &del_index);
                    }
                    user = delete_user_from_index(user, users_count, del_index);
                    save_data(user, users_count);
                    break;

                case 6:
                    printf("Выход из аккаунта...\n");
                    menu = 0;
                    flag = 0;
                    break;

                    default:
                        printf("Неверный ввод. Попробуйте снова!");
                    Sleep(1000);
                    system("cls");
                    break;
            }
        }
    }
}

void print_user(User users) {

    printf("ФИО клиента : %s\n", users.fullname);
    printf("Дата Рождения клиента : %s\n", users.birthday);

    printf("Номер Счёта: ");
    print_formatted_number(users.card.card_number);

    printf("\nАдрес Электронной почты:%s ",users.user_data.email);
    puts("\n");

    printf("Баланс на счёте: %.2f %s", users.card.balance,users.card.currency);
    puts("\n");

}

void print_all_users(User* users, unsigned int* users_count) {

    for (int i = 0; i < *users_count; i++) {

        printf("-----------------------------------\n");
        printf("CLIENT_INDEX: %d\n", i);
        users[i].card.card_number[16] = '\0';
        print_user(users[i]);

    }
    printf("-----------------------------------\n");
}

void save_data(User* users, unsigned int* users_count) {
    FILE* file = fopen("users.bin", "wb");
    if (file == NULL) {
        perror("Failed to open users.bin for writing");
        return;
    }

    fwrite(users_count, sizeof(unsigned int), 1, file);
    for (unsigned int i = 0; i < *users_count; i++) {
        unsigned int len;

        len = strlen(users[i].fullname) + 1;
        fwrite(&len, sizeof(unsigned int), 1, file);
        fwrite(users[i].fullname, sizeof(char), len, file);

        len = strlen(users[i].birthday) + 1;
        fwrite(&len, sizeof(unsigned int), 1, file);
        fwrite(users[i].birthday, sizeof(char), len, file);

        fwrite(users[i].user_data.login, sizeof(char), 50, file);

        len = strlen(users[i].user_data.password) + 1;
        fwrite(&len, sizeof(unsigned int), 1, file);
        fwrite(users[i].user_data.password, sizeof(char), len, file);

        len = strlen(users[i].user_data.email) + 1;
        fwrite(&len, sizeof(unsigned int), 1, file);
        fwrite(users[i].user_data.email, sizeof(char), len, file);

        fwrite(users[i].card.card_number, sizeof(char), 16, file);

        fwrite(&users[i].card.balance, sizeof(float), 1, file);

        fwrite(users[i].card.currency, sizeof(char), 3, file);
    }

    fclose(file);
}
User* init_data(unsigned int* users_count) {
    unsigned int len;
    FILE* file = fopen("users.bin", "rb");
    if (file == NULL) {
        perror("Failed to open users.bin for reading");
        return NULL;
    }

    fread(users_count, sizeof(unsigned int), 1, file);
    if (*users_count == 0) {
        fclose(file);
        return NULL;
    }

    User* users = malloc(*users_count * sizeof(User));
    if (users == NULL) {
        perror("Failed to allocate memory for users");
        fclose(file);
        return NULL;
    }

    for (unsigned int i = 0; i < *users_count; i++) {

        fread(&len, sizeof(unsigned int), 1, file);
        users[i].fullname = malloc(len * sizeof(char));
        if (users[i].fullname == NULL) {
            perror("Failed to allocate memory for fullname");
            free_users(users, i);
            fclose(file);
            return NULL;
        }
        fread(users[i].fullname, sizeof(char), len, file);

        fread(&len, sizeof(unsigned int), 1, file);
        users[i].birthday = malloc(len * sizeof(char));
        if (users[i].birthday == NULL) {
            perror("Failed to allocate memory for birthday");
            free(users[i].fullname);
            free_users(users, i);
            fclose(file);
            return NULL;
        }
        fread(users[i].birthday, sizeof(char), len, file);

        fread(users[i].user_data.login, sizeof(char), 50, file);

        fread(&len, sizeof(unsigned int), 1, file);
        users[i].user_data.password = malloc(len * sizeof(char));
        if (users[i].user_data.password == NULL) {
            perror("Failed to allocate memory for password");
            free(users[i].fullname);
            free(users[i].birthday);
            free_users(users, i);
            fclose(file);
            return NULL;
        }
        fread(users[i].user_data.password, sizeof(char), len, file);

        fread(&len, sizeof(unsigned int), 1, file);
        users[i].user_data.email = malloc(len * sizeof(char));
        if (users[i].user_data.email == NULL) {
            perror("Failed to allocate memory for email");
            free(users[i].fullname);
            free(users[i].birthday);
            free(users[i].user_data.password);
            free_users(users, i);
            fclose(file);
            return NULL;
        }
        fread(users[i].user_data.email, sizeof(char), len, file);

        fread(users[i].card.card_number, sizeof(char), 16, file);

        fread(&users[i].card.balance, sizeof(float), 1, file);

        fread(users[i].card.currency, sizeof(char), 3, file);
    }

    fclose(file);
    return users;
}

void free_users(User* users, unsigned int count) {
    for (unsigned int j = 0; j < count; j++) {
        free(users[j].fullname);
        free(users[j].birthday);
        free(users[j].user_data.email);
        free(users[j].user_data.password);
    }
    free(users);
}


void personal_info(User *user,int index){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
    GetConsoleScreenBufferInfo(handle, &originalAttributes);
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    printf("------------------------------------------------");
    printf("\n\tДобро пожаловать %s\n", user[index].fullname);
    printf("\nНомер вашего счёта : ");
    user[index].card.card_number[16] = '\0';
    print_formatted_number(user[index].card.card_number);
    printf("\n");
    printf("\nАдрес Электронной почты : %s ",user[index].user_data.email);
    printf("\n");
    printf("------------------------------------------------");
    SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
}

void user_panel(User *user, unsigned int *users_count, int index) {

    int flag = 1;
    int menu = 1;

    while (flag) {

        menu = 1;
        while (menu) {
            personal_info(user,index);
            int option;
            printf("\n0-Просмотреть баланс\n1-Отправить деньги\n2-Сменить валюту баланса\n3-Изменить личную информацию\n4-Выйти из аккаунта\n");
            printf("Введите действие: ");
            scanf("%d", &option);
            switch (option) {
                case 0:
                    system("cls");
                    printf("\nБаланс вашего счёта : %.2f %s\n", user[index].card.balance, user[index].card.currency);
                    break;
                case 1:
                    system("cls");
                    printf("1-Отправить по номеру карты, 2-Назад\n");//2-Отправить по ФИО держателя карты - inactive

                    int send_option;
                    printf("Ваш выбор : ");
                    scanf("%d", &send_option);
                    if (send_option == 1) {
                        char buffer[50];
                        system("cls");
                        printf("Введите номер карты: ");
                        scanf("%*[\n]");
                        scanf("%[^\n]", buffer);
                        int trader_index;
                        for (int j = 0; j < *users_count; j++) {
                            if (j == index) {
                                continue;
                            }
                            if (strcmp(user[j].card.card_number, buffer) == 0) {
                                float transfer_value;
                                printf("Введите сумму денег, которую вы хотите перевести %s\n", user[j].fullname);
                                scanf("%f", &transfer_value);

                                if (strcmp(user[j].card.currency, user[index].card.currency) == 0) {
                                    float commission = comission(&user[index].card, user, users_count, transfer_value);

                                    if (user[index].card.balance < (transfer_value + commission)) {
                                        puts("Недостаточно средств");
                                        return;
                                    }

                                    user[index].card.balance -= (transfer_value + commission);
                                    user[j].card.balance += transfer_value;
                                } else {
                                    float commission = comission(&user[index].card, user, users_count, transfer_value);
                                    printf("\nКомиссионный сбор при переводе средств на счет в другой валюте составит :%.2f\n", commission);
                                    printf("Желаете продолжить? 1-Да, 2-Нет: ");
                                    int chose;
                                    scanf("%d", &chose);
                                    float unchanged_value;
                                    switch (chose) {
                                        case 1:
                                            if (user[index].card.balance < (transfer_value + commission)) {
                                                puts("Недостаточно средств");
                                                break;
                                            }
                                            unchanged_value = transfer_value+commission;
                                            break;
                                        case 2:

                                            return;
                                        default:
                                            printf("Incorrect input. Try again!\n");
                                            Sleep(1000);
                                            system("cls");
                                            break;
                                    }

                                    const char *command = "curl -s -X GET https://api.exchangerate-api.com/v4/latest/USD -o response.json";
                                    int result = system(command);
                                    if (result == 0) {
                                        FILE *file_1 = fopen("response.json", "r");
                                        if (file_1) {
                                            fseek(file_1, 0, SEEK_END);
                                            long fileSize = ftell(file_1);
                                            fseek(file_1, 0, SEEK_SET);

                                            char *buffer = malloc(fileSize + 1);
                                            if (buffer) {
                                                fread(buffer, 1, fileSize, file_1);
                                                buffer[fileSize] = '\0';
                                                char currency[4];
                                                strcpy(currency, user[index].card.currency);

                                                char query[10];
                                                sprintf(query, "\"%s\":", currency);
                                                char *start = strstr(buffer, query);
                                                if (start) {
                                                    start += strlen(query);
                                                    char *end = strchr(start, ',');
                                                    if (end) {
                                                        *end = '\0';
                                                        float rate = atof(start);
                                                        transfer_value /= rate;
                                                    }
                                                }
                                                free(buffer);
                                            }
                                            fclose(file_1);
                                        }

                                        FILE *file_2 = fopen("response.json", "r");
                                        if (file_2) {
                                            fseek(file_2, 0, SEEK_END);
                                            long fileSize = ftell(file_2);
                                            fseek(file_2, 0, SEEK_SET);
                                            char *buffer_1 = malloc(fileSize + 1);
                                            if (buffer_1) {
                                                fread(buffer_1, 1, fileSize, file_2);
                                                buffer_1[fileSize] = '\0';
                                                char currency[4];
                                                strcpy(currency, user[j].card.currency);

                                                char query[10];
                                                sprintf(query, "\"%s\":", currency);
                                                char *start = strstr(buffer_1, query);
                                                if (start) {
                                                    start += strlen(query);
                                                    char *end = strchr(start, ',');
                                                    if (end) {
                                                        *end = '\0';
                                                        float rate = atof(start);
                                                        transfer_value *= rate;
                                                    }
                                                }
                                                free(buffer_1);
                                            }
                                            fclose(file_2);
                                        }
                                    }

                                    user[index].card.balance -= unchanged_value;
                                    user[j].card.balance += transfer_value;
                                }
                            }
                        }
                    }
                    else if(send_option==2){
                        system("cls");
                        break;
                    }
                    else{
                        printf("Неверный ввод. Попробуйте снова!");
                        Sleep(1000);
                        system("cls");
                    }
                    break;
                case 2:
                    system("cls");
                    change_currency(user, index);
                    break;

                case 3:
                    system("cls");
                    change_profile(user,index);
                    break;
                case 4:
                    printf("Выход из аккаунта...\n");
                    while (getchar() != '\n');
                    menu = 0;
                    flag = 0;
                    break;
                default:
                    while (getchar() != '\n');
                    printf("Неверный ввод. Пожалуйста, попробуйте снова.\n");
                    Sleep(1000);
                    system("cls");
                    break;
            }
        }
    }
}

void login_panel(User *users, unsigned int *users_count) {
    FILE *admins = fopen("admins.bin", "rb");
    if (admins == NULL) {
        perror("Failed to open admins.bin");
        return;
    }

    char buffer[50];
    char login[50];
    char password[65];
    char hash_hex[65];
    bool found = false;

    printf("Введите Логин: ");
    scanf("%49s", login);

    int index = -1;
    for (unsigned int i = 0; i < *users_count; i++) {
        if (strcmp(users[i].user_data.login, login) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nНе удалось найти аккаунт\n");
        Sleep(600);
        system("cls");
        fclose(admins);
        return;
    }

    rewind(admins);
    while (fread(buffer, sizeof(char), 50, admins) == 50) {
        if (strcmp(buffer, login) == 0) {
            found = true;
            break;
        }
    }

    int try_count = 3;
    while (try_count > 0) {
        printf("\t -> Введите пароль для своего аккаунта <-\n");
        scanf("%64s", password);

        struct sha256 sha;
        sha256_init(&sha);
        sha256_append(&sha, (const uint8_t*)password, strlen(password));
        sha256_finalize_hex(&sha, hash_hex);
        hash_hex[strcspn(hash_hex, "\n")] = 0;

        if (strcmp(users[index].user_data.password, hash_hex) == 0) {
            fclose(admins);
            if (found) {
                system("cls");
                admin_panel(users, users_count, index);
            } else {
                system("cls");
                user_panel(users, users_count, index);
            }
            return;
        } else {
            printf("Неправильный пароль\n");
            Sleep(600);
            system("cls");
            try_count--;
            printf("Осталось попыток: %d\n", try_count);

            if (try_count == 0) {
                char email[100];
                strcpy(email, users[index].user_data.email);
                char new_password[7];
                generate_password(new_password);

                HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
                GetConsoleScreenBufferInfo(handle, &originalAttributes);
                SetConsoleTextAttribute(handle, FOREGROUND_RED);

                printf("\tНовый пароль отправлен вам на электронную почту.\n");

                SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
                Sleep(1000);
                send_email(email, "Password Recovery", new_password);

                struct sha256 sha1;
                char hash_hex1[65];
                sha256_init(&sha1);
                sha256_append(&sha1, (const uint8_t*)new_password, strlen(new_password));
                sha256_finalize_hex(&sha1, hash_hex1);
                hash_hex1[strcspn(hash_hex1, "\n")] = 0;
                strcpy(users[index].user_data.password, hash_hex1);

                fclose(admins);
                system("cls");
                return;
            }
        }
    }
    fclose(admins);
}



void generate_code(char *code) {
    int CODE_LENGTH = 5;
    srand(time(NULL));

    for (size_t i = 0; i < CODE_LENGTH; ++i) {

        code[i] = '0' + (rand() % 10);

    }

    code[CODE_LENGTH] = '\0';
}
void change_profile(User *user, int index) {
    printf("\nИзменить Пароль - 1\n");
    printf("\nИзменить Адрес электронной почты - 2\n");
    printf("\nВернуться обратно - 3\n");
    int option;
    printf("\nВаш выбор :");
    scanf("%d", &option);
    switch (option) {
        case 1: {
            printf("Вам на почту отправлен код для подтверждения личности\n");
            char code[6];
            generate_code(code);
            send_email(user[index].user_data.email, "Код для подтверждения личности", code);
            char input_code[6];
            int try_count = 3;
            while (try_count > 0) {
                printf("Осталось попыток: %d\n", try_count);
                printf("Введите код: ");
                scanf("%5s", input_code); // Чтение кода от пользователя
                if (strcmp(input_code, code) == 0) {
                    char password[100];

                    while(1) {
                        printf("Введите пароль: ");
                        scanf("%99s", password);


                        if(check_password(password)){
                            break;
                        }
                    }

                    struct sha256 sha_recovery;
                    char hash_hex_changed[65];
                    sha256_init(&sha_recovery);
                    sha256_append(&sha_recovery, password, strlen(password));
                    sha256_finalize_hex(&sha_recovery, hash_hex_changed);
                    strcpy(user[index].user_data.password,hash_hex_changed);


                    printf("\nПароль изменен!\n");
                    Sleep(1000);
                    system("cls");
                    break;
                } else {
                    printf("Неверный код, попробуйте снова!\n");
                    try_count--;
                }
            }
            if (try_count == 0) {
                printf("Попытки исчерпаны. Пароль не был изменен.\n");
            }
            break;
        }
        case 2: {
            printf("\tДля подтверждения действия введите ваш пароль:\n");

            int try_p_count = 3;
            while (try_p_count > 0) {
                printf("Осталось попыток: %d\n", try_p_count);
                char password[100];
                scanf("%99s", password);
                struct sha256 sha_recovery;
                char hash_hex_changed[65];
                sha256_init(&sha_recovery);
                sha256_append(&sha_recovery, password, strlen(password));
                sha256_finalize_hex(&sha_recovery, hash_hex_changed);

                if (strcmp(user[index].user_data.password, hash_hex_changed) == 0) {
                    char email[100];
                    printf("Введите ваш новый адрес электронной почты: ");
                    scanf("%99s", email);
                    strcpy(user[index].user_data.email, email);
                    printf("\nАдрес электронной почты изменен!\n");
                    break;
                } else {
                    printf("Неверный пароль, попробуйте снова!\n");
                    try_p_count--;
                }
            }
            if (try_p_count == 0) {
                printf("Попытки исчерпаны. Адрес электронной почты не был изменен.\n");
            }
            break;
        }

        case 3:
            system("cls");
            break;

        default:
            printf("Неверный выбор.\n");
            Sleep(1000);
            system("cls");
            break;
    }
}
            User *delete_user_from_index(User *users, unsigned int *users_count, unsigned int deleted_index) {
                if (*users_count <= 0) {
                    return users;
                }
                free(users[deleted_index].fullname);
                int flag = calculate_age(users[deleted_index].birthday);
                if (flag != 0) {
                    free(users[deleted_index].birthday);
                }
                for (int i = deleted_index; i < *users_count - 1; i++) {
                    users[i] = users[i + 1];
                }
                *users_count -= 1;
                if (*users_count != 0)users = realloc(users, *users_count * sizeof(User));
                else {
                    free(users);
                    users = NULL;
                }
                return users;
            }

            void change_currency(User *user, int index) {

                if (strcmp(user[index].card.currency, "USD") == 0) {

                    const char *command = "curl -s -X GET https://api.exchangerate-api.com/v4/latest/USD -o response.json";
                    int result = system(command);
                    if (result == 0) {

                        FILE *file = fopen("response.json", "r");
                        if (file) {
                            fseek(file, 0, SEEK_END);
                            long fileSize = ftell(file);
                            fseek(file, 0, SEEK_SET);

                            char *buffer = malloc(fileSize + 1);
                            if (buffer) {
                                fread(buffer, 1, fileSize, file);
                                buffer[fileSize] = '\0';

                                printf("Введите валюту (BYN, RUB, EUR, UAH, ISL, JPY, CZK, PLN, KGS, COP, ...): ");
                                char currency[4];
                                scanf("%s", currency);

                                // Формируем строку запроса для поиска курса
                                char query[10];
                                sprintf(query, "\"%s\":", currency);

                                // Находим позицию начала курса
                                char *start = strstr(buffer, query);
                                if (start) {
                                    start += strlen(query);
                                    char *end = strchr(start, ',');
                                    if (end) {
                                        *end = '\0'; // Удаляем запятую в конце значения
                                        float rate = atof(start);
                                        user[index].card.balance *= rate;
                                        strcpy(user[index].card.currency, currency);
                                        system("cls");
                                        puts("\n------------------------------------------");

                                        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
                                        CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
                                        GetConsoleScreenBufferInfo(handle, &originalAttributes);
                                        SetConsoleTextAttribute(handle, FOREGROUND_RED);

                                        printf("\tВалюта успешно изменена!");

                                        SetConsoleTextAttribute(handle, originalAttributes.wAttributes);

                                        puts("\n------------------------------------------\n");

                                    }
                                } else {
                                    printf("Курс для валюты %s не найден.\n", currency);
                                    Sleep(1000);
                                    system("cls");
                                }

                                free(buffer);
                            }

                            fclose(file);
                        } else {
                            printf("Не удалось открыть файл response.json.\n");
                        }
                    } else {
                        printf("Нет доступа к интернету.\n");
                    }


                } else {

                        const char *command = "curl -s -X GET https://api.exchangerate-api.com/v4/latest/USD -o response.json";
                        int result = system(command);
                        if (result == 0) {
                            FILE *file = fopen("response.json", "r");
                            if (file) {
                                fseek(file, 0, SEEK_END);
                                long fileSize = ftell(file);
                                fseek(file, 0, SEEK_SET);

                                char *buffer = malloc(fileSize + 1);
                                printf("Введите валюту (BYN, RUB, EUR, UAH, ISL, JPY, CZK, PLN, KGS, COP, ...): ");
                                char cur[4];
                                scanf("%s",cur);
                                if (buffer) {
                                    fread(buffer, 1, fileSize, file);
                                    buffer[fileSize] = '\0';

                                    char currency[4];
                                    char tr_currency[4];
                                    strcpy(currency,cur);
                                    strcpy(tr_currency, user[index].card.currency);

                                    char query[10];
                                    sprintf(query, "\"%s\":", currency);

                                    char tr_query[10];
                                    sprintf(tr_query, "\"%s\":", tr_currency);

                                    char *pre_start = strstr(buffer, tr_query);

                                    if (pre_start) {
                                        pre_start += strlen(tr_query);
                                        char *pre_end = strchr(pre_start, ',');
                                        if (pre_end) {
                                            *pre_end = '\0'; // Удаляем запятую в конце значения
                                            float pre_rate = atof(pre_start);
                                            user[index].card.balance /= pre_rate;
                                            strcpy(user[index].card.currency, "USD");
                                            if (strcmp(tr_currency, "USD") == 0) {
                                                printf("\n %s\n", query);
                                                return;
                                            }
                                        }
                                    }
                                    free(buffer);
                                    fclose(file);
                                }
                                FILE *file = fopen("response.json", "r");
                                fseek(file, 0, SEEK_END);
                                long fileSize_1 = ftell(file);
                                fseek(file, 0, SEEK_SET);
                                char query[10];
                                char currency[4];
                                strcpy(currency,cur);
                                sprintf(query, "\"%s\":", currency);
                                char *buffer_1 = malloc(fileSize_1 + 1);
                                if(buffer_1){
                                    fread(buffer_1, 1, fileSize, file);
                                    buffer_1[fileSize] = '\0';
                                    char *start_tr = strstr(buffer_1, query);
                                    if (start_tr) {
                                        start_tr += strlen(query);
                                        char *end = strchr(start_tr, ',');
                                        if (end) {
                                            *end = '\0'; // Удаляем запятую в конце значения
                                            float rate = atof(start_tr);
                                            user[index].card.balance *= rate;
                                            strcpy(user[index].card.currency, currency);
                                            puts("\n------------------------------------------");

                                            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
                                            CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
                                            GetConsoleScreenBufferInfo(handle, &originalAttributes);
                                            SetConsoleTextAttribute(handle, FOREGROUND_RED);

                                            printf("\tВалюта успешно изменена!");
                                            SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
                                            puts("\n------------------------------------------\n");

                                        }
                                    } else {
                                        printf("Курс для валюты %s не найден.\n", currency);
                                    }

                                    free(buffer_1);
                                }

                                fclose(file);
                        } else {
                            printf("Не удалось открыть файл response.json.\n");
                        }
                    } else {
                        printf("Проверьте подключение к интернету.\n");
                    }


                }


            }

            int is_request_successful() {
                const char *command = "curl -s -X GET https://api.exchangerate-api.com/v4/latest/USD -o response.json";
                int result = system(command);

                return result;
            }

            void check_connection(){
                HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
                GetConsoleScreenBufferInfo(handle, &originalAttributes);
                int is_request;
                is_request = is_request_successful();
                if (is_request) {
                    system("cls");
                    SetConsoleTextAttribute(handle, FOREGROUND_RED);
                    printf("------------------------------------------------");
                    printf("\n\tБанк работает в offline-режиме\n");
                    printf("------------------------------------------------");
                    SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
                }
                else{
                    system("cls");
                    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                    printf("------------------------------------------------");
                    printf("\n\tБанк работает в online-режиме\n");
                    printf("------------------------------------------------");
                    SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
                }
}



void manage() {
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO originalAttributes;
    GetConsoleScreenBufferInfo(handle, &originalAttributes);

    FILE *file = fopen("users.bin", "rb");
    if (file == NULL) {
        perror("Failed to open users.bin for reading");
        return;
    }

    unsigned int users_count = 0;
    if (fread(&users_count, sizeof(unsigned int), 1, file) != 1) {
        if (ferror(file)) {
            perror("Failed to read users_count from users.bin");
            fclose(file);
            return;
        }
    }
    fclose(file);

    User *user = init_data(&users_count);
    if (user == NULL && users_count > 0) {
        // If users were expected but loading failed, handle the error
        fprintf(stderr, "Failed to load user data\n");
        return;
    }

    printf("Проверка интернет соединения...\n");
    bool flag = false;
    int choice;
    while (!flag) {
        check_connection();
        printf("\n0 - Выход.\n1 - Добавить клиента банка.\n2 - Вход в аккаунт.\n");
        printf("Ваш выбор: ");
        if (scanf("%d", &choice) != 1) {
            SetConsoleTextAttribute(handle, FOREGROUND_RED);
            printf("\nНекорректный выбор. Пожалуйста, попробуйте снова.\n");
            SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
            while (getchar() != '\n'); // Clear the input buffer
        } else {
            switch (choice) {
                case 1:
                    user = add_user(user, &users_count);
                    Sleep(1000);
                    save_data(user, &users_count);
                    system("cls");
                    break;
                case 2:
                    login_panel(user, &users_count);
                    save_data(user, &users_count);
                    system("cls");
                    break;
                case 0:
                    flag = true;
                    break;
                default:
                    SetConsoleTextAttribute(handle, FOREGROUND_RED);
                    printf("\nНекорректный выбор. Пожалуйста, попробуйте снова.\n");
                    SetConsoleTextAttribute(handle, originalAttributes.wAttributes);
                    break;
            }
        }
    }
    free_users(user, users_count);
}
