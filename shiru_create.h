#ifndef __SHIRUSU_CREATE_H__
#define __SHIRUSU_CREATE_H__

 
#include <stdbool.h>

struct shiru_create {
    bool help;
};

extern struct shiru_create shiru_create_opts;

int shiru_create_parse(int argc, const char** argv);
int shiru_create_help(void);
int shiru_create_exec(const struct shiru_create*);

#define ENV_XDG_DATA_HOME "XDG_DATA_HOME"

#endif