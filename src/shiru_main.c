////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
// This file is part of Shiruku : A little note taker                                         //
// Copyright (C) 2023 Yves Ndiaye                                                             //
//                                                                                            //
// Shiruku is free software: you can redistribute it and/or modify it under the terms         //
// of the GNU General Public License as published by the Free Software Foundation,            //
// either version 3 of the License, or (at your option) any later version.                    //
//                                                                                            //
// Shiruku is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;       //
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR           //
// PURPOSE.  See the GNU General Public License for more details.                             //
// You should have received a copy of the GNU General Public License along with Shiruku.      //
// If not, see <http://www.gnu.org/licenses/>.                                                //
//                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/shiru_main.h"
#include "../include/shiru_misc.h"
#include "../include/shiru_util.h"
#include "stdlib.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>

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
    shirusu - A simple fast thought note taker\n\n\
    shirusu [COMMAND] [OPTIONS]... \n\
    shirusu [-n <name> | --name <name>] [-m <message> | --message <message>]\n\
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

int shiru_create_home_directory(const char* xdg) {
    const char* format = "%s%c%s";
    size_t length = snprintf(NULL, 0, format, xdg, SEPARATOR, SHIRUSU_NAME);
    char* dirname = malloc(length + 1);
    if (dirname == NULL) {
        perror("allocated dirname");
        return EXIT_FAILURE;
    }
    sprintf(dirname, format, xdg, SEPARATOR, SHIRUSU_NAME);
    int status = mkdir((const char*) dirname, 0777);
    if (status != 0) {
        perror(errno == EEXIST ? "directory already exist" : "");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int shiru_main_exec(const struct shiru_main* opts) {
    if (opts->help) {
        shiru_main_help();
        return 0;
    }

    return EXIT_SUCCESS;
}