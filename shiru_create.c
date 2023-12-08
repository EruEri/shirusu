#include "shiru_create.h"
#include <pwd.h>
#include <unistd.h>


struct shiru_create shiru_create_opts = {};

int shiru_create_parse(int argc, const char** argv) {
    return 0;
}


int shirisu_create() {
    struct passwd *pw = getpwuid(getuid());
    const char* home_dir = pw->pw_dir;
    return -1;
}