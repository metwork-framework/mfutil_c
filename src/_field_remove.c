#include <glib.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "field.h"

static gchar *separator = ":";
static gboolean use_wildcards = FALSE;
static GOptionEntry entries[] = {
    { "use-wildcards", 'w', 0, G_OPTION_ARG_NONE, &use_wildcards, "use wildcards in value", NULL },
    { "separator", 's', 0, G_OPTION_ARG_STRING, &separator, "list separator", "SEPARATOR" },
    { 0, 0, 0, 0, 0, 0, 0 }
};

int main(int argc, char *argv[])
{
    GOptionContext *context;
    setlocale(LC_ALL, "");
    context = g_option_context_new("LIST_OF_VALUES VALUE_TO_REMOVE - remove a value from a list of values separated with a given separator");
    g_option_context_add_main_entries(context, entries, NULL);
    if (!g_option_context_parse(context, &argc, &argv, NULL)) {
        g_print("%s", g_option_context_get_help(context, TRUE, NULL));
        return 1;
    }
    if (argc != 3) {
        g_print("%s", g_option_context_get_help(context, TRUE, NULL));
        return 1;
    }
    gchar *res = field_remove(argv[1], argv[2], separator, use_wildcards);
    g_print("%s\n", res);
    g_free(res);
    g_option_context_free(context);
    return 0;
}
