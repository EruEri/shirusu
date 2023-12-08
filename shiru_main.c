#include "shiru_main.h"
#include "stdlib.h"
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

struct shiru_main shiru_main_opts = {
    .message = NULL,
    .name = NULL,
};

static struct option long_options[] = {
    {"name", required_argument, 0, 'n'},
    {"message", required_argument, 0, 'm'},
    {0, 0, 0, 0}
};


int shiru_main_parse(int argc, const char** argv) {
    int status = 0;
    while (true) {
        int option_index = 0;
        int res = getopt_long(
            argc, (char*const*) argv, "m:n:", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
        case 'm':
            shiru_main_opts.message = optarg;
            break;
        case 'n':
            shiru_main_opts.name = optarg;
            break;
        case '?':
            status = 1;
            break;
        }
    }
    return status;
}