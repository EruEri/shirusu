#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

const char*const VERSION = "0.1.0";
const char*const AUTHOR = "";

const char* usage = "usage: shirusu [OPTIONS...]";

const char* help = \
"\
\
";

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

struct shirusu_options {
    bool version;
    bool help;
};

static struct shirusu_options options = {
    .version = false, 
    .help = false
};

int main(int argc, const char** argv) {

    while (true) {
        int option_index = 0;
        int res = getopt_long(argc, (char*const*) argv, "vh", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
        case 'v':
            options.version = true;
        case 'h':
            options.help = true;
        break;
        case '?':
            fprintf(stderr, "Unknown option\n");
            break;
        }
    }

    if (options.version) {
        fprintf(stdout, "%s\n", VERSION);
    } else if (options.help) {
        fprintf(stdout, "%s\n", "help");
    }

}