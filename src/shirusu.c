////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
// This file is part of Shirusu : A little note taker                                         //
// Copyright (C) 2023 Yves Ndiaye                                                             //
//                                                                                            //
// Shirusu is free software: you can redistribute it and/or modify it under the terms         //
// of the GNU General Public License as published by the Free Software Foundation,            //
// either version 3 of the License, or (at your option) any later version.                    //
//                                                                                            //
// Shirusu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;       //
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR           //
// PURPOSE.  See the GNU General Public License for more details.                             //
// You should have received a copy of the GNU General Public License along with Shirusu.      //
// If not, see <http://www.gnu.org/licenses/>.                                                //
//                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include "../include/shiru_create.h"
#include "../include/shiru_list.h"
#include "../include/shiru_main.h"
#include "../include/shiru_misc.h"


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
};

int show_common_option(struct shiru_options* opts) {
    if (opts->version) {
        show_version();
        exit(0);
    }
    return 0;
};

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
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

int parse_options_common(int argc, const char** argv, bool* version) {
    opterr = 0;
    while (true) {
        int option_index = 0;
        int res = getopt_long(argc, (char*const*) argv, "", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
        case 'v':
            *version = true;
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
    parse_options_common(argc, argv, &version);
    optind = 1;
    opts->version = version;
    opts->subcommand = subcommand;
    show_common_option(opts);
    switch (subcommand) {
    case SHIRU_NO_SUB: {
        shiru_main_parse(argc, argv);
        opts->options.o_main = shiru_main_opts;
        break;
    }
    case SHIRU_SUB_INIT: {
        shiru_create_parse(argc, argv);
        opts->options.o_create = shiru_create_opts;
        break;
    }
    case SHIRU_SUB_LIST: {
        shiru_list_parse(argc, argv);
        opts->options.o_list = shiru_list_opts;
        break;
    }
    };

    return 0;
}

int main_exec(struct shiru_options* opts) {
    switch (opts->subcommand) {
    case SHIRU_NO_SUB:
        return shiru_main_exec(&opts->options.o_main);
    case SHIRU_SUB_INIT:
        return shiru_create_exec(&opts->options.o_create);
    case SHIRU_SUB_LIST:
        return 0;
    }

    return 0;
}

int main(int argc, const char** argv) {
    struct shiru_options opts = {};
    parse_options(argc, argv, &opts);
    return main_exec(&opts);
}
