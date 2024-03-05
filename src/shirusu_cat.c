////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
// This file is part of shirusu : A little note taker                                         //
// Copyright (C) 2023 Yves Ndiaye                                                             //
//                                                                                            //
// shirusu is free software: you can redistribute it and/or modify it under the terms         //
// of the GNU General Public License as published by the Free Software Foundation,            //
// either version 3 of the License, or (at your option) any later version.                    //
//                                                                                            //
// shirusu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;       //
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR           //
// PURPOSE.  See the GNU General Public License for more details.                             //
// You should have received a copy of the GNU General Public License along with shirusu.      //
// If not, see <http://www.gnu.org/licenses/>.                                                //
//                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////

#include "../include/shirusu_cat.h"
#include "../include/shirusu_misc.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHIRUSU_CAT_BUFFER_SIZE 2048

struct shirusu_cat shirusu_cat_opts = {
    .help = false
};

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

int shirusu_cat_file(FILE* file) {
    unsigned long bytes_read = 0;
    char buffer[SHIRUSU_CAT_BUFFER_SIZE];
        do {
            bytes_read = fread(buffer, sizeof(char), SHIRUSU_CAT_BUFFER_SIZE, file);
        fwrite(buffer, sizeof(char), bytes_read, stdout);
    } while (bytes_read == SHIRUSU_CAT_BUFFER_SIZE);
    return 0;
}

int shirusu_cat_notename(const char* note) {
    const char* notepath = shirusu_home_file(note);
    FILE* notefile = fopen(notepath, "r+");
    if (notefile == NULL) {
        goto deinit;
    }
    shirusu_cat_file(notefile);
    fclose(notefile);
deinit:
    free( (void *) notepath);
    return 0;
}

int shirusu_cat_parse(int argc, const char** argv) {
    int status = 0;
    while (true) {
        int option_index;
        int res = getopt_long(
            argc, (char *const*) argv, "h", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
            case 'h':
                shirusu_cat_opts.help = true;
                break;
            case '?':
                status = 1;
                break;

        }
    }
    shirusu_cat_opts.notes = argv + optind;
    return status;
}

int shirusu_cat_run(const struct shirusu_cat* opts) {
    const char** root = opts->notes;
    const char* note = root[0];
    while (note != NULL) {
        shirusu_cat_notename(note);
        note = *(++root);
    }
    return 0;
}

int shirusu_cat_exec(const struct shirusu_cat* opts) {
    if (opts->help) {
        shirusu_cat_help();
        return EXIT_SUCCESS;
    }
    return shirusu_cat_run(opts);
}

int shirusu_cat_help(void) {
    printf("\
Usage:\n\
    shirusu cat - print notes\n\n\
    shirusu cat [OPTIONS]... \n\
Description:\n\
    Print notes to the standard output\n\
Options:\n\
    -h, --help             Show help\n\
"
);
    return 0;
}