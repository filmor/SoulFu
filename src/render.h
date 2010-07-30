#ifndef SOULFU_RENDER_H
#define SOULFU_RENDER_H

// <ZZ> This file has all the stuff for rendering objects...
//      setup_shadow            - Reads shadow names from SHADOW.TXT
//      render_rdy              - Renders a model

extern unsigned char* global_bone_data;
extern unsigned short global_num_bone;

/* render.c */
unsigned char *render_generate_model_world_data(unsigned char *data, unsigned short frame, float *matrix, unsigned char *write);
void render_crunch_bone(unsigned char *data, unsigned short frame, unsigned short bone, unsigned char detail_level);
void render_crunch_vertex(unsigned char *data, unsigned short frame, unsigned short vertex, unsigned char recalc_weight, unsigned char detail_level);
void render_crunch_rdy(unsigned char *data);
void render_crunch_all(unsigned char mask);
void setup_shadow(void);
void render_bone_frame(unsigned char *base_model_data, unsigned char *bone_data, unsigned char *current_frame_data);
unsigned char render_pregenerate_normals(unsigned char *data, unsigned short frame, unsigned char detail_level);
void render_rdy(unsigned char *data, unsigned short frame, unsigned char mode, unsigned char **texture_file_data_block, unsigned char main_alpha, unsigned char *bone_frame_data, unsigned char petrify, unsigned char eye_frame);
void render_shadow_setup(void);
void render_rdy_character_shadow(unsigned char *data, unsigned char *character_data, unsigned char main_alpha, float scale, float z);
void render_rdy_shadow(unsigned char *data, unsigned short frame, float x, float y, float z, unsigned char mode);
void render_fill_temp_character_bone_number(unsigned char *data);
int render_bone_id(unsigned char *data, unsigned short frame, unsigned short joint_one, unsigned short joint_two, unsigned char bone_id);
unsigned char *get_start_of_frame(unsigned char *data, unsigned short frame);
unsigned short get_number_of_bones(unsigned char *data);
#endif
