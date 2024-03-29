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

#include "../include/shirusu_create.h"
#include "../include/shirusu_util.h"
#include "../include/shirusu_misc.h"
#include <sys/stat.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <pwd.h>

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

struct shiru_create shiru_create_opts = {
    .help = false
};

int shiru_create_home_directory(const char* xdg) {
    const char* format = "%c%s%c%s";
    size_t length = snprintf(NULL, 0, format, FILE_SEPARATOR, xdg, FILE_SEPARATOR, SHIRUSU_NAME);
    char* dirname = malloc(length + 1);
    if (dirname == NULL) {
        perror("allocated dirname");
        return EXIT_FAILURE;
    }
    sprintf(dirname, format, FILE_SEPARATOR, xdg, FILE_SEPARATOR, SHIRUSU_NAME);
    int status = mkdir((const char*) dirname, 0777);
    free((void *) dirname);
    if (status != 0) {
        perror(errno == EEXIST ? "directory already exist" : "");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


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
        return EXIT_SUCCESS;
    }

    const char* root = xdg_home_dir();
    if (!root) { return EXIT_FAILURE; }
    
    int status = shiru_create_home_directory(root);
    free((void *) root);
    return status;
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
