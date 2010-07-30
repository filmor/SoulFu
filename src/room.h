#ifndef SOULFU_ROOM_H
#define SOULFU_ROOM_H

// <ZZ> This file contains functions for drawing & editing & otherwise working with
//      the new room format...

#define EXTERIOR_VERTEX             0
#define EXTERIOR_TEX_VERTEX         1
#define EXTERIOR_TRIANGLE           2
extern unsigned short global_num_vertex;
extern unsigned short global_num_tex_vertex;
extern unsigned short global_num_triangle;
extern unsigned short global_room_active_group;

#define ROOM_CEILING_Z  20.0f
#define ROOM_CEILING_BUMP_Z 18.0f
#define ROOM_HEIGHTMAP_Z  40.0f
#define ROOM_HEIGHTMAP_SCALE 0.00244140625f // ROOM_HEIGHTMAP_Z / 16384...  for the heightmap return function...
#define ROOM_HEIGHTMAP_SIZE 1024            // Heightmap is 2048x2048, 16 values per square foot
#define ROOM_HEIGHTMAP_PRECISION 4.0f       // Each foot of room is sampled this many times (square for a square foot)
#define ROOM_HEIGHTMAP_BIAS      0.125f     // Should be 0.5/precision...  Used to help out with rounding...
#define ROOM_HEIGHTMAP_BORDER 64            // Size of border on any side...
#define ROOM_PIT_HIGH_LEVEL -14.0f
#define ROOM_PIT_HURT_LEVEL -28.0f
#define ROOM_PIT_LOW_LEVEL -30.0f

#define ONE_OVER_512 0.001953125f
#define ONE_OVER_256 0.00390625f
#define MAX_ROOM_TEXTURE 32

#define WALL_TEXTURE_SCALE   0.050f   // Wall texture repeats every 20ft...
//#define WALL_TEXTURE_SCALE   0.0625f   // Wall texture repeats every 16ft...
#define MINIMUM_WALL_LENGTH  0.2500f    // Don't allow short walls...


// Exterior wall flags...
#define ROOM_WALL_FLAG_LOW_NORMAL_WALL   0
#define ROOM_WALL_FLAG_LOW_NO_TRIM_WALL  1
#define ROOM_WALL_FLAG_LOW_NO_WALL       2
#define ROOM_WALL_FLAG_LOW_DOOR          3
#define ROOM_WALL_FLAG_LOW_SHUTTER       4
#define ROOM_WALL_FLAG_LOW_PASSAGE       5
#define ROOM_WALL_FLAG_LOW_BOSS_DOOR     6
#define ROOM_WALL_FLAG_LOW_CRACKED_DOOR  7
#define ROOM_WALL_FLAG_LOW_SECRET_DOOR   8

// Room texture flags...
#define ROOM_TEXTURE_FLAG_NOLINE     1
#define ROOM_TEXTURE_FLAG_NOHEIGHT   2
#define ROOM_TEXTURE_FLAG_FLOORTEX   4
#define ROOM_TEXTURE_FLAG_NODRAW     8
#define ROOM_TEXTURE_FLAG_ALPHATRANS 16
#define ROOM_TEXTURE_FLAG_NOSHADOW   32
#define ROOM_TEXTURE_FLAG_PAPERDOLL  64
#define ROOM_TEXTURE_FLAG_SMOOTH     128

/* room.c */
void room_weldable_vertex_clear(void);
void room_weldable_vertex_add(unsigned short vertex, unsigned short segment, float *intersection_info);
void room_weldable_vertex_remove(unsigned short vertex);
void intersect_xy_lines(float *info_a, float *info_b, float *write_xy);
unsigned char *room_ddd_plop_function(unsigned char function, unsigned char *write, unsigned char *ddd_file_start, unsigned char base_model, unsigned char *texture_list, float *position_xyz, float *fore_xy, unsigned char pillar_stretch);
unsigned char *room_plop_all_function(unsigned char function, unsigned char *write, unsigned char *data, unsigned char *srf_file, unsigned char *ddd_wall_door_file, unsigned short object_group, unsigned short rotation);
unsigned char *room_wall_segment_function(unsigned char function, unsigned char *srf_file, unsigned char *write, unsigned char *vertex_data, unsigned char *tex_vertex_data, unsigned short segment, unsigned short num_segment, unsigned short vertex, unsigned short last_vertex, unsigned char *ddd_wall_door_file, unsigned char base_model, float wall_texture_offset, float wall_texture_scale, unsigned short rotation);
unsigned char *room_exterior_wall_function(unsigned char function, unsigned char *srf_file, unsigned char *write, unsigned char *vertex_data, unsigned char *tex_vertex_data, unsigned char *ddd_wall_door_file, unsigned char *door_wall_list, unsigned short rotation);
float room_heightmap_height_slow(unsigned char *data, float x, float y);
void room_heightmap_clear(signed short *heightmap_data);
void room_heightmap_triangle(signed short *heightmap_data, float *fa_xyz, float *fb_xyz, float *fc_xyz);
float room_srf_waypoint_distance(unsigned char *waypoint_data, unsigned char from_waypoint, unsigned char to_waypoint);
void room_srf_find_goto_waypoint(unsigned char *waypoint_data, unsigned char *waypoint_line_data, unsigned char initial_waypoint);
void room_setup_lighting(unsigned char *data, float *light_xyz, float ambient);
void room_set_texture_data(unsigned char *texture_data, unsigned char texture, unsigned int hardware_texture, unsigned char flags);
void room_spawn_all(unsigned char *srf_file, unsigned short rotation, unsigned char *door_wall_list, unsigned char *object_defeated_list, unsigned char difficulty, unsigned short seed, unsigned short object_group);
void room_edge_line_add(unsigned char *edge_line_data, unsigned short vertex_a, unsigned short vertex_b, unsigned short check_vertex);
void room_restock_monsters(unsigned char *srf_file, unsigned char *object_defeated_list, unsigned char difficulty, unsigned short seed, unsigned short object_group);
unsigned char room_uncompress(unsigned char *srf_file, unsigned char *destination_buffer, unsigned char *ddd_wall_door_file, unsigned short rotation, unsigned char *door_wall_list, unsigned char *object_defeated_list, unsigned char difficulty, unsigned short seed, unsigned short object_group);
void room_get_point_xyz(float percent_x, float percent_y, float *final_x, float *final_y, float *final_z, float scale, unsigned char z_finder_mode, unsigned char snap_mode);
unsigned char room_find_wall_center(unsigned char *data, unsigned short rotation, unsigned short wall, float *center_xyz, float *offset_xyz, float normal_add);
unsigned char room_find_best_wall(unsigned char *data, unsigned char allow_bottom_doors, unsigned short rotation, float *vector_xy, unsigned char *walls_to_not_use);
void room_draw_srf(float x, float y, float z, unsigned char *data, unsigned char *color_rgb, unsigned short rotation, unsigned char mode);
void room_draw(unsigned char *data);
unsigned char room_findpath(unsigned char *data, float *from_xy, float *to_xy, float *write_xy, unsigned char *character_data);

#endif
