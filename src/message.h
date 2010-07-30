#ifndef SOULFU_MESSAGE_H
#define SOULFU_MESSAGE_H

// <ZZ> This file contains functions to handle the message buffer
//      message_get         - Macro that returns a pointer to one of the last 16 messages
//      message_reset       - Clears out the message buffer
//      message_sanitize    - Replaces "bad" words with #@$% style text
//      message_add         - Adds a message to the message buffer


extern unsigned char* sanitize_file;

/* message.c */
void message_reset(void);
void message_setup(void);
void message_sanitize(char *message_text);
void message_add(char *message_text, char *speaker_name, unsigned char sanitize);
void language_message_add(unsigned short message_index);
#endif
