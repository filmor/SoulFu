#ifndef SOULFU_SOUND_H
#define SOULFU_SOUND_H

#define LEFT 0
#define RIGHT 1

#define MAX_CHANNEL 64                  // Maximum number of simultaneous sounds

extern int music_tempo;
extern unsigned char channel_new_volume[MAX_CHANNEL][2];
extern unsigned char sound_flip_pan;

extern unsigned char main_volume;              // For fades...
extern unsigned char master_sfx_volume;        // User option
extern unsigned char master_music_volume;      // User option

/* sound.c */
void play_sound(unsigned int start_delay, unsigned char *sound_file_start, unsigned char volume, unsigned char pan, unsigned short pitch_skip, unsigned char *loop_data);
void sound_reset_channels(void);
void sound_setup(void);
void fill_sound_buffer(void);
void fill_music(void);
void play_music(unsigned char *filedata, unsigned short start_time, unsigned char mode);
#endif
