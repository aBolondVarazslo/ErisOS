#include "shell.h"
#include "../../lib/terminal.h"
#include "../../drivers/ps2/ps2.h"

#define NUM_COMMANDS (sizeof(commands) / sizeof(commands[0]))

void terminal_readLine(char *buf, size_t max_len) {
    size_t i = 0;
    while (1) {
        int c = ps2_getChar();
        if (c == -1) continue; /* Nothing typed yet */

        if (c == '\n') {
            terminal_typeChar('\n', STATUS_NORMAL);
            break;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                terminal_typeChar('\b', STATUS_NORMAL);
            }
            /* If i == 0, nothing to delete */
            continue;
        } else if (i < max_len - 1) {
            buf[i++] = (char)c;
            terminal_typeChar((char)c, STATUS_NORMAL);
        }
    }
    buf[i] = '\0';
}

int terminal_tokenise(char *buf, char *argv[MAX_ARGS]) {
    int argc = 0;
    int i = 0;

    while (buf[i] != '\0' && argc < MAX_ARGS) {
        /* Skip spaces between words */
        while (buf[i] == ' ') {
            i++;
        }

        if (buf[i] == '\0') {
            break;
        }

        /* At the start of a word */
        argv[argc] = &buf[i];
        argc++;

        /* Walk through the word */
        while (buf[i] != ' ' && buf[i] != '\0') {
            i++;
        }

        /* Sets space to be null terminator to differenciate between words */
        if (buf[i] == ' ') {
            buf[i] = '\0';
            i++;
        }
    }

    return argc;
}

typedef void (*shell_command_fn)(int argc, char *argv[]);

static void cmd_echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        terminal_writeString(argv[i], STATUS_NORMAL);
        terminal_typeChar(' ', STATUS_NORMAL);
    }
    terminal_typeChar('\n', STATUS_NORMAL);
};

static void cmd_clear() {
    terminal_initialise();
}

static void cmd_help();

typedef struct {
    const char *name;
    shell_command_fn fn;
    const char *description;
} shell_command_t;

static const shell_command_t commands[] = {
    {"echo", cmd_echo, "Outputs text to the terminal"},
    {"clear", cmd_clear, "Clears the terminal"},
    {"help", cmd_help, "Outputs commands and descriptions to the terminal"}
};

static void cmd_help() {
    for (int i = 0; i < NUM_COMMANDS; i++) {
        size_t len = strlen(commands[i].name);

        terminal_writeString(commands[i].name, STATUS_NORMAL);

        if (len < 10) {
            for(size_t i = len; i < 10; i++) {
                terminal_typeChar(' ', STATUS_NORMAL);
            }
        } else {
            terminal_typeChar(' ', STATUS_NORMAL);
        }

        terminal_writeString(commands[i].description,STATUS_NORMAL);
        terminal_typeChar('\n', STATUS_NORMAL);
    }
}

static void shell_dispatch(int argc, char *argv[]) {
    /* Empty line entered */
    if (argc == 0) return;

    /* Loop through every registered command in the table */
    for (size_t i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(argv[0], commands[i].name) == 0) {
            commands[i].fn(argc, argv);
            return;
        }
    }

    /* Fallback if command isn't valid */
    terminal_writeString("Unknown command: ", STATUS_FAILURE);
    terminal_writeString(argv[0], STATUS_FAILURE);
    terminal_typeChar('\n', STATUS_FAILURE);
}

void shell_run(void) {
    /* Creates buffer and argument arrays */
    char buf[MAX_LINE];
    char *argv[MAX_ARGS];

    while (1) {
        /* Terminal prompt */
        terminal_writeString("> ", STATUS_NORMAL);
        terminal_readLine(buf, sizeof(buf));

        /* Breaks input into command and arguments and runs it */
        int argc = terminal_tokenise(buf, argv);
        shell_dispatch(argc, argv);
    }
}