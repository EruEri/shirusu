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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include "../include/shirusu_misc.h"
#include "../include/shirusu_util.h"

static const int year_start = 1900;
const char*const SHIRUSU_NAME = "shirusu";
const char*const VERSION = "0.1.0";
const char*const AUTHOR = "Yves Ndiaye";
const char*const usage = "usage: shirusu [COMMAND] ...";

// sorted in alphabetic order and NOTHING MORE!!!
const char* SHIRUSU_EDITORS[] = {
    "ee",
    "emacs",
    "nano",
    "vi",
    "vim"
};

const size_t SHIRUSU_EDITORS_COUNT = sizeof(SHIRUSU_EDITORS) / sizeof(const char*);

const char* SHIRUSU_IGNORE_FILES[] = {
    ".",
    "..",
    ".DS_Store"
};

const size_t SHIRUSU_IGNORE_FILES_COUNT = sizeof(SHIRUSU_IGNORE_FILES) / sizeof(const char*);

int show_version() {
    fprintf(stdout, "%s\n", VERSION);
    exit(0);
}

const char* xdg_home_dir() {
    const char* env = getenv(ENV_XDG_DATA_HOME);

    if (env != NULL) {
        const char* root = NULL;
        size_t length = strlen(env) + 1;
        root = malloc(length);
        if (root == NULL) {
            perror("XDG_DATA_HOME allocation");
            return NULL;
        }
        memcpy((void *) root, env, length);
        return root;
    } else {
        struct passwd *pw = getpwuid(getuid());
        const char* home_dir = pw->pw_dir;
        const char* format = "%s%c.local%cshare%c";
        size_t length = snprintf(NULL, 0, format, 
            home_dir, FILE_SEPARATOR, FILE_SEPARATOR, FILE_SEPARATOR
        ) + 1;
        char* root = malloc(length);
        if (root == NULL) { return NULL; }
        snprintf(root, length, format, 
            home_dir, FILE_SEPARATOR, FILE_SEPARATOR, FILE_SEPARATOR
        );
        return root;
    }
}

const char* shirusu_home(void) {
    const char* xdg_home = xdg_home_dir();
    const char* shirusu_h = NULL;
    if (xdg_home == NULL) { 
        perror(NULL);
        goto dealloc;
    }
    const char* format = "%s%c%s%c";
    size_t length = snprintf(NULL, 0, format, xdg_home, FILE_SEPARATOR, SHIRUSU_NAME, FILE_SEPARATOR) + 1;
    shirusu_h = malloc(length);
    if (shirusu_h == NULL) {
        perror(NULL);
        goto dealloc;
    }

    snprintf((char*) shirusu_h, length, format, xdg_home, FILE_SEPARATOR, SHIRUSU_NAME, FILE_SEPARATOR);
    
dealloc:
    free((void*) xdg_home);
    return shirusu_h;
}

const char* shirusu_home_file(const char* file) {
    const char* shiru_home = shirusu_home();
    char* shiru_file = NULL;
    if (shiru_home == NULL) { 
        perror(NULL);
        goto dealloc;
    }
    const char* format = "%s%s";
    size_t length = snprintf(NULL, 0, format, shiru_home, file) + 1;
    shiru_file = malloc(length);
    if (shiru_file == NULL) {
        perror(NULL);
        goto dealloc;
    }
    snprintf(shiru_file, length, format, shiru_home, file);
    
dealloc:
    free((void*) shiru_home);
    return shiru_file;
}


bool is_shirusu_initialized(void) {
    const char* shirusu = shirusu_home();
    if (shirusu == NULL) return false;
    bool res = access(shirusu, F_OK) == 0;
    free((void*) shirusu);
    return res;
}


const char* shiru_timestamp(void) {
    time_t t = time(NULL);
    struct tm* tm = localtime( &t );
    const char* format = "%s.%u-%02u-%02u.%02u-%02u-%02u";
    size_t length = snprintf(
        NULL, 0, format, SHIRUSU_NAME,
        tm->tm_year + year_start,
        tm->tm_mon + 1,
        tm->tm_mday,
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec
    ) + 1;
    char* timestamp = malloc(length);
    if (timestamp == NULL) {
        perror("Timestamp allocation");
        return NULL;
    }
    snprintf(
        timestamp, length, format, SHIRUSU_NAME,
        tm->tm_year + year_start,
        tm->tm_mon + 1,
        tm->tm_mday,
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec
    );
    return timestamp;
}
