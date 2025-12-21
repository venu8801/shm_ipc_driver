This is a kernel module for shared memory creation between user-space and kernel space
this driver creates a memory which can be mapped to the process's address space and allows IPC between two processes.


Directory structure:

├── LICENSE
├── README.md
├── shm_driver
│   ├── inc
│   │   ├── shm_common.h
│   │   ├── shm_error.h
│   │   └── shm_utils.h
│   ├── Makefile
│   └── src
│       └── shm_module.c
└── shm_lib


shm_driver: directory contains the kernel driver which handles the shared memory related controls and IPC.

shm_lib: Userspace library to use driver features.