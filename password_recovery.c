//
//
// Created by mzitr on 21.05.2024.
//
//
#include "functions.h"

#define FROM    "<bank.application.pract@mail.ru>"
#define SMTP_URL "smtp://smtp.mail.ru:587"
#define USERNAME "bank.application.pract@mail.ru"
#define PASSWORD "75mV1UWCZ5D81u09RhzN"

struct upload_status {
    int lines_read;
    const char **payload_text;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
        return 0;
    }

    data = upload_ctx->payload_text[upload_ctx->lines_read];

    if (data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;
        return len;
    }

    return 0;
}

void send_email(const char *to, const char *subject, const char *message)
{
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx = { 0 };

    static const char *headers[] = {
            "To: ",
            "From: " FROM "\r\n",
            "Subject: ",
            "\r\n",
            NULL
    };

    const char *payload_text[6];
    char to_header[256];
    char subject_header[256];
    char message_body[1024];

    snprintf(to_header, sizeof(to_header), "To: %s\r\n", to);
    snprintf(subject_header, sizeof(subject_header), "Subject: %s\r\n", subject);
    snprintf(message_body, sizeof(message_body), "%s\r\n", message);

    payload_text[0] = to_header;
    payload_text[1] = headers[1];
    payload_text[2] = subject_header;
    payload_text[3] = headers[3];
    payload_text[4] = message_body;
    payload_text[5] = NULL;

    upload_ctx.payload_text = payload_text;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, USERNAME);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, PASSWORD);
        curl_easy_setopt(curl, CURLOPT_URL, SMTP_URL);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

        recipients = curl_slist_append(recipients, to);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}


