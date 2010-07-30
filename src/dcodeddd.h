#ifndef SOULFU_DCODEDDD_H
#define SOULFU_DCODEDDD_H

// <ZZ> This file contains functions to convert DDD files to RDY
//      decode_ddd              - The main function to do a DDD conversion

#define USED_PERMANENT 1
#define USED_TEMPORARY 2

/* dcodeddd.c */
void ddd_generate_model_action_list(unsigned char *data);
void ddd_remove_data(unsigned char *data_block_start, unsigned int data_size, unsigned char *data_to_remove, unsigned short bytes_to_remove);
void ddd_simplify_two_vertices(unsigned short *num_vertex_spot, unsigned short *num_tex_vertex_spot, unsigned short vertex_to_keep, unsigned short vertex_to_remove, unsigned short tex_vertex_to_keep, unsigned short tex_vertex_to_remove, unsigned char *data, unsigned int data_size, unsigned char num_texture);
unsigned char ddd_simplify_once(unsigned short *num_vertex_spot, unsigned short *num_tex_vertex_spot, unsigned char *data, unsigned int data_size, unsigned char num_texture);
void ddd_simplify_geometry(unsigned short *num_vertex_spot, unsigned short *num_tex_vertex_spot, unsigned char *data, unsigned char percent, unsigned int data_size, unsigned char num_texture);
void ddd_continue_simplify(unsigned short *num_vertex_spot, unsigned short *num_tex_vertex_spot, unsigned char *data, unsigned char percent, unsigned int data_size, unsigned char num_texture, unsigned short num_vertex);
void add_cartoon_line(unsigned short vertex_a, unsigned short vertex_b, unsigned short check, unsigned char force_line, unsigned short *cartoon_data);
void remove_cartoon_lines(unsigned short *cartoon_data);
unsigned char *ddd_create_strip(unsigned char *helper_data, unsigned char *new_data, unsigned short main_triangle, unsigned short num_triangle);
void ddd_strip_fan_geometry(unsigned short num_vertex, unsigned short num_tex_vertex, unsigned char *old_data, unsigned char *helper_data, unsigned char *new_data, unsigned char num_texture);
void ddd_decode_base_model(unsigned char **olddata_spot, unsigned char **newdata_spot, unsigned char **newindex_spot, unsigned char *newdata_start, unsigned char detail_level, float scale);
void ddd_decode_bone_frame(unsigned char **olddata_spot, unsigned char **newdata_spot, unsigned char **newindex_spot, unsigned char *newdata_start, float scale);
signed char decode_ddd(unsigned char *index, unsigned char *filename);
void ddd_magic_update_thing(unsigned char mask);
#endif
