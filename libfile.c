#include "libfile.h"

int create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }
    fclose(file);
    return 0;
}

int delete_file(const char *filename) {
    if (remove(filename) != 0) {
        return -1;
    }
    return 0;
}

int read_file(const char *filename, char **content) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    *content = (char *)malloc(size + 1);
    if (*content == NULL) {
        fclose(file);
        return -1;
    }
    fread(*content, 1, size, file);
    (*content)[size] = '\0';
    fclose(file);
    return 0;
}

int write_to_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }
    fwrite(content, sizeof(char), strlen(content), file);
    fclose(file);
    return 0;
}

int append_to_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        return -1;
    }
    fwrite(content, sizeof(char), strlen(content), file);
    fclose(file);
    return 0;
}

int edit_file(const char *filename, const char *old_content, const char *new_content) {
    char *file_content;
    if (read_file(filename, &file_content) != 0) {
        return -1;
    }
    char *pos = strstr(file_content, old_content);
    if (pos != NULL) {
        size_t new_content_len = strlen(new_content);
        size_t old_content_len = strlen(old_content);
        size_t content_len = strlen(file_content);
        char *new_file_content = (char *)malloc(content_len - old_content_len + new_content_len + 1);
        if (new_file_content == NULL) {
            free(file_content);
            return -1;
        }
        strncpy(new_file_content, file_content, pos - file_content);
        strcpy(new_file_content + (pos - file_content), new_content);
        strcpy(new_file_content + (pos - file_content) + new_content_len, pos + old_content_len);
        write_to_file(filename, new_file_content);
        free(file_content);
        free(new_file_content);
        return 0;
    }
    free(file_content);
    return -1;
}

int delete_pattern_in_file(const char *filename, const char *pattern) {
    char *file_content;
    if (read_file(filename, &file_content) != 0) {
        return -1;
    }
    char *pos = strstr(file_content, pattern);
    while (pos != NULL) {
        size_t pattern_len = strlen(pattern);
        size_t content_len = strlen(file_content);
        char *new_file_content = (char *)malloc(content_len - pattern_len + 1);
        if (new_file_content == NULL) {
            free(file_content);
            return -1;
        }
        strncpy(new_file_content, file_content, pos - file_content);
        strcpy(new_file_content + (pos - file_content), pos + pattern_len);
        write_to_file(filename, new_file_content);
        free(file_content);
        file_content = new_file_content;
        pos = strstr(file_content, pattern);
    }
    free(file_content);
    return 0;
}

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    fclose(file);
    return 1;
}

long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int copy_file(const char *src, const char *dst) {
    FILE *src_file = fopen(src, "r");
    if (src_file == NULL) {
        return -1;
    }
    FILE *dst_file = fopen(dst, "w");
    if (dst_file == NULL) {
        fclose(src_file);
        return -1;
    }
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes, dst_file);
    }
    fclose(src_file);
    fclose(dst_file);
    return 0;
}

int move_file(const char *src, const char *dst) {
    if (copy_file(src, dst) == 0) {
        return delete_file(src);
    }
    return -1;
}
