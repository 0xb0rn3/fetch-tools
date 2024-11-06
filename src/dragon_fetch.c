#include "common/fetch.h"

const char* ANIME_ART[] = {
    "⠀⠀⠀⠀⢀⡠⠤⠔⢲⢶⡖⠒⠤⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    "⠀⠀⣠⡚⠁⢀⠀⠀⢄⢻⣿⠀⠀⠀⡙⣷⢤⡀⠀⠀⠀⠀⠀⠀",
    "⠀⡜⢱⣇⠀⣧⢣⡀⠀⡀⢻⡇⠀⡄⢰⣿⣷⡌⣢⡀⠀⠀⠀⠀",
    "⠸⡇⡎⡿⣆⠹⣷⡹⣄⠙⣽⣿⢸⣧⣼⣿⣿⣿⣶⣼⣆⠀⠀⠀",
    "⣷⡇⣷⡇⢹⢳⡽⣿⡽⣷⡜⣿⣾⢸⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀",
    "⣿⡇⡿⣿⠀⠣⠹⣾⣿⣮⠿⣞⣿⢸⣿⣛⢿⣿⡟⠯⠉⠙⠛⠓",
    "⣿⣇⣷⠙⡇⠀⠁⠀⠉⣽⣷⣾⢿⢸⣿⠀⢸⣿⢿⠀⠀⠀⠀⠀",
    "⡟⢿⣿⣷⣾⣆⠀⠀⠘⠘⠿⠛⢸⣼⣿⢖⣼⣿⠘⡆⠀⠀⠀⠀",
    "⠃⢸⣿⣿⡘⠋⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⡆⠇⠀⠀⠀⠀",
    "⠀⢸⡿⣿⣇⠀⠈⠀⠤⠀⠀⢀⣿⣿⣿⣿⣿⣿⣧⢸⠀⠀⠀⠀",
    "⠀⠈⡇⣿⣿⣷⣤⣀⠀⣀⠔⠋⣿⣿⣿⣿⣿⡟⣿⡞⡄⠀⠀⠀",
    "⠀⠀⢿⢸⣿⣿⣿⣿⣿⡇⠀⢠⣿⡏⢿⣿⣿⡇⢸⣇⠇⠀⠀⠀",
    "⠀⠀⢸⡏⣿⣿⣿⠟⠋⣀⠠⣾⣿⠡⠀⢉⢟⠷⢼⣿⣿⠀⠀⠀",
    "⠀⠀⠈⣷⡏⡱⠁⠀⠊⠀⠀⣿⣏⣀⡠⢣⠃⠀⠀⢹⣿⡄⠀⠀",
    "⠀⠀⠘⢼⣿⠀⢠⣤⣀⠉⣹⡿⠀⠁⠀⡸⠀⠀⠀⠈⣿⡇⠀⠀"
};

void print_color_blocks() {
    printf("\n");
    // Print color blocks
    for(int i = 0; i < 8; i++) {
        printf("\033[4%dm   ", i);
    }
    printf(RESET "\n");
    for(int i = 0; i < 8; i++) {
        printf("\033[10%dm   ", i);
    }
    printf(RESET "\n\n");
}

int main() {
    SystemInfo info;
    get_system_info(&info);
    
    printf("\n");
    int info_line = 0;
    
    for (int i = 0; i < sizeof(ANIME_ART) / sizeof(ANIME_ART[0]); i++) {
        printf("%s%s%s", CYAN, ANIME_ART[i], RESET);
        
        switch(info_line) {
            case 0:
                printf("  %s%s%s@%s%s%s", BOLD, info.username, CYAN, info.hostname, RESET, RESET);
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
    
    print_color_blocks();
    return 0;
}
