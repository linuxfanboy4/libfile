#ifndef LIBFILE_H
#define LIBFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_file(const char *filename);
int delete_file(const char *filename);
int read_file(const char *filename, char **content);
int write_to_file(const char *filename, const char *content);
int append_to_file(const char *filename, const char *content);
int edit_file(const char *filename, const char *old_content, const char *new_content);
int delete_pattern_in_file(const char *filename, const char *pattern);
int file_exists(const char *filename);
long get_file_size(const char *filename);
int copy_file(const char *src, const char *dst);
int move_file(const char *src, const char *dst);

#endif
