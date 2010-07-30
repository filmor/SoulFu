#ifndef SOULFU_CHARACT_H
#define SOULFU_CHARACT_H

// <ZZ> This file has stuff for moving characters and stuff.  Stuff.


/* charact.c */
void character_action_setup(void);
void character_collide_all(void);
void character_shadow_draw_all(void);
void character_draw_all_prime(void);
void character_draw_all(unsigned char after_water, unsigned char draw_only_doors);
void char_collision_point(float *position_xyz, float *velocity_xyz, float x_offset, float y_offset);
void char_floor_point(float *position_xyz);
void character_update_all(void);
void character_bone_frame_clear(void);
void character_bone_frame_all(void);
void character_button_function(unsigned short character, unsigned char code, unsigned char button, unsigned char axis);
void character_local_player_control(void);
void character_refresh_items_all(void);

#endif
