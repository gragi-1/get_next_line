# Get Next Line 🚀

## Introduction ✨

**Get Next Line** is a C library function that reads a line from a file descriptor, returning it as a dynamically allocated string. It is designed to handle input efficiently, safely, and flexibly, making it a valuable utility for C programmers.

---

## Academic Context 🎓

This project is part of the 42 School curriculum, where students are challenged to implement robust, reusable C functions. The main learning objectives include:
- Mastery of file I/O in C
- Dynamic memory management
- Use of static variables for persistent state
- Clean, modular code design

---

## Features 🛠️
- **Reads one line at a time** from any file descriptor (file, stdin, pipe, etc.)
- **Handles lines of any length** (not limited by buffer size)
- **Efficient memory usage**
- **Bonus: Supports multiple file descriptors simultaneously**
- **Customizable buffer size** via `BUFFER_SIZE`
- **No memory leaks** (valgrind-clean)

---

## How It Works ⚙️

`get_next_line` reads from a file descriptor until it finds a newline (`\n`) or reaches EOF. It uses a static buffer to store leftover data between calls, ensuring that lines are returned correctly even if they span multiple reads. The bonus version manages a separate buffer for each file descriptor, allowing concurrent reads.

---

## Installation & Compilation 🏗️

A `Makefile` is provided for easy compilation:

```bash
make all
```

To clean up object files:
```bash
make clean
```

---

## Usage 💡

### Standard Version

Include the header and compile the standard source files:

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

### Bonus Version (Multiple FDs) 🔄

To read from multiple file descriptors at once, use the bonus files:

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line1, *line2;

    while ((line1 = get_next_line(fd1)) || (line2 = get_next_line(fd2))) {
        if (line1) {
            printf("file1: %s", line1);
            free(line1);
        }
        if (line2) {
            printf("file2: %s", line2);
            free(line2);
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}
```

---

## API Reference 📑

### Header: `get_next_line.h` / `get_next_line_bonus.h`

```c
char *get_next_line(int fd);
```
- **fd**: File descriptor to read from
- **Returns**: Next line read from `fd` (including `\n` if present), or `NULL` on EOF or error. The returned string must be freed by the caller.

#### Internal Utility Functions
- `size_t ft_strlen(const char *s);`
- `char *ft_strchr(const char *s, int c);`
- `char *ft_strdup(const char *s1);`
- `char *ft_strjoin(const char *s1, const char *s2);`
- `void *ft_memcpy(void *dst, const void *src, size_t n);`

---

## Customization 🧩

Set the buffer size by defining the `BUFFER_SIZE` macro before compilation:

```c
#define BUFFER_SIZE 1024
#include "get_next_line.h"
```
Or add `-DBUFFER_SIZE=1024` to your compiler flags.

---

## Testing & Troubleshooting 🧪

- Test with files of various sizes, empty files, and files without a trailing newline.
- Check for memory leaks using [Valgrind](https://valgrind.org/):
  ```bash
  valgrind --leak-check=full ./your_program file.txt
  ```
- If you encounter issues, ensure `BUFFER_SIZE` is set to a reasonable value (e.g., 32, 42, 1024).

---

## FAQ ❓

**Q: Does `get_next_line` work with stdin or pipes?**
A: Yes! You can use it with any valid file descriptor, including stdin (fd = 0) and pipes.

**Q: What happens if the file does not end with a newline?**
A: The last line will still be returned, even if it does not end with `\n`.

**Q: Is the returned string always dynamically allocated?**
A: Yes. You must `free()` each line after use to avoid memory leaks.

**Q: How many file descriptors can the bonus version handle?**
A: Up to 1024 (by default, can be changed in the code).

---

## Integration Tips 🔗

- Add the source and header files to your project and include the appropriate header.
- Use the Makefile as a reference for your own build system.
- For best performance, tune `BUFFER_SIZE` to match your typical line length or I/O pattern.
- Always check for `NULL` returns to handle EOF and errors gracefully.

---

## License 📄

This project is released under the MIT License. See [LICENSE](LICENSE) for details.

---

## Acknowledgments 🙏
- Developed as part of the 42 School curriculum.
- Inspired by the need for robust file reading utilities in C.
- Thanks to the 42 community for support and feedback.

