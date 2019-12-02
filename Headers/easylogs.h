#ifndef EASYLOGS_EASYLOGS_H
#define EASYLOGS_EASYLOGS_H

#define PREFIX_DEBUG "[DEBUG] "
#define PREFIX_INFO "[INFO] "
#define PREFIX_WARNING "[WARNING] "
#define PREFIX_ERROR "[ERROR] "

//useless to change - this is a static library
#define LOG_NAME "output.log"

void output_logs_str(const char prefix[], const char str[], ...)__attribute__((format(printf,2, 3)));
void close_file(void);
void get_log_file(void);

#endif //EASYLOGS_EASYLOGS_H
