#include "../include/shiru_create.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <pwd.h>
#include <getopt.h>


static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

struct shiru_create shiru_create_opts = {
    .help = false
};

int shiru_create_parse(int argc, const char** argv) {
    while (true) {
        int option_index = 0;
        int res = getopt_long(argc, (char*const*) argv, "", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
        case 'h':
            shiru_create_opts.help = true;
            break;
        case '?':
            break;
        }
    }

    return 0;
}

int shiru_create_exec(const struct shiru_create * opts) {
    if (opts->help) {
        shiru_create_help();
        return 0;
    }
    return 0;
}


int shiru_create_help(void) {
      printf("\
Usage:\n\
    shirusu init - Initialiaze shirusu\n\n\
    shirusu init [OPTIONS]... \n\
Description:\n\
    Initialiaze shirusu by creating a directory in the $XDG_DATA_HOME directory\n\
Options:\n\
    -h, --help             Show help\n\
        --version          Show version\n\
"
);
    return 0;  
}


int shirisu_create() {
    struct passwd *pw = getpwuid(getuid());
    const char* home_dir = pw->pw_dir;
    return -1;
}