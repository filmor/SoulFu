#ifndef SOULFU_LOGFILE_H
#define SOULFU_LOGFILE_H

// <ZZ> This file contains functions for handling the logfile.txt file
//      log_message             - Writes a message to the log file using printf style
//                                formatting
//      close_logfile           - Closes the logfile, automatically called via atexit()
//      open_logfile            - Opens the logfile

extern int log_error_count;

/* logfile.c */
void log_message(char *format, ...);
void close_logfile(void);
signed char open_logfile(void);
#endif
