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

#ifndef __SHIRUSU_CREATE_H__
#define __SHIRUSU_CREATE_H__

 
#include <stdbool.h>

struct shiru_create {
    bool help;
};

extern struct shiru_create shiru_create_opts;

int shiru_create_parse(int argc, const char** argv);
int shiru_create_help(void);
int shiru_create_exec(const struct shiru_create*);

#endif
