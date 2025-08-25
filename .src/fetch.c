#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <pwd.h>
#include <time.h>

// ANSI color codes
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Function to get OS info
void get_os_info(char* os_name, char* kernel) {
    struct utsname sys_info;
    uname(&sys_info);
    
    // Try to get OS name from /etc/os-release
    FILE* file = fopen("/etc/os-release", "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
                strcpy(os_name, line + 13);
                // Remove quotes and newline
                os_name[strcspn(os_name, "\"\n")] = 0;
                break;
            }
        }
        fclose(file);
    } else {
        strcpy(os_name, "Linux");
    }
    
    sprintf(kernel, "%s %s", sys_info.sysname, sys_info.release);
}

// Function to get memory info
void get_memory_info(char* memory) {
    struct sysinfo sys_info;
    sysinfo(&sys_info);
    
    long total_ram = sys_info.totalram / 1024 / 1024; // Convert to MB
    long free_ram = sys_info.freeram / 1024 / 1024;
    long used_ram = total_ram - free_ram;
    
    sprintf(memory, "%ld MB / %ld MB (%.1f%%)", used_ram, total_ram, 
            (float)used_ram / total_ram * 100);
}

// Function to get storage info
void get_storage_info(char* storage) {
    struct statvfs stat;
    
    if (statvfs("/", &stat) != 0) {
        strcpy(storage, "Unknown");
        return;
    }
    
    unsigned long total = (stat.f_blocks * stat.f_frsize) / (1024 * 1024 * 1024); // GB
    unsigned long available = (stat.f_bavail * stat.f_frsize) / (1024 * 1024 * 1024); // GB
    unsigned long used = total - available;
    
    sprintf(storage, "%lu GB / %lu GB (%.1f%%)", used, total, 
            (float)used / total * 100);
}

// Function to get uptime
void get_uptime(char* uptime) {
    struct sysinfo sys_info;
    sysinfo(&sys_info);
    
    long uptime_seconds = sys_info.uptime;
    long days = uptime_seconds / 86400;
    long hours = (uptime_seconds % 86400) / 3600;
    long minutes = (uptime_seconds % 3600) / 60;
    
    if (days > 0) {
        sprintf(uptime, "%ld days, %ld hours, %ld mins", days, hours, minutes);
    } else if (hours > 0) {
        sprintf(uptime, "%ld hours, %ld mins", hours, minutes);
    } else {
        sprintf(uptime, "%ld mins", minutes);
    }
}

// Function to get CPU info
void get_cpu_info(char* cpu) {
    FILE* file = fopen("/proc/cpuinfo", "r");
    if (!file) {
        strcpy(cpu, "Unknown");
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "model name", 10) == 0) {
            char* colon = strchr(line, ':');
            if (colon) {
                strcpy(cpu, colon + 2);
                cpu[strcspn(cpu, "\n")] = 0;
                // Trim leading/trailing whitespace
                char* start = cpu;
                while (*start == ' ') start++;
                memmove(cpu, start, strlen(start) + 1);
                break;
            }
        }
    }
    fclose(file);
}

// Function to get shell info
void get_shell_info(char* shell) {
    char* shell_env = getenv("SHELL");
    if (shell_env) {
        char* shell_name = strrchr(shell_env, '/');
        if (shell_name) {
            strcpy(shell, shell_name + 1);
        } else {
            strcpy(shell, shell_env);
        }
    } else {
        strcpy(shell, "Unknown");
    }
}

// Function to get desktop environment
void get_desktop_info(char* desktop) {
    char* de = getenv("XDG_CURRENT_DESKTOP");
    if (de) {
        strcpy(desktop, de);
    } else {
        de = getenv("DESKTOP_SESSION");
        if (de) {
            strcpy(desktop, de);
        } else {
            strcpy(desktop, "Unknown");
        }
    }
}

// Function to print info line
void print_info(const char* color, const char* label, const char* value) {
    printf("%s%s%-12s%s %s\n", color, BOLD, label, RESET, value);
}

int main() {
    // Get user info
    struct passwd* pw = getpwuid(getuid());
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    
    // Get system info
    char os_name[256] = {0};
    char kernel[256] = {0};
    char memory[256] = {0};
    char storage[256] = {0};
    char uptime[256] = {0};
    char cpu[256] = {0};
    char shell[256] = {0};
    char desktop[256] = {0};
    
    get_os_info(os_name, kernel);
    get_memory_info(memory);
    get_storage_info(storage);
    get_uptime(uptime);
    get_cpu_info(cpu);
    get_shell_info(shell);
    get_desktop_info(desktop);
    
    printf("\n");
    
    // Print header
    printf("%s%s%s@%s%s\n", CYAN, BOLD, pw->pw_name, hostname, RESET);
    
    // Print separator
    int header_len = strlen(pw->pw_name) + strlen(hostname) + 1;
    for (int i = 0; i < header_len; i++) {
        printf("%s-%s", CYAN, RESET);
    }
    printf("\n");
    
    // Print system info
    print_info(RED, "OS:", os_name);
    print_info(GREEN, "Kernel:", kernel);
    print_info(YELLOW, "Uptime:", uptime);
    print_info(BLUE, "Shell:", shell);
    print_info(MAGENTA, "Desktop:", desktop);
    print_info(CYAN, "CPU:", cpu);
    print_info(WHITE, "Memory:", memory);
    print_info(GREEN, "Storage:", storage);
    
    // Print color palette
    printf("%sColors:%s      ", WHITE, RESET);
    printf("%s●%s ", RED, RESET);
    printf("%s●%s ", GREEN, RESET);
    printf("%s●%s ", YELLOW, RESET);
    printf("%s●%s ", BLUE, RESET);
    printf("%s●%s ", MAGENTA, RESET);
    printf("%s●%s ", CYAN, RESET);
    printf("%s●%s", WHITE, RESET);
    printf("\n\n");
    
    return 0;
}
