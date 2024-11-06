#ifndef FETCH_H
#define FETCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>

// Color definitions
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// System information structure
typedef struct {
    char hostname[256];
    char username[256];
    char os_name[256];
    char kernel[256];
    char uptime[64];
    char shell[256];
    char cpu_info[256];
    char memory[64];
    char disk_space[64];
} SystemInfo;

// Function declarations
void get_system_info(SystemInfo *info);
char* get_command_output(const char* cmd);
void print_info_line(const char* label, const char* value);

#endif
