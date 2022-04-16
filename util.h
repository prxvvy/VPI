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
