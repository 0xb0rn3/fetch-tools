#include "common/fetch.h"

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
    
    // Print Dragon ASCII art with system information
    printf("\n");
    int info_line = 0;
    for (int i = 0; i < sizeof(DRAGON_ART) / sizeof(DRAGON_ART[0]); i++) {
        printf("%s%s%s", RED, DRAGON_ART[i], RESET);
        
        // Print system information alongside the art
        switch(info_line) {
            case 0:
                printf("  %s%s%s@%s%s%s", BOLD, info.username, BLUE, info.hostname, RESET, RESET);
                break;
            case 1:
                printf("  %s%s%s", BOLD, "OS: ", RESET);
                printf("%s", info.os_name);
                break;
            case 2:
                printf("  %s%s%s", BOLD, "KERNEL: ", RESET);
                printf("%s", info.kernel);
                break;
            case 3:
                printf("  %s%s%s", BOLD, "SHELL: ", RESET);
                printf("%s", info.shell);
                break;
            case 4:
                printf("  %s%s%s", BOLD, "CPU: ", RESET);
                printf("%s", info.cpu_info);
                break;
            case 5:
                printf("  %s%s%s", BOLD, "MEMORY: ", RESET);
                printf("%s", info.memory);
                break;
            case 6:
                printf("  %s%s%s", BOLD, "DISK: ", RESET);
                printf("%s", info.disk_space);
                break;
            case 7:
                printf("  %s%s%s", BOLD, "UPTIME: ", RESET);
                printf("%s", info.uptime);
                break;
        }
        printf("\n");
        info_line++;
    }
    printf("\n");
    return 0;
}
