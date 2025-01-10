#include "common/fetch.h"

#define COLOR_PRIMARY    "\033[38;5;39m"   // Bright blue for primary text
#define COLOR_SECONDARY  "\033[38;5;147m"  // Light purple for secondary text
#define COLOR_ACCENT    "\033[38;5;208m"   // Orange for accents
#define COLOR_LABEL     "\033[1;38;5;255m" // Bright white for labels
#define SEPARATOR       "═"                // Unicode box drawing character for separators

const char* DRAGON_ART[] = {
    "⠀⠀⠀⠀⠀⠀⠀⣀⣤⠴⠖⠚⠛⠛⠙⠛⠓⠒⠦⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀   ",
    "⠀⠀⠀⠀⣠⡴⠋⠁⠀⢠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠦⣀⠀⠀⠀⠀⠀  ",
    "⠀⠀⣠⠞⠁⠀⠀⠀⠀⠈⢿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⡄⠀⠀⠀  ",
    "⠀⣴⠋⠀⠀⠀⠀⢦⣄⠰⣄⡛⢿⣷⣦⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠘⢆⠀⠀  ",
    "⣼⠁⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣷⣦⣀⠀⠀⠀⠀⠀⠈⢇⠀  ",
    "⢰⠇⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣌⡻⣿⣄⠀⠀⠀⠀⠀⠘⡆  ",
    "⣾⠀⠀⠀⠀⢀⣾⣿⣿⡿⢚⣿⡿⠟⠙⢿⣿⣿⣿⡟⠻⢿⣿⣷⣶⣆⠀⠀⠀",
    "⣿⠀⠀⠀⠀⣼⣿⡿⣫⣾⡖⠀⠐⣿⠗⠀⠉⠻⣿⣷⠀⠀⠈⠙⢿⡏⠀⠀⠀",
    "⢿⠀⠀⠀⠀⣿⣿⣵⣿⡟⢴⣦⣤⠙⠀⠀⠀⢀⣼⣿⣆⡀⠀⠀⠘⠀⠀⠀⠀",
    "⠸⡄⠀⠀⠀⡿⢻⣿⣿⡇⡌⢻⣿⡀⠀⠀⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⢀⠃",
    "⢳⡀⠀⠀⠇⠸⣿⣿⡇⣧⡀⠈⠓⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠌   ",
    "⠀⠳⡄⠀⠀⠀⢻⣿⣇⢻⣷⡴⢦⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠎⠀   ",
    "⠀⠀⠘⢦⡀⠀⠀⠙⣿⡀⠻⠿⢶⣤⣀⣀⠀⠀⠀⠀⠀⠀⢀⠔⠁     ",
    "⠀⠀⠀⠀⠉⠲⢄⡀⠈⠓⠄⠀⠀⠀⠀⠉⠁⠀⠀⠀⡠⠔⠁       ",
    "⠀⠀⠀⠀⠀⠀⠀⠉⠑⠒⠤⠤⠤⠤⠂⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
};

int main() {
    SystemInfo info;
    get_system_info(&info);
    
    // Configuration for consistent formatting
    FormatConfig format = {
        .label_color = COLOR_LABEL,
        .value_color = COLOR_SECONDARY,
        .separator = "│",
        .padding = -12  // Negative padding for left alignment
    };
    
    printf("\n");
    
    // Print header with username and hostname
    printf("%s%s%s@%s%s%s\n", 
           COLOR_PRIMARY, info.username,
           COLOR_ACCENT, COLOR_PRIMARY, info.hostname,
           RESET);
    
    print_separator(40, COLOR_SECONDARY);
    
    // Print system information with consistent formatting
    print_system_info("OS", info.os_name, &format);
    print_system_info("KERNEL", info.kernel, &format);
    print_system_info("SHELL", info.shell, &format);
    print_system_info("CPU", info.cpu_info, &format);
    print_system_info("MEMORY", info.memory, &format);
    print_system_info("DISK", info.disk_space, &format);
    print_system_info("UPTIME", info.uptime, &format);
    
    print_separator(40, COLOR_SECONDARY);
    
    // Print color palette
    printf("\nColor Palette:\n");
    for (int i = 0; i < 8; i++) {
        printf("\033[48;5;%dm   ", i);
    }
    printf("%s\n", RESET);
    
    printf("\n");
    return 0;
