#ifndef SOULFU_LOGFILE_H
#define SOULFU_LOGFILE_H

/* logfile.c */
void log_message(char *format, ...);
void close_logfile(void);
signed char open_logfile(void);
#endif
