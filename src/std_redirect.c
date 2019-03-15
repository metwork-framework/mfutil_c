#include <glib.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "wrapper.h"

static gchar *stdout_target = NULL;
static gchar *stderr_target = NULL;

static GOptionEntry entries[] = {
    { "stdout", 'o', 0, G_OPTION_ARG_STRING, &stdout_target, "if set, redirect stdout to this file", NULL },
    { "stderr", 'e', 0, G_OPTION_ARG_STRING, &stderr_target, "if set, redirect stderr to this file", NULL },
    { 0, 0, 0, 0, 0, 0, 0 }
};

void redirect_std(int source, gchar *target) {
    if (target == NULL) {
        return;
    }
    int fd = open(target, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        g_warning("can't create/open %s for appending", target);
        exit(2);
    }
    dup2(fd, source);
    close(fd);
}

int main(int argc, char *argv[])
{
    GOptionContext *context;
    setlocale(LC_ALL, "");
    context = g_option_context_new("-- COMMAND [COMMAND_ARG1] [COMMAND_ARG2] [...] - wrapper to execute the given command with stdout/strerr redirection");
    g_option_context_add_main_entries(context, entries, NULL);
    if (!g_option_context_parse(context, &argc, &argv, NULL)) {
        g_print(g_option_context_get_help(context, TRUE, NULL));
        return 1;
    }
    if (argc < 2) {
        g_print(g_option_context_get_help(context, TRUE, NULL));
        return 1;
    }
    if (argc == 2) {
        if (g_strcmp0(argv[1], "--") == 0) {
            g_print(g_option_context_get_help(context, TRUE, NULL));
            return 1;
        }
    }
    redirect_std(1, stdout_target);
    redirect_std(2, stderr_target);
    return wrapper(argc, argv);
}
