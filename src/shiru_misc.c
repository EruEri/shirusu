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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include "../include/shiru_misc.h"
#include "../include/shiru_util.h"


const char*const ENV_XDG_DATA_HOME = "XDG_DATA_HOME";
const char*const SHIRUSU_NAME = "shirusu";
const char*const VERSION = "0.1.0";
const char*const AUTHOR = "Yves Ndiaye";
const char*const usage = "usage: shirusu [COMMAND] ...";

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
            perror("XDG_DATA_HOME copy");
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
            home_dir, FILE_SEPARATOR, FILE_SEPARATOR
        );
        return root;
    }
}

const char* shirusu_home(void) {
  return NULL;
}
