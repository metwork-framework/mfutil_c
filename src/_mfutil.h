#ifndef _MFUTIL_H_
#define _MFUTIL_H_

#define MFUTIL_ANSI_COLOR_RESET       "\033[0m"
#define MFUTIL_ANSI_COLOR_BLACK       "\033[30m"
#define MFUTIL_ANSI_COLOR_RED         "\033[31m"
#define MFUTIL_ANSI_COLOR_GREEN       "\033[32m"
#define MFUTIL_ANSI_COLOR_YELLOW      "\033[33m"
#define MFUTIL_ANSI_COLOR_BLUE        "\033[34m"
#define MFUTIL_ANSI_COLOR_MAGENTA     "\033[35m"
#define MFUTIL_ANSI_COLOR_CYAN        "\033[36m"
#define MFUTIL_ANSI_COLOR_WHITE       "\033[37m"
#define MFUTIL_ANSI_COLOR_BOLDBLACK   "\033[1m\033[30m"
#define MFUTIL_ANSI_COLOR_BOLDRED     "\033[1m\033[31m"
#define MFUTIL_ANSI_COLOR_BOLDGREEN   "\033[1m\033[32m"
#define MFUTIL_ANSI_COLOR_BOLDYELLOW  "\033[1m\033[33m"
#define MFUTIL_ANSI_COLOR_BOLDBLUE    "\033[1m\033[34m"
#define MFUTIL_ANSI_COLOR_BOLDMAGENTA "\033[1m\033[35m"
#define MFUTIL_ANSI_COLOR_BOLDCYAN    "\033[1m\033[36m"
#define MFUTIL_ANSI_COLOR_BOLDWHITE   "\033[1m\033[37m"

#define MFUTIL_ANSI_COLOR_OK          "\033[32;2m"
#define MFUTIL_ANSI_COLOR_NORMAL      "\033[0;0m"
#define MFUTIL_ANSI_COLOR_WARNING     "\033[33;2m"
#define MFUTIL_ANSI_COLOR_ALERT       "\033[31;2m"
#define MFUTIL_ANSI_COLOR_EMERGENCY   "\033[31;4m"

#define MFUTIL_COLUMN_OK              60

#include <glib.h>

void synutil_echo_something(const gchar *code, const gchar *before, const gchar *after, const gchar *message, const gchar *line_end);

#endif /* _MFUTIL_H_ */
