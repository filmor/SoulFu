#ifndef SOULFU_MAP_H
#define SOULFU_MAP_H

/* map.c */
void map_clear(void);
unsigned char map_doors_overlap(unsigned short room_a, unsigned char room_a_wall, unsigned short room_b, unsigned char room_b_wall);
unsigned char map_connect_rooms(unsigned short room_a, unsigned short room_b);
unsigned char map_rooms_overlap_elaborate(unsigned char *room_a_srf, float *room_a_xy, unsigned short room_a_rotation, unsigned char *room_b_srf, float *room_b_xy, unsigned short room_b_rotation);
unsigned char map_rooms_overlap(unsigned short room_a, unsigned short room_b);
unsigned char map_add_room(unsigned char *srf_file, float x, float y, unsigned short rotation, unsigned char seed, unsigned char twset, unsigned char level, unsigned char flags, unsigned char difficulty, unsigned char area, unsigned short from_room, unsigned char multi_connect);
void map_remove_room(void);
void map_automap_prime(float centerx, float centery, unsigned char level, float tolerance);
void map_automap_draw(void);
#endif
