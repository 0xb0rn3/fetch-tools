#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
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

// ASCII art lines
const char* ascii_lines[] = {
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣴⣶⣶⣶⣶⣦⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣾⣿⣿⣿⣿⣟⠁⠀⢹⣿⣿⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⢠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢫⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀",
    "⠀⠀⠀⢠⣿⣿⣿⣿⣿⣏⠹⣿⣿⣿⣿⣿⣿⡃⠀⢩⣿⣿⣶⣬⣿⠟⠙⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀",
    "⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⠀⠻⠛⠛⠿⠛⠛⠁⠀⠘⠛⠿⠛⠛⠿⠇⢰⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀",
    "⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣶⣶⡄⠀⠀⠀⣠⣤⣦⣄⡀⠀⠀⠀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀",
    "⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⢠⣿⣿⣿⣿⣿⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀",
    "⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠘⠿⣿⣿⣿⠟⠀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀",
    "⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀",
    "⠘⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠉⠻⣿⣿⣿⣿⡿⠋⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁",
    "⠀⠀⠀⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⣿⣿⣿⣿⡗⠂⢸⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠁⠀⠀⠀",
    "⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⢸⣿⣿⣿⠁⡁⢸⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⢸⣿⣿⣿⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⠀⠀⢸⣿⣿⣿⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⠀⠀⢸⣿⣿⡏⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⠀⠀⠸⣿⣿⡇⠀⠀⢸⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠉⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⢿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⠿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀"
};

#define ASCII_LINES_COUNT 22

// Function to read a line from a file
char* read_file_line(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    static char buffer[256];
    if (fgets(buffer, sizeof(buffer), file)) {
        // Remove newline
        buffer[strcspn(buffer, "\n")] = 0;
        fclose(file);
        return buffer;
    }
    fclose(file);
    return NULL;
}

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
    
    sprintf(memory, "%ld MB / %ld MB", used_ram, total_ram);
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

// Function to print info line with ASCII art
void print_info_with_ascii(const char* color, const char* label, const char* value, int line_num) {
    const int target_col = 40;
    const int min_padding = 2;
    // Calculate the maximum allowed length for the value string to keep alignment
    int max_value_len = target_col - strlen(label) - 2 /* for ": " */ - min_padding;

    char truncated_value[256];
    strncpy(truncated_value, value, sizeof(truncated_value) - 1);
    truncated_value[sizeof(truncated_value) - 1] = '\0'; // Ensure null termination

    // If the value is too long, truncate it and add "..."
    if (strlen(truncated_value) > max_value_len) {
        truncated_value[max_value_len - 3] = '\0'; // Make space for "..."
        strcat(truncated_value, "...");
    }

    // Calculate visible length with the (possibly) truncated value
    int visible_len = strlen(label) + strlen(truncated_value) + 2; // +2 for ": "

    // Print the info line
    printf("%s%s%s%s: %s", color, BOLD, label, RESET, truncated_value);

    // Add padding to reach the target column
    int padding = target_col - visible_len;
    if (padding < min_padding) padding = min_padding;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    if (line_num < ASCII_LINES_COUNT) {
        printf("%s%s%s", CYAN, ascii_lines[line_num], RESET);
    }
    printf("\n");
}

// Function to print just ASCII art line
void print_ascii_line(int line_num) {
    // Pad to column 40
    for (int i = 0; i < 40; i++) {
        printf(" ");
    }
    
    if (line_num < ASCII_LINES_COUNT) {
        printf("%s%s%s", CYAN, ascii_lines[line_num], RESET);
    }
    printf("\n");
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
    char uptime[256] = {0};
    char cpu[256] = {0};
    char shell[256] = {0};
    
    get_os_info(os_name, kernel);
    get_memory_info(memory);
    get_uptime(uptime);
    get_cpu_info(cpu);
    get_shell_info(shell);
    
    printf("\n");
    
    // Print header with ASCII art
    printf("%s%s%s@%s%s", CYAN, BOLD, pw->pw_name, hostname, RESET);
    
    // Calculate visible length and pad to column 40
    int header_visible_len = strlen(pw->pw_name) + strlen(hostname) + 1;
    int header_padding = 40 - header_visible_len;
    if (header_padding < 2) header_padding = 2;
    
    for (int i = 0; i < header_padding; i++) {
        printf(" ");
    }
    
    printf("%s%s%s", CYAN, ascii_lines[0], RESET);
    printf("\n");
    
    // Print separator with ASCII art
    int header_len = strlen(pw->pw_name) + strlen(hostname) + 1;
    for (int i = 0; i < header_len; i++) {
        printf("%s-%s", CYAN, RESET);
    }
    
    for (int i = 0; i < header_padding; i++) {
        printf(" ");
    }
    
    printf("%s%s%s", CYAN, ascii_lines[1], RESET);
    printf("\n");
    
    // Print system info with ASCII art
    print_info_with_ascii(RED, "OS", os_name, 2);
    print_info_with_ascii(GREEN, "Kernel", kernel, 3);
    print_info_with_ascii(YELLOW, "Uptime", uptime, 4);
    print_info_with_ascii(BLUE, "Shell", shell, 5);
    print_info_with_ascii(MAGENTA, "CPU", cpu, 6);
    print_info_with_ascii(CYAN, "Memory", memory, 7);
    
    // Print color palette with ASCII art
    printf("%sColors%s: ", WHITE, RESET);
    printf("%s●%s ", RED, RESET);
    printf("%s●%s ", GREEN, RESET);
    printf("%s●%s ", YELLOW, RESET);
    printf("%s●%s ", BLUE, RESET);
    printf("%s●%s ", MAGENTA, RESET);
    printf("%s●%s ", CYAN, RESET);
    printf("%s●%s ", WHITE, RESET);
    
    // Correctly calculate color line visible length and pad to column 40
    // "Colors: " is 8 chars. Each colored "● " is 2 chars. 7 sets of them. Total = 8 + (7*2) = 22.
    int color_visible_len = 22;
    int color_padding = 40 - color_visible_len;
    if (color_padding < 2) color_padding = 2;
    
    for (int i = 0; i < color_padding; i++) {
        printf(" ");
    }
    
    printf("%s%s%s", CYAN, ascii_lines[8], RESET);
    printf("\n");
    
    // Print remaining ASCII art lines
    for (int i = 9; i < ASCII_LINES_COUNT; i++) {
        print_ascii_line(i);
    }
    
    printf("\n");
    
    return 0;
}
