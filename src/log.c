#include "include/log.h"


void log_dbg(char* content) {
   fprintf(stderr, KMAG "[DEBUG] %s%s\n", KNRM, content);
};

void log_inf(char* content) {
   fprintf(stderr, KBLU "[INFO] %s%s\n", KNRM, content);
};

void log_war(char* content) {
   fprintf(stderr, KYEL "[WARNING] %s%s\n", KNRM, content);
};
   
void log_err(char* content) {
   fprintf(stderr, KRED "[ERROR] %s%s\n", KNRM, content);
};
