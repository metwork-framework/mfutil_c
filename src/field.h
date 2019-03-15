#ifndef FIELD_H_
#define FIELD_H_

#include <glib.h>

gchar *field_prepend(const gchar *list_of_values, const gchar *value,
        const gchar *separator);

gchar *field_remove(const gchar *list_of_values, const gchar *value,
        const gchar *separator, gboolean use_wildcards);

void field_remove_env(const gchar *env_variable, const gchar *value,
        gboolean use_wildcards, GString **bash_cmds);

void field_prepend_env(const gchar *env_variable, const gchar *value,
        GString **bash_cmds);

void conditional_prepend_env(const gchar *directory, const gchar *directory_name,
        gboolean force_prepend, const gchar *env_variable, GString **bash_cmds);


#endif /* FIELD_H_ */
