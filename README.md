# Get Next Line Project

## Description

Get Next Line (GNL) is a C function designed to read a line ending with a newline character ('\n') from a file descriptor. This project is part of the 42 School curriculum, aimed at teaching file handling and dynamic memory allocation in C, as well as introducing the concept of static variables.

## Objective

The main goal of this project is straightforward yet fundamental: to program a function that returns a line read from a file descriptor. It's not just a practical addition to any C function library but also serves to teach the essential concept of static variables in C, a cornerstone in memory management and program flow control.

## Compilation

The project includes a Makefile for easy compilation. You can compile the project using the following command:

```bash
make all
```

## Usage

To use the get_next_line function in your project, include the get_next_line.h header and make sure get_next_line.c and get_next_line_utils.c are compiled with your source files.

Example usage in a C program:

```C
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Contributions

This project is the result of individual effort as part of the 42 School curriculum. While the project is closed to direct contributions, any feedback is welcome.
