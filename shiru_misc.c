#include <stdlib.h>
#include <stdio.h>
#include "shiru_misc.h"

const char*const VERSION = "0.1.0";
const char*const AUTHOR = "Yves Ndiaye";

const char*const usage = "usage: shirusu [COMMAND] ...";

int show_version() {
    fprintf(stdout, "%s\n", VERSION);
    exit(0);
}


int show_help(void) {
    printf("\
Usage:\n\
    shiruku : A simple fast thought note taker\n\n\
    shiruku [COMMAND] [OPTIONS]... \n\
Options:\n\
    -n, --name=NAME        Name of the new note\n\
    -m, --message=MESSAGE  Content of the note\n\
    -h, --help             Show help\n\
        --version          Show version\n\
Commands:\n\
    init                   Initialiaze init\n\
    list                   List notes\n\
"
);
    return 0;
}