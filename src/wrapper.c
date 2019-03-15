#include <glib.h>
#include <unistd.h>

#include "wrapper.h"

int wrapper(int argc, char *argv[])
{
    int i = 0;
    int start = 1;
    if (g_strcmp0(argv[1], "--") == 0) {
        start = 2;
    }
    int new_argc = argc - 1 - (start - 1);
    const char *command = argv[start];
    gchar **command_args = g_malloc(sizeof(gchar*) * (new_argc + 1));
    for (i = start ; i < argc ; i++ ) {
        command_args[i - start] = g_strdup(argv[i]);
    }
    command_args[new_argc] = NULL;
    int res = execvp(command, command_args);
    if (res != 0) {
        g_warning("can't launch command=%s", command);
    }
    return res;
}
