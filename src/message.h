#ifndef SOULFU_MESSAGE_H
#define SOULFU_MESSAGE_H

/* message.c */
void message_reset(void);
void message_setup(void);
void message_sanitize(char *message_text);
void message_add(char *message_text, char *speaker_name, unsigned char sanitize);
void language_message_add(unsigned short message_index);
#endif
