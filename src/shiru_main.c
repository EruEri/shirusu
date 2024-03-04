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

#include "../include/shiru_main.h"
#include "../include/shiru_misc.h"
#include "../include/shiru_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>

struct shiru_main shiru_main_opts = {
    .message = NULL,
    .name = NULL,
    .exist_name = NULL,
    .help = false,
};

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"message", required_argument, 0, 'm'},
    {"name", required_argument, 0, 'n'},
    {0, 0, 0, 0}
};

static const char* shiru_main_usage = \
"shirusu [-n <name> | --name <name> | -x <name> ] [-m <message> | --message <message>]";


int shiru_main_parse(int argc, const char** argv) {
    int status = 0;
    while (true) {
        int option_index = 0;
        int res = getopt_long(
            argc, (char*const*) argv, "hm:x:n:", long_options, &option_index);
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
        case 'x':
            shiru_main_opts.exist_name = optarg;
            break;
        case '?':
            status = 1;
            break;
        }
    }
    return status;
}

int shiru_delege_editor(const char* path) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Cannot start editor");
        return EXIT_SUCCESS;
    }

    if (pid == 0) {
        const char* shirusu_editor = getenv(ENV_SHIRUSU_EDITOR);
        if (shirusu_editor) {
            execlp(shirusu_editor, shirusu_editor, path, (void*) 0);
            perror("$SHIRUSU_EDITOR");
        }
        const char* editor = getenv(ENV_EDITOR);
        if (editor) {
            execlp(editor, editor, path, (void*) 0);
            perror("$EDITOR");
        }

        for (size_t i = 0; i < SHIRUSU_EDITORS_COUNT; i+= 1) {
            const char* ed = SHIRUSU_EDITORS[i];
            execlp(ed, ed, path, (void*) 0);
        }
        fprintf(stderr, "No editor found\n");
        return EXIT_FAILURE;
    } else {
        // parent
        int status = 0;
        wait(&status);
        return status;
    }
}

int shiru_main_run(const struct shiru_main* opts) {
    const char* message = opts->message;
    const char* name = opts->name;
    bool is_filename_allocated = false;
    const char* full_path_file = NULL;
    const char* filename = name;
    int status = EXIT_SUCCESS;

    if (opts->name == NULL && opts->exist_name == NULL) {
        is_filename_allocated = true;
        filename = shiru_timestamp();
        if (filename == NULL) {
            return EXIT_FAILURE;
        }
    } else if (opts->name) {
        filename = opts->name;
    } else if (opts->exist_name) {
        filename = opts->exist_name;
    }

    full_path_file = shirusu_home_file(filename);
    if (!full_path_file) {
        status = EXIT_FAILURE;
        goto deinit;
    }

    if (opts->exist_name) {
        bool res = access(full_path_file, F_OK) == 0;
        if (!res) {
            fprintf(stderr, "note \"%s\" doesnt exist\n", opts->exist_name);
            status = EXIT_FAILURE;
            goto deinit;
        }
    }

    FILE* file = fopen(full_path_file, "a+");
    if (file == NULL) {
        perror("file error");
        status = EXIT_FAILURE;
        goto deinit;
    }

    if (message) {
        fprintf(file, "%s\n", message);
        fclose(file);
    } else {
        fclose(file);
        status = shiru_delege_editor(full_path_file);
    }

deinit:
    
    if (is_filename_allocated) {
        free((void *) filename);
    }
    free((void *) full_path_file);
    return status;
}


static bool shiru_main_validate(const struct shiru_main* opts) {
    if (opts->name && opts->exist_name) {
        fprintf(stderr, "Args conflict : --name can't be used with -x\n");
        fprintf(stderr, "usage : %s\n", shiru_main_usage);
        return false;
    }

    return true;
}



int shiru_main_exec(const struct shiru_main* opts) {
    if (opts->help) {
        shiru_main_help();
        return EXIT_SUCCESS;
    }

    if (!shiru_main_validate(opts)) {
        return EXIT_FAILURE;
    }

    if (!is_shirusu_initialized()) {
        fprintf(stderr, "%s not initialized. Please run:\n  %s init\n", SHIRUSU_NAME, SHIRUSU_NAME);
        return EXIT_FAILURE;
    }
    
    return shiru_main_run(opts);
}

int shiru_main_help(void) {
      printf("\
Usage:\n\
    shirusu - A simple fast thought note taker\n\n\
    shirusu [COMMAND] [OPTIONS]... \n\
    shirusu [-n <name> | --name <name> | -x <name> ] [-m <message> | --message <message>]\n\
Options:\n\
    -n, --name=NAME        Name of the new note\n\
    -x,       =NAME        Name of the existing note\n\
    -m, --message=MESSAGE  Content of the note\n\
    -h, --help             Show help\n\
        --version          Show version\n\
Commands:\n\
    init                   Initialiaze init\n\
    list                   List notes\n\
Environments:\n\
    SHIRUSU_EDITOR         Try to open note with if define\n\
    EDITOR                 Try to open note with if SHIRUSU_EDITOR isn't define\n\
"
);
    return 0;  
}
