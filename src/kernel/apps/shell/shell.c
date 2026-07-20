#include "shell.h"
#include "../../lib/vga.h"
#include "../../lib/terminal.h"

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

    /* Output tokenised version of string */
    for (int i = 0; i < argc; ++i) {
        terminal_writeString(argv[i], STATUS_DEBUG);
        terminal_typeChar('\n', STATUS_DEBUG);
    }
    
    return argc;
}