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

#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/shirusu_list.h"
#include "../include/shirusu_misc.h"

struct shiru_list shiru_list_opts = {
    .help = false
};

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}  
};


static bool ignored_file(const char* file) {
    for (size_t i = 0; i < SHIRUSU_IGNORE_FILES_COUNT; i += 1) {
        const char* current_ignore = SHIRUSU_IGNORE_FILES[i];
        if (strcmp(file, current_ignore) == 0) {
            return true;
        }
    }
    return false;
}

int shiru_list_parse(int argc, const char ** argv) {
    int status = 0;
    while (true) {
        int option_index = 0;
        int res = getopt_long(
            argc, (char*const*) argv, "h", long_options, &option_index);
        if (res == -1) break;
        switch (res) {
        case 'h':
            shiru_list_opts.help = true;
            break;
        case '?':
            status = 1;
            break;
        }
    }
    return status;
}

int shiru_list_run(const struct shiru_list* opts) {
    int status = EXIT_SUCCESS;
    bool is_initialized = is_shirusu_initialized();
    DIR* directory = NULL;
    if (!is_initialized) {
        fprintf(stderr, "%s not initialized. Please run:\n  %s init\n", SHIRUSU_NAME, SHIRUSU_NAME);
        return EXIT_FAILURE;
    }
    const char* shiru_home = shirusu_home();
    if (shiru_home == NULL) {
        perror(NULL);
        return EXIT_FAILURE;
    }
    
    directory = opendir(shiru_home);
    if (directory == NULL) {
        perror(shiru_home);
        status = EXIT_FAILURE;
        goto end;
    }
    struct dirent* file = NULL;
    do {
        file = readdir(directory);
        if (file && !ignored_file(file->d_name)) {
            printf("%s\n", file->d_name);
        }
    } while (file != NULL);
    
    closedir(directory);
end:
    free((void*) shiru_home);
    return status;
}

int shiru_list_exec(const struct shiru_list* opts) {
    if (opts->help) {
        shiru_list_help();
        return EXIT_SUCCESS;
    }
    return shiru_list_run(opts);
}


int shiru_list_help(void) {
    printf("Usage:\n");
    printf("    shirusu list - List taken notes\n\n");
    printf("    shirusu list [OPTIONS]...\n");
    printf("Description:\n");
    printf("    List existing notes in shirusu directory\n");
    printf("Options:\n");
    printf("    -h, --help             Show help\n");
    printf("        --version          Show version\n");
    return 0;
}
