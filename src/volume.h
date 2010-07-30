#ifndef SOULFU_VOLUME_H
#define SOULFU_VOLUME_H

/* volume.c */
void volume_shadow_edge(float *start_xyz, float *end_xyz);
void volume_rdy_find_temp_stuff(unsigned char *data, unsigned short frame);
void volume_rdy_character_shadow(unsigned char *data, unsigned short frame, unsigned char *bone_frame_data);
void volume_draw_room_shadows(unsigned char *data);
void volume_shadow_draw_all(void);
#endif
