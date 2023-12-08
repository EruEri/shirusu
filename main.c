#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include "shiru_create.h"
#include "shiru_list.h"
#include "shiru_main.h"
#include "shiru_misc.h"
#include <string.h>

enum shiru_subcommand {
    SHIRU_NO_SUB,
    SHIRU_SUB_INIT,
    SHIRU_SUB_LIST,
};

struct shiru_options {
    enum shiru_subcommand subcommand;
    union {
        struct shiru_create o_create;
        struct shiru_list o_list;
        struct shiru_main o_main;
    } options;
    bool version;
    bool help;
};

const char* usage = "usage: shirusu [COMMAND] ...";

const char* synosis = \
"\
shirusu  [-i | --init]\n\
        [-l | --list]\n\
        [-m <message>| --message <message>] [-n <note_name> | --name <note_name>]\n\
        [-h | --help] [--version]\
";

const char* help = \
"\
\
";

int show_version() {
    fprintf(stdout, "%s\n", VERSION);
    exit(0);
}

int show_help() {
    fprintf(stdout, "%s\n", usage);
    exit(0);
}

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

enum shiru_subcommand parse_subcommand(int argc, const char** argv) {
    const char* first = argv[1];
    if (strcmp(first, "list") == 0) {
        return SHIRU_SUB_LIST;
    } else if (strcmp(first, "init") == 0) {
        return SHIRU_SUB_INIT;
    } else {
        return SHIRU_NO_SUB;
    }
}

int parse_options_common(int argc, const char** argv, bool* help, bool* version) {
    opterr = 0;
    while (true) {
        int option_index = 0;
        int res = getopt_long(argc, (char*const*) argv, "h", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
        case 'v':
            *version = true;
            break;
        case 'h':
            *help = true;
            break;
        case '?':
            break;
        }
    }
    opterr = 1;
    return 0;
}

int parse_options(int argc, const char** argv, struct shiru_options* opts) {
    if (argc < 2) return 0;
    enum shiru_subcommand subcommand = parse_subcommand(argc, argv);
    bool version = false;
    bool help = false;
    parse_options_common(argc, argv, &help, &version);
    optind = 1;
    opts->help = help;
    opts->version = version;
    opts->subcommand = subcommand;
    switch (subcommand) {
    case SHIRU_NO_SUB: {
        shiru_main_parse(argc, argv);
        opts->options.o_main = shiru_main_opts;
        break;
    }
    optind +=1;
    case SHIRU_SUB_INIT: {
        shiru_create_parse(argc, argv + 1);
        opts->options.o_create = shiru_create_opts;
        break;
    }
    case SHIRU_SUB_LIST: {
        shiru_list_parse(argc, argv + 1);
        opts->options.o_list = shiru_list_opts;
        break;
    }
    };

    return 0;
} 

int main(int argc, const char** argv) {
    struct shiru_options opts = {};
    parse_options(argc, argv, &opts);
    if (opts.help) {
        show_help();
    } else if (opts.version) {
        show_version();
    }

    // for (int i = 0; i < argc; i+=1) {
    //     printf("%s\n", argv[i]);
    // }
    // shiru_main_parse(argc, argv);
    
}