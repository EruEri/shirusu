#ifndef __SHIRUSU_MAIN_H__
#define __SHIRUSU_MAIN_H__

#include <stdbool.h>

struct shiru_main {
    const char* name;
    const char* message;
    bool help;
};

extern struct shiru_main shiru_main_opts;

int shiru_main_parse(int argc, const char**);
int shiru_main_help(void);
int shiru_main_exec(const struct shiru_main*);

#endif