#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOGO_WIDTH 42  // The width of the logo

void print_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}

char *get_system_info(const char *command) {
    char *info = NULL;
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        print_error("Failed to execute command");
    }
    char buf[1024];
    if (fgets(buf, sizeof(buf), fp) != NULL) {
        size_t len = strlen(buf);
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
            len--;
        }
        info = (char *) malloc(len + 1);
        if (info == NULL) {
            print_error("Failed to allocate memory");
        }
        strncpy(info, buf, len);
        info[len] = '\0';
    }
    pclose(fp);
    return info;
}

void print_system_info(const char *os_info, const char *cpu_info) {
    char *logo = "            .-\"\"\"-.\n"
                 "           '       \\\n"
                 "          |,.  ,-.  |\n"
                 "          |()L( ()| |\n"
                 "          |,'  `\".| |\n"
                 "          |.___.,| `\n"
                 "         .j `--\"' `  `.\n"
                 "        / '        '   \\\n"
                 "       / /          `   `.\n"
                 "      / /            `    .\n"
                 "     / /              l   |\n"
                 "    . ,               |   |\n"
                 "    ,\"`.             .|   |\n"
                 " _.'   ``.          | `..-'l\n"
                 "|       `.`,        |      `.\n"
                 "|         `.    __.j         )\n"
                 "|__        |--\"\"___|      ,-'\n"
                 "   `\"--...,+\"\"\"\"   `._,.-'\"\n";
    printf("%s\n", logo);
    printf("%-*s%s", LOGO_WIDTH, "", "Operating System:\n");
    printf("%*s%s\n", LOGO_WIDTH, "", os_info);
    printf("%-*s%s", LOGO_WIDTH, "", "CPU Information:\n");
    printf("%*s%s\n", LOGO_WIDTH, "", cpu_info);
}

int main() {
    char *os_info = get_system_info("uname -a");
    if (os_info == NULL) {
        print_error("Failed to get operating system information");
    }
    char *cpu_info = get_system_info("cat /proc/cpuinfo | grep 'model name' | uniq");
    if (cpu_info == NULL) {
        print_error("Failed to get CPU information");
    }
    print_system_info(os_info, cpu_info);
    free(os_info);
    free(cpu_info);
    return 0;
}
