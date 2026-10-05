# MiniGuard

MiniGuard is a Linux file-system monitoring agent written in C.

The project is intended to practice Linux system programming, network programming, and defensive C programming.

## Current Features

- Command-line argument parsing
- Configuration validation
- Watch path configuration
- Server IP configuration
- TCP port validation
- Makefile-based build

## Build

```bash
make
```

To remove build artifacts:

```bash
make clean
```

## Usage

```bash
./miniguard -d /tmp/watch -h 127.0.0.1 -p 9000
```

Example output:

```text
MiniGuard configuration
watch_path : /tmp/watch
server     : 127.0.0.1
port       : 9000
```

## Project Structure

```text
miniguard/
├── include/
│   └── config.h
├── src/
│   ├── main.c
│   └── config.c
├── .gitignore
├── Makefile
└── README.md
```

## Roadmap

- File-system monitoring with inotify
- File creation, modification, deletion, and move event detection
- TCP event transmission
- Graceful shutdown with signal handling
- I/O multiplexing with poll or epoll
- Multithreaded event processing
- Thread-safe event queue
- Server reconnection handling
- Error handling and debugging with gdb, strace, and AddressSanitizer

## Development Goals

The main goals of this project are to gain practical experience with:

- C programming
- Linux system calls
- File descriptors
- File-system event monitoring
- TCP socket programming
- Process and thread concepts
- I/O multiplexing
- Error handling
- Debugging Linux applications
