#include "fetch.h"

char* get_command_output(const char* cmd) {
    FILE* fp = popen(cmd, "r");
    if (!fp) return NULL;
    
    char* output = malloc(1024);
    if (fgets(output, 1024, fp) != NULL) {
        output[strcspn(output, "\n")] = 0;
    } else {
        free(output);
        output = NULL;
    }
    pclose(fp);
    return output;
}

void get_system_info(SystemInfo *info) {
    struct utsname uts;
    struct sysinfo si;
    struct passwd *pw;
    
    // Get basic system information
    uname(&uts);
    sysinfo(&si);
    pw = getpwuid(getuid());
    
    // Hostname and username
    strncpy(info->hostname, uts.nodename, sizeof(info->hostname) - 1);
    strncpy(info->username, pw->pw_name, sizeof(info->username) - 1);
    
    // Kernel information
    snprintf(info->kernel, sizeof(info->kernel), "%s %s", uts.sysname, uts.release);
    
    // OS Information
    FILE *os_release = fopen("/etc/os-release", "r");
    if (os_release) {
        char line[256];
        while (fgets(line, sizeof(line), os_release)) {
            if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
                char *name = strchr(line, '=') + 2;
                name[strlen(name)-2] = '\0';
                strncpy(info->os_name, name, sizeof(info->os_name) - 1);
                break;
            }
        }
        fclose(os_release);
    }
    
    // Shell information
    char *shell = getenv("SHELL");
    if (shell) {
        char *shell_name = strrchr(shell, '/');
        strncpy(info->shell, shell_name ? shell_name + 1 : shell, sizeof(info->shell) - 1);
    }
    
    // CPU Information
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo) {
        char line[256];
        while (fgets(line, sizeof(line), cpuinfo)) {
            if (strncmp(line, "model name", 10) == 0) {
                char *model = strchr(line, ':') + 2;
                model[strlen(model)-1] = '\0';
                strncpy(info->cpu_info, model, sizeof(info->cpu_info) - 1);
                break;
            }
        }
        fclose(cpuinfo);
    }
    
    // Memory information
    unsigned long total_ram = si.totalram * si.mem_unit / (1024 * 1024);
    unsigned long used_ram = (si.totalram - si.freeram) * si.mem_unit / (1024 * 1024);
    snprintf(info->memory, sizeof(info->memory), "%lu MB / %lu MB", used_ram, total_ram);
    
    // Disk space
    char *df_cmd = "df -h / | tail -n 1 | awk '{print $3\"/\"$2\" (\"$5\")\"}\'";
    char *disk = get_command_output(df_cmd);
    if (disk) {
        strncpy(info->disk_space, disk, sizeof(info->disk_space) - 1);
        free(disk);
    }

    // Uptime calculation
    unsigned long uptime = si.uptime;
    unsigned long days = uptime / 86400;
    unsigned long hours = (uptime % 86400) / 3600;
    unsigned long minutes = (uptime % 3600) / 60;
    snprintf(info->uptime, sizeof(info->uptime), "%lu days, %lu hours, %lu minutes", 
             days, hours, minutes);
}

void print_info_line(const char* label, const char* value) {
    printf("%s%s%s: %s%s%s\n", BOLD, label, RESET, CYAN, value, RESET);
}
