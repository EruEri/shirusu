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

#ifndef __SHIRUSU_MAIN_H__
#define __SHIRUSU_MAIN_H__

#include <stdbool.h>

struct shiru_main {
    const char* name;
    const char* message;
    bool help;
};

extern struct shiru_main shiru_main_opts;

int shiru_main_parse(int argc, const char**);
int shiru_main_help(void);
int shiru_main_exec(const struct shiru_main*);

#endif