/* VPI - A program to automate the installation of Vim plugins with native
 * plugin manager. Copyright (C) 2022 prxvvy <qsk55464@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//
// Created by prxvvy on 16/04/2022
//

#ifndef UTIL_H
#define UTIL_H

#define _XOPEN_SOURCE 500

#include <ftw.h>

int is_equal_to(char *p_input1, char *p_input2);

int unlink_callback(const char *fpath, const struct stat *sb, int typeflag,
                    struct FTW *ftwbuf);

int rmrf(char *path);

int starts_with(char *p_string, char *p_toFind);

int includes(char *p_string, char *p_toFind);

char *concatenate_git_cmd(char *p_githubURL, char *p_destDir, int b_special);

#endif  // UTIL_H
