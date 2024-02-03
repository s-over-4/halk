#include "include/util.h"

void* ecalloc(size_t nmemb, size_t size) {
   void* p;

   if (! (p = calloc(nmemb, size))) { DIE("Failed to calloc:"); }

   return p;
}

void* emalloc(size_t size) {
   void* p;

   if (! (p = malloc(size))) { DIE("Failed to malloc:"); }

   return p;
}

void* erealloc(void* dest, size_t size) {
   void* p;

   if (! (p = realloc(dest, size))) { DIE("Failed to realloc:"); }

   return p;
}
