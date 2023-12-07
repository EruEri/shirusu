#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

const char*const VERSION = "0.1.0";
const char*const AUTHOR = "";

const char* usage = "usage: shirusu [OPTIONS...]";

const char* synosis = \
"shirusu ([--create] | [-l | --list] | [-n <note_name> | --name <note_name>]) [-h | --help] [--version]";

const char* help = \
"\
\
";

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"name", required_argument, 0, 'n'},
    {"list", no_argument, 0, 'l'},
    {"create", no_argument, 0, 'c'},
    {0, 0, 0, 0}
};

struct shirusu_options {
    bool version;
    bool help;
    bool list;
    bool create;
    const char* note_name;
};

static struct shirusu_options options = {
    .version = false, 
    .help = false,
    .list = false,
    .create = false,
    .note_name = NULL
};

int show_option() {
    return fprintf(stdout, "version = %u\nhelp = %u\nname = %s\n", options.version, options.help, options.note_name);
}

int check_mutual_exclusive() {
    return 0;
}

int main(int argc, const char** argv) {

    while (true) {
        int option_index = 0;
        int res = getopt_long(argc, (char*const*) argv, "ln:v", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
        case 'v':
            options.version = true;
            break;
        case 'h':
            options.help = true;
            break;
        case 'n':
            options.note_name = optarg;
            break;
        case 'l':
            options.list = true;
            break;
        case 'c':
            options.create = true;
            break;
        case '?':
            fprintf(stderr, "%s\n", usage);
            fprintf(stderr, "%s\n", synosis);
            exit(1);
        }
    }

    show_option();
}