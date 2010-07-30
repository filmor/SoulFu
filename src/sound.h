#ifndef SOULFU_SOUND_H
#define SOULFU_SOUND_H

/* sound.c */
void play_sound(unsigned int start_delay, unsigned char *sound_file_start, unsigned char volume, unsigned char pan, unsigned short pitch_skip, unsigned char *loop_data);
void sound_reset_channels(void);
void sound_setup(void);
void fill_sound_buffer(void);
void fill_music(void);
void play_music(unsigned char *filedata, unsigned short start_time, unsigned char mode);
#endif
