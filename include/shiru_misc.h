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

#ifndef __SHIRUSU_MISC_H__
#define __SHIRUSU_MISC_H__

#include <stdbool.h>

extern const char*const VERSION;
extern const char*const AUTHOR;
extern const char*const usage;
extern const char*const help;
extern const char*const SHIRUSU_NAME;
extern const char*const ENV_XDG_DATA_HOME;

int show_version(void);
bool is_shirusu_initialized(void);
const char* xdg_home_dir();
const char* shirusu_home(void);
const char* shiru_timestamp(void);
const char* shirusu_home_file(const char* file);

#endif
