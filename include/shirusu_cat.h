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

#ifndef __SHIRUSU_CAT_H_
#define __SHIRUSU_CAT_H_

#include <stdbool.h>

struct shirusu_cat {
    const char** notes;
    bool help;
};

extern struct shirusu_cat shirusu_cat_opts;
int shirusu_cat_exec(const struct shirusu_cat* opts);
int shirusu_cat_parse(int, const char**);
int shirusu_cat_help(void);

#endif