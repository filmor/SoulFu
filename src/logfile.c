FILE* logfile;
int log_error_count;

void log_message(char *format, ...)
{
    // <ZZ> This function spits out a message to the logfile.txt file, following standard printf
    //      style formatting.  It also logs any errors to the message buffer (for ingame tools).
    va_list ap;
    char log_buffer[256];

    if(logfile)
    {
        va_start(ap, format);
        vsprintf(log_buffer, format, ap);
        va_end(ap);
        fprintf(logfile, "%s\n", log_buffer);
        fflush(logfile);


        #ifdef DEVTOOL
            if(log_buffer[0] == 'E' && log_error_count < 1)
            {
                log_buffer[64] = 0;
                message_add(log_buffer, NULL, FALSE);
                log_error_count++;
            }
            if(log_buffer[0] == 'F' && log_error_count == 1)
            {
                log_buffer[64] = 0;
                message_add(log_buffer, NULL, FALSE);
                log_error_count++;
            }
        #endif
    }
}


void close_logfile(void)
{
    // <ZZ> This function closes the logfile, and should be run automatically on program
    //      termination...
    if(logfile)
    {
        log_message("INFO:   Log file closed");
        fclose(logfile);
    }
}


signed char open_logfile(void)
{
    // <ZZ> This function opens up the LOGFILE.TXT file and registers close_logfile() to run
    //      on program termination.  It returns TRUE if it worked okay, FALSE if there was a
    //      problem.
    logfile = fopen("LOGFILE.TXT", "w");
    log_error_count = 0;
    if(logfile)
    {
        log_message("INFO:   Log file started");
        atexit(close_logfile);
        return TRUE;
    }
    return FALSE;
}

