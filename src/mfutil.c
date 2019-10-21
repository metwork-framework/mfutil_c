#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "mfutil.h"
#include "_mfutil.h"

GRand *__rand = NULL;

GRand *__get_grand()
{
    if (__rand == NULL) {
        __rand = g_rand_new();
    }
    return __rand;
}

/**
 * Return the current timestamp.
 *
 * @return current timestamp
 */
glong mfutil_get_current_timestamp()
{
    GTimeVal gtv;
    g_get_current_time(&gtv);
    return gtv.tv_sec;
}

/**
 * Retourne un identifiant "unique" sous forme d'une chaine hexa allouée
 *
 * @return identifiant "unique" hexa (à libérer par g_free)
 */
gchar *mfutil_get_unique_hexa_identifier()
{
    GRand *rnd = __get_grand();
    gchar *res = g_malloc(sizeof(gchar) * 33);
    guint32 ri;
    int i;
    for (i = 0 ; i < 4 ; i++) {
        ri = g_rand_int(rnd);
        sprintf(res + (i * 8) * sizeof(gchar),  "%08x", ri);
    }
    return res;
}

void mfutil_echo_clean()
{
    printf("%s%i%s", "\033[", MFUTIL_COLUMN_OK, "G           ");
}

void mfutil_echo_something(const gchar *code, const gchar *before, const gchar *after, const gchar *message, const gchar *line_end)
{
    gboolean interactive = mfutil_is_interactive_execution();
    if (interactive) {
        printf("%s%i%s", "\033[", MFUTIL_COLUMN_OK, "G");
        if ((message == NULL) || (strlen(message) == 0)) {
            printf("[ %s%s%s ]%s", before, code, after, line_end);
        } else {
            printf("[ %s%s%s ] %s%s", before, code, after, message, line_end);
        }
    } else {
        if ((message == NULL) || (strlen(message) == 0)) {
            printf("[ %s%s%s ]%s", before, code, after, line_end);
        } else {
            printf("[ %s%s%s ] %s%s", before, code, after, message, line_end);
        }
    }
}

void mfutil_echo_ok(const gchar *message)
{
    gboolean interactive = mfutil_is_interactive_execution();
    if (interactive) {
        mfutil_echo_clean();
        mfutil_echo_something("OK", MFUTIL_ANSI_COLOR_GREEN, MFUTIL_ANSI_COLOR_NORMAL, message, "\n");
    } else {
        mfutil_echo_something("OK", "", "", message, "\n");
    }
}

void mfutil_echo_running()
{
    gboolean interactive = mfutil_is_interactive_execution();
    if (interactive) {
        mfutil_echo_clean();
        mfutil_echo_something("RUNNING", MFUTIL_ANSI_COLOR_YELLOW, MFUTIL_ANSI_COLOR_NORMAL, NULL, "");
    }
}

void mfutil_echo_nok(const gchar *message)
{
    gboolean interactive = mfutil_is_interactive_execution();
    if (interactive) {
        mfutil_echo_clean();
        mfutil_echo_something("ERROR", MFUTIL_ANSI_COLOR_RED, MFUTIL_ANSI_COLOR_NORMAL, message, "\n");
    } else {
        mfutil_echo_something("ERROR", "", "", message, "\n");
    }
}

void mfutil_echo_warning(const gchar *message)
{
    gboolean interactive = mfutil_is_interactive_execution();
    if (interactive) {
        mfutil_echo_clean();
        mfutil_echo_something("WARNING", MFUTIL_ANSI_COLOR_YELLOW, MFUTIL_ANSI_COLOR_NORMAL, message, "\n");
    } else {
        mfutil_echo_something("WARNING", "", "", message, "\n");
    }
}

/**
 * Affiche un message en gras.
 */
void mfutil_echo_bold(const gchar *message)
{
    gboolean interactive = mfutil_is_interactive_execution();
    if (interactive) {
        printf("\033[1m%s\033[0m\n", message);
    } else {
        printf("%s\n", message);
    }
}

/**
 * Retourne TRUE si l'exécution du programme se fait dans un shell interactif et si stdout et stderr dirigent vers un terminal
 *
 * Si on redirige stdout et/ou stderr vers un pipe ou un fichier, la fonction retournera FALSE
 *
 * @return TRUE si l'exécution du programme se fait dans un shell interactif, FALSE sinon
 */
gboolean mfutil_is_interactive_execution()
{
    gboolean res = TRUE;
    const gchar *tmp2 = g_getenv("NOINTERACTIVE");
    if (tmp2 != NULL) {
        if (atoi(tmp2) == 1) {
            return FALSE;
        }
    }
    struct stat buf;
    if (stat("/tmp/nointeractive", &buf) == 0) {
        if ((mfutil_get_current_timestamp() - buf.st_mtime) < 60) {
            return FALSE;
        }
    }
    if (!(isatty(fileno(stdout)))) {
        return FALSE;
    }
    if (!(isatty(fileno(stderr)))) {
        return FALSE;
    }
    return res;
}

/**
 * Free a pointer with g_free
 *
 * Can be useful only for writing non-C bindings.
 *
 * @param pointer pointer to free
 */
void mfutil_g_free(gpointer pointer)
{
    g_free(pointer);
}

/**
 * Return the file size from a filepath
 *
 * @param filepath complete filepath
 * @return file size (or -1 if problem)
 */
long mfutil_get_file_size(const gchar *filepath) {
    struct stat st;
    if (stat(filepath, &st) == 0) {
        return st.st_size;
    } else {
        return -1;
    }
}
