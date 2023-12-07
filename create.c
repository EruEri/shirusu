#include "create.h"
#include <pwd.h>
#include <unistd.h>



int shirisu_create() {
    struct passwd *pw = getpwuid(getuid());
    const char* home_dir = pw->pw_dir;
    return -1;
}