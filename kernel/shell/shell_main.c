#include <kfsdef.h>
#include <kfslib.h>
#include <io.h>

char buffer[2048];

char *readline(char* prompt){
    printk(prompt);
    return buffer;
}

size_t  shell_main(void) {
    size_t exit_code = 1;

    char *line = readline("$>");
    (void)line;
    return exit_code;
}