# Get Next Line

## Overview

**Get Next Line** is a robust C library function that reads a line from a file descriptor, handling input efficiently and safely. Developed as part of the 42 School curriculum, this project demonstrates advanced file handling, dynamic memory management, and the use of static variables in C. It is designed to be both a practical utility and an educational exercise in low-level programming.

---

## Features

- **Reads one line at a time** from any file descriptor (including files, stdin, pipes, etc.)
- **Handles lines of arbitrary length** (not limited by buffer size)
- **Efficient memory management**: dynamically allocates only what is needed
- **Bonus: Supports multiple file descriptors simultaneously** (see Bonus section)
- **Customizable buffer size** via `BUFFER_SIZE` macro
- **No memory leaks** (valgrind-clean)

---

## How It Works

`get_next_line` reads from a file descriptor until it encounters a newline (`\n`) or EOF, returning the line (including the newline, if present). It uses a static variable to store leftover data between calls, ensuring that lines are returned correctly even if they span multiple reads.

---

## Installation & Compilation

A `Makefile` is provided for easy compilation. To build the library and test program:

```bash
make all
```

This will compile the necessary source files. You can clean up object files with:

```bash
make clean
```

---

## Usage

To use `get_next_line` in your project:

1. Include the header:
    ```c
    #include "get_next_line.h"
    ```
2. Compile `get_next_line.c` and `get_next_line_utils.c` with your sources.

### Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int fd;
    char *line;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

## API Documentation

### Header: `get_next_line.h`

```c
char *get_next_line(int fd);
```
- **fd**: File descriptor to read from
- **Returns**: Next line read from `fd` (including `\n` if present), or `NULL` on EOF or error. The returned string must be freed by the caller.

#### Utility Functions (internal use):
- `size_t ft_strlen(const char *s);`
- `char *ft_strchr(const char *s, int c);`
- `char *ft_strdup(const char *s1);`
- `char *ft_strjoin(const char *s1, const char *s2);`
- `void *ft_memcpy(void *dst, const void *src, size_t n);`

---

## Customization

You can set the buffer size used for reading by defining the `BUFFER_SIZE` macro before compilation. For example:

```c
#define BUFFER_SIZE 1024
#include "get_next_line.h"
```
Or by adding `-DBUFFER_SIZE=1024` to your compiler flags.

---

## Bonus Part: Multiple File Descriptors

The bonus version (`get_next_line_bonus.c` and `get_next_line_bonus.h`) supports reading from multiple file descriptors simultaneously. This is achieved by maintaining a separate static buffer for each descriptor.

- To use the bonus version, include `get_next_line_bonus.h` and compile the bonus source files.
- The API remains the same: `char *get_next_line(int fd);`

---

## Testing & Troubleshooting

- Test with files of various sizes, empty files, and files without a trailing newline.
- Check for memory leaks using [Valgrind](https://valgrind.org/):
  ```bash
  valgrind --leak-check=full ./your_program file.txt
  ```
- If you encounter issues, ensure `BUFFER_SIZE` is set to a reasonable value (e.g., 32, 42, 1024).

---

## License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.

---

## Acknowledgments

- Developed as part of the 42 School curriculum.
- Inspired by the need for robust file reading utilities in C.
- Special thanks to the 42 community for support and feedback.
