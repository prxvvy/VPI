//
// Created by prxvvy on 08/03/2022
//

#define _XOPEN_SOURCE 500
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_equal_to(char *p_input1, char *p_input2) {
  /* If the len of both strings are not equal, well they are not the same */

  if (strlen(p_input1) != strlen(p_input2)) return 0;

  unsigned int index = 0;

  while (p_input1[index] != '\0' && p_input2[index] != '\0') {
    if ((p_input1[index] != p_input2[index])) return 0;
    index++;
  }
  return 1;
}

int unlink_callback(const char *fpath, const struct stat *sb, int typeflag,
                    struct FTW *ftwbuf) {
  int rv = remove(fpath);

  if (rv) perror(fpath);

  return rv;
}

int rmrf(char *path) {
  return nftw(path, unlink_callback, 64, FTW_DEPTH | FTW_PHYS);
}

int starts_with(char *p_string, char *p_toFind) {
  for (unsigned int i = 0; i < strlen(p_string); ++i) {
    if (i == 0) {
      if (is_equal_to((char[2]){p_string[i], '\0'}, p_toFind) == 0)
        return 0;
      else
        return 1;
    }
  }
  return 0;
}

int includes(char *p_string, char *p_toFind) {
  size_t sLen = strlen(p_string);
  size_t toFindLen = strlen(p_toFind);

  unsigned int timesFound = 0;

  if (sLen > toFindLen) {
    for (unsigned int i = 0, j = 0; i < sLen; ++i) {
      do {
        if (p_string[i] == p_toFind[j]) {          /* If stars with same char */
          if (++timesFound == toFindLen) return 1; /* If got same len */
          i++;
          j++;
        } else {
          i -= timesFound;
          timesFound = 0;
          j = 0;
        }
      } while (timesFound);
    }
    return 0;
  } else {
    printf("\"%s\" is longer than \"%s\"\n", p_toFind, p_string);
    return 0;
  }
}

