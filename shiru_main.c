#include "shiru_main.h"
#include "stdlib.h"
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

struct shiru_main shiru_main_opts = {
    .message = NULL,
    .name = NULL,
    .help = false,
};

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"message", required_argument, 0, 'm'},
    {"name", required_argument, 0, 'n'},
    {0, 0, 0, 0}
};


int shiru_main_parse(int argc, const char** argv) {
    int status = 0;
    while (true) {
        int option_index = 0;
        int res = getopt_long(
            argc, (char*const*) argv, "hm:n:", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
        case 'm':
            shiru_main_opts.message = optarg;
            break;
        case 'n':
            shiru_main_opts.name = optarg;
            break;
        case 'h':
            shiru_main_opts.help = true;
            break;
        case '?':
            status = 1;
            break;
        }
    }
    return status;
}

int shiru_main_help(void) {
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

int shiru_main_exec(const struct shiru_main* opts) {
    if (opts->help) {
        shiru_main_help();
        return 0;
    }

    return 0;
}