# LibFile Library

**LibFile** is a C library that provides an easy-to-use interface for common file management operations such as creating, deleting, reading, writing, appending, editing, copying, and moving files.

## Features

- **File Creation**: Create new empty files.
- **File Deletion**: Delete existing files.
- **File Reading**: Read the entire content of a file.
- **File Writing**: Write or overwrite content to a file.
- **File Appending**: Append content to an existing file.
- **File Editing**: Replace specific content within a file.
- **Pattern Deletion**: Remove occurrences of a specific pattern from a file.
- **File Existence Check**: Verify if a file exists.
- **File Size Retrieval**: Get the size of a file in bytes.
- **File Copying**: Duplicate the content of one file to another.
- **File Moving**: Move a file to a new location (copy and delete).

## Installation

To integrate **LibFile** into your project, follow these steps:

1. Download the library header and implementation files:
   ```bash
   wget https://raw.githubusercontent.com/linuxfanboy4/libfile/refs/heads/main/libfile.h
   wget https://raw.githubusercontent.com/linuxfanboy4/libfile/refs/heads/main/libfile.c
   ```

2. Compile the library:
   ```bash
   gcc -c libfile.c -o libfile.o
   ```

3. Use the compiled library in your project. For example, if your program is `myprogram.c`:
   ```bash
   gcc myprogram.c libfile.o -o myprogram
   ```

## Function Reference

Below is a summary of the available functions and their purposes:

| Function                      | Description                                        |
|-------------------------------|----------------------------------------------------|
| `int create_file(const char *filename)` | Creates an empty file with the given name. Returns 0 on success, -1 on failure. |
| `int delete_file(const char *filename)` | Deletes the specified file. Returns 0 on success, -1 on failure. |
| `int read_file(const char *filename, char **content)` | Reads the content of the file and stores it in a dynamically allocated string. Returns 0 on success, -1 on failure. |
| `int write_to_file(const char *filename, const char *content)` | Overwrites the file with the specified content. Returns 0 on success, -1 on failure. |
| `int append_to_file(const char *filename, const char *content)` | Appends the specified content to the file. Returns 0 on success, -1 on failure. |
| `int edit_file(const char *filename, const char *old_content, const char *new_content)` | Replaces occurrences of old content with new content in the file. Returns 0 on success, -1 on failure. |
| `int delete_pattern_in_file(const char *filename, const char *pattern)` | Deletes occurrences of the specified pattern from the file. Returns 0 on success, -1 on failure. |
| `int file_exists(const char *filename)` | Checks if the specified file exists. Returns 1 if the file exists, 0 otherwise. |
| `long get_file_size(const char *filename)` | Retrieves the size of the specified file in bytes. Returns file size on success, -1 on failure. |
| `int copy_file(const char *src, const char *dst)` | Copies content from the source file to the destination file. Returns 0 on success, -1 on failure. |
| `int move_file(const char *src, const char *dst)` | Moves a file from the source to the destination path. Returns 0 on success, -1 on failure. |

## Example Usage

Here's an example of how you might use **LibFile** to create a file, write content to it, and read it back:

```c
#include <stdio.h>
#include "libfile.h"

int main() {
    const char *filename = "example.txt";
    const char *content = "Hello, World!";
    char *read_content = NULL;

    // Create a file
    if (create_file(filename) == 0) {
        printf("File created successfully.\n");
    } else {
        printf("Failed to create file.\n");
        return 1;
    }

    // Write to the file
    if (write_to_file(filename, content) == 0) {
        printf("Content written to file.\n");
    } else {
        printf("Failed to write to file.\n");
        return 1;
    }

    // Read from the file
    if (read_file(filename, &read_content) == 0) {
        printf("File content: %s\n", read_content);
        free(read_content); // Don't forget to free allocated memory
    } else {
        printf("Failed to read from file.\n");
        return 1;
    }

    return 0;
}
```

## Notes

- Memory management is crucial when working with functions like `read_file`. Ensure allocated memory is freed appropriately.
- Check the return values of all functions to handle errors gracefully.
- This library does not handle concurrency and should not be used in multithreaded environments without additional synchronization mechanisms.

## License

This library is open-source. Feel free to use, modify, and distribute it as per your project's needs. Make sure to provide attribution if required.
