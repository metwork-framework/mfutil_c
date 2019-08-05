#ifndef MFUTIL_H_
#define MFUTIL_H_

#include <glib.h>

void mfutil_echo_ok(const gchar *message);
void mfutil_echo_running();
void mfutil_echo_nok(const gchar *message);
void mfutil_echo_warning(const gchar *message);
void mfutil_echo_bold(const gchar *message);
void mfutil_echo_clean();
gchar *mfutil_get_unique_hexa_identifier();
void mfutil_g_free(gpointer pointer);
long mfutil_get_file_size(const gchar *filepath);
gboolean mfutil_is_interactive_execution();

#endif /* MFUTIL_H_ */
