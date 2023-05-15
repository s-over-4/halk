#ifndef LOG_H
#define LOG_H


#include <stdio.h>


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


void log_dbg(char* content);
void log_inf(char* content);
void log_war(char* content);
void log_err(char* content);


#endif
