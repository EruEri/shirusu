#include <stdlib.h>
#include <stdio.h>
#include "../include/shiru_misc.h"

const char*const VERSION = "0.1.0";
const char*const AUTHOR = "Yves Ndiaye";
const char*const SHIRUSU_NAME = "shirusu";
const char*const usage = "usage: shirusu [COMMAND] ...";

int show_version() {
    fprintf(stdout, "%s\n", VERSION);
    exit(0);
}