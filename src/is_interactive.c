#include <glib.h>
#include "mfutil.h"
#include <locale.h>
#include <stdio.h>

static GOptionEntry entries[] = {
    { 0, 0, 0, 0, 0, 0, 0 }
};

int main(int argc, char *argv[])
{
    /**
     * Variables globales
     */
    GError *error = NULL;
    GOptionContext *context;
    int res = 0;

    /**
     * Parsing de la ligne de commande
     */
    setlocale(LC_ALL, "");
    context = g_option_context_new("- return status code 0 if we guess this is an interactive execution");
    g_option_context_add_main_entries(context, entries, NULL);
    if (!g_option_context_parse (context, &argc, &argv, &error)) {
        g_print("%s", g_option_context_get_help(context, TRUE, NULL));
        fprintf(stderr, "ERROR WHEN COMMAND LINE PARSING\n");
    }

    /**
     * Appel
     */
    gboolean is = mfutil_is_interactive_execution();
    if (is == FALSE) {
        res = 1;
    }

    /**
     * Libération / sortie
     */
    return res;
}
