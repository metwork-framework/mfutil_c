#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>

#include "field.h"

/**
 * Prepend a value in a list of values (as string) separated with a given separator.
 *
 * If the value is already in the list, the value is moved at the
 * beggining but not duplicated.
 *
 * @param list_of_values list of values (as string) separated with a separator.
 * @param value value to prepend.
 * @param separator separator of values.
 * @return allocated new list of values (as string) (free with g_free).
 */
gchar *field_prepend(const gchar *list_of_values, const gchar *value,
        const gchar *separator)
{
    if (value == NULL) {
        return g_strdup(list_of_values);
    }
    gchar **tmp = NULL;
    guint size = 0;
    if (list_of_values != NULL) {
        tmp = g_strsplit(list_of_values, separator, 0);
        size = g_strv_length(tmp);
    }
    GString *out = NULL;
    gboolean first = TRUE;
    if (strlen(value) > 0) {
        out = g_string_new(value);
        first = FALSE;
    } else {
        out = g_string_new(NULL);
    }
    for (guint i = 0 ; i < size ; i++) {
        if (g_strcmp0(tmp[i], value) != 0) {
            if (!first) {
                out = g_string_append(out, separator);
            }
            out = g_string_append(out, tmp[i]);
            first = FALSE;
        }
    }
    g_strfreev(tmp);
    return g_string_free(out, FALSE);
}

/**
 * Remove a value in a list of values (as string) separated with a given separator.
 *
 * You can use wildcards in value if you set use_wilcards=TRUE.
 *
 * @param list_of_values list of values (as string) separated with a separator.
 * @param value value to remove.
 * @param separator separator of values.
 * @param use_wildcards if TRUE, you can use wildcards (see g_pattern) in value.
 * @return allocated new list of values (as string) (free with g_free).
 */
gchar *field_remove(const gchar *list_of_values, const gchar *value,
        const gchar *separator, gboolean use_wildcards)
{
    if ((value == NULL) || (list_of_values == NULL))  {
        return g_strdup(list_of_values);
    }
    gchar **tmp = g_strsplit(list_of_values, separator, 0);
    guint size = g_strv_length(tmp);
    GString *out = g_string_new(NULL);
    GPatternSpec *pattern = NULL;
    gboolean first = TRUE;
    gboolean match = FALSE;
    if (use_wildcards) {
        pattern = g_pattern_spec_new(value);
    }
    for (guint i = 0 ; i < size ; i++) {
        if (!use_wildcards) {
            match = (g_strcmp0(tmp[i], value) == 0);
        } else {
            match = g_pattern_match_string(pattern, tmp[i]);
        }
        if (!match) {
            if (!first) {
                out = g_string_append(out, separator);
            }
            out = g_string_append(out, tmp[i]);
            first = FALSE;
        }
    }
    g_strfreev(tmp);
    if (use_wildcards) {
        g_pattern_spec_free(pattern);
    }
    return g_string_free(out, FALSE);
}

/**
 * Remove a value in an environnement variable containing list of values (as string) separated with a ":" separator.
 *
 * You can use wildcards in value if you set use_wilcards=TRUE.
 *
 * @param env_variable environnement variable containing list of values (as string) separated with a ":" separator.
 * @param value value to remove.
 * @param use_wildcards if TRUE, you can use wildcards (see g_pattern) in value.
 * @param bash_cmds if not NULL, bash commands to do the same operation in bash will be appended.
 */
void field_remove_env(const gchar *env_variable, const gchar *value,
        gboolean use_wildcards, GString **bash_cmds)
{
    const gchar *variable = g_getenv(env_variable);
    gchar *new_value;
    if (variable != NULL) {
        new_value = field_remove(variable, value, ":", use_wildcards);
    } else {
        new_value = field_remove("", value, ":", use_wildcards);
    }
    g_setenv(env_variable, new_value, TRUE);
    if (bash_cmds != NULL) {
        g_string_append_printf(*bash_cmds, "export %s=\"%s\";\n", env_variable, new_value);
    }
    g_free(new_value);
}

/**
 * Prepend a value in an environnement variable containing a list of values (as string) separated with the ":" separator.
 *
 * If the value is already in the list, the value is moved at the
 * beggining but not duplicated.
 *
 * @param env_variable environnement variable containing list of values (as string) separated with a ":" separator.
 * @param value value to prepend.
 * @param bash_cmds if not NULL, bash commands to do the same operation in bash will be appended.
 */
void field_prepend_env(const gchar *env_variable, const gchar *value,
        GString **bash_cmds)
{
    const gchar *variable = g_getenv(env_variable);
    gchar *new_value;
    if (variable != NULL) {
        new_value = field_prepend(variable, value, ":");
    } else {
        new_value = field_prepend("", value, ":");
    }
    g_setenv(env_variable, new_value, TRUE);
    if (bash_cmds != NULL) {
        g_string_append_printf(*bash_cmds, "export %s=\"%s\";\n",
                env_variable, new_value);
    }
    g_free(new_value);
}

/**
 * Prepend the fullpath of a directory in a given environnement variable containing list of values separated with ":" separator.
 *
 * If the directory does not exist and force_prepend is FALSE, the environnement variable is untouched
 *
 * @param directory root directory
 * @param directory_name directory name (will be added to directory variable with a "/" as separator) to get the fullpath of the directory.
 * @param env_variable environnement variable containing list of values (as string) separated with a separator.
 * @param bash_cmds if not NULL, bash commands to do the same operation in bash will be appended.
 * @see field_prepend_env
 */
void conditional_prepend_env(const gchar *directory, const gchar *directory_name,
        gboolean force_prepend, const gchar *env_variable, GString **bash_cmds)
{
    gchar *full_path = g_strdup_printf("%s/%s", directory, directory_name);
    if (force_prepend || g_file_test(full_path, G_FILE_TEST_IS_DIR) == TRUE) {
        field_prepend_env(env_variable, full_path, bash_cmds);
    }
    g_free(full_path);
}
