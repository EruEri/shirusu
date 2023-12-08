#ifndef __SHIRUSU_CREATE_H__
#define __SHIRUSU_CREATE_H__

 
struct shiru_create {};

extern struct shiru_create shiru_create_opts;

int shiru_create_parse(int argc, const char**);

#define ENV_XDG_DATA_HOME "XDG_DATA_HOME"

#endif