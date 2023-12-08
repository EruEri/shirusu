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
#include "../include/shiru_misc.h"

const char*const VERSION = "0.1.0";
const char*const AUTHOR = "Yves Ndiaye";
const char*const SHIRUSU_NAME = "shirusu";
const char*const usage = "usage: shirusu [COMMAND] ...";

int show_version() {
    fprintf(stdout, "%s\n", VERSION);
    exit(0);
}