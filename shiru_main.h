#ifndef __SHIRUSU_MAIN_H__
#define __SHIRUSU_MAIN_H__

 
struct shiru_main {
    const char* name;
    const char* message;
};

extern struct shiru_main shiru_main_opts;

int shiru_main_parse(int argc, const char**);

#endif