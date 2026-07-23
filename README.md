*This project has been created as part of the 42 curriculum by ahideo-k.*

# get_next_line

## Description

The objective of this project is to implement the `get_next_line()` function, capable of reading a file descriptor one line at a time.

Unlike a regular call to `read()`, which simply returns a sequence of bytes, `get_next_line()` preserves unread data between function calls by using a static variable. This allows the function to return exactly one complete line on each invocation while continuing from where the previous call stopped.

The project introduces one of the most important concepts in C programming: **static variables**, while reinforcing dynamic memory management, string manipulation, file descriptor handling, and efficient buffer-based reading.

---

## Project Structure

```text
.
├── Makefile
├── get_next_line.h
├── get_next_line.c
├── get_next_line_utils.c
└── README.md
```

Each source file has a single responsibility, making the project modular and easier to maintain.

---

## Features

- Reads one line per function call
- Supports any valid file descriptor
- Reads from files or standard input
- Preserves unread data between calls
- Handles arbitrary `BUFFER_SIZE` values
- Dynamically allocates only the required memory
- Returns lines including the terminating `\n` when present
- Compliant with the 42 Norm

---

# Algorithm and Technical Choices

The core challenge of this project is that a single call to `read()` rarely returns exactly one line.

Instead, the function must remember any data that belongs to the next line. This is achieved through a **static variable**, which retains its value between function calls.

The algorithm follows these steps:

1. Validate the file descriptor and `BUFFER_SIZE`.
2. Read data from the file descriptor in chunks of `BUFFER_SIZE` bytes.
3. Append each newly read chunk to the existing stored data.
4. Stop reading as soon as a newline character (`\n`) is found or the end of the file is reached.
5. Extract the next complete line from the stored data.
6. Save any remaining characters after the extracted line for the next function call.
7. Return the extracted line.

Visually, the process works like this:

```text
File

Hello World\n
How are you?\n
42 School

            ↓ read()

Static buffer

Hello World\nHow are

            ↓

Returned line

Hello World\n

            ↓

Remaining static data

How are

            ↓ next call

How are you?\n
```

The use of a static variable avoids rereading previously processed data while ensuring that every byte is read only once.

This approach satisfies the project requirements while minimizing unnecessary system calls and memory allocations.

---

# Instructions

## Clone the repository

```bash
git clone https://github.com/Andre-Kikuchi/get_next_line.git
cd get_next_line
```

## Compile

Compile with the desired buffer size.

Example:

```bash
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
	get_next_line.c get_next_line_utils.c main.c
```

The project must also compile without explicitly defining `BUFFER_SIZE`, using its default value.

---

## Example

```c
#include "get_next_line.h"
#include <fcntl.h>  // open() e O_RDONLY
#include <stdio.h>  // printf
#include <stdlib.h> // free()
#include <unistd.h> // close()

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     i;

    // If a file is passed as an argument, open the file.
	// If nothing is passed, use 0 (stdin / Standard Input).
    if (argc > 1)
        fd = open(argv[1], O_RDONLY);
    else
        fd = 0;

    if (fd == -1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            printf("NULL\n");
        return (0);
    }

    i = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("[%d] \"%s\"\n", i, line);
        free(line);
        i++;
    }

    printf("[%d] NULL\n", i);

    if (fd > 2)
        close(fd);
    return (0);
}

./a.out test.txt
or
echo -en "Line 1\nLine 2" | ./a.out
```

---

# Technical Choices

This project follows the requirements established by the 42 subject.

- Written entirely in C
- Compiled with `cc`
- Compiler flags:
  - `-Wall`
  - `-Wextra`
  - `-Werror`
- Uses only the authorized functions:
  - `read`
  - `malloc`
  - `free`
- No global variables
- No use of `libft`
- Uses a static variable to preserve reading state
- Compatible with different `BUFFER_SIZE` values
- Code compliant with the 42 Norm

---

# Learning Outcomes

Through this project I practiced:

- Static variables
- File descriptors
- Low-level file reading
- Dynamic memory management
- Buffer manipulation
- String processing
- Memory leak prevention
- Modular software design

---

# Resources

## Documentation

- The Linux Manual Pages — `read(2)`
- The Linux Manual Pages — `open(2)`
- The Linux Manual Pages — `close(2)`
- cppreference — Dynamic memory allocation
- Beej's Guide to C Programming

Useful websites:

- https://man7.org/linux/man-pages/man2/read.2.html
- https://man7.org/linux/man-pages/man2/open.2.html
- https://man7.org/linux/man-pages/man2/close.2.html
- https://42-cursus.gitbook.io/guide/useful-tools/file-descriptors-fd
- https://beej.us/guide/bgc/

---

## AI Usage

Artificial Intelligence was used only as a learning support tool.

Specifically, it was used to:

- clarify the behavior of static variables;
- review edge cases involving file descriptors;
- understand memory management strategies;
- improve the project documentation.

All code was designed, implemented, tested, debugged, and fully understood before submission.

---

# License

This project was developed as part of the 42 curriculum and is intended for educational purposes.