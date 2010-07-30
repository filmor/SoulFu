#ifndef SOULFU_MAP_H
#define SOULFU_MAP_H

// <ZZ> This file contains stuff for making the map work...
//      map_clear           - Clears the map
//      map_add_room        - Adds a room to the map
//      map_remove_room     - Removes a room from the map

#define MAP_ROOM_FLAG_FOUND       128
#define MAP_ROOM_FLAG_DUAL_LEVEL  64
#define MAP_ROOM_FLAG_TOWN        32
#define MAP_ROOM_FLAG_BOSS        16
#define MAP_ROOM_FLAG_VIRTUE      8
#define MAP_ROOM_FLAG_OUTSIDE     4
#define MAX_MAP_ROOM 4000
#define MAX_AUTOMAP_ROOM 200

extern unsigned short map_last_town_room;
extern float map_room_door_pushback;
extern unsigned char map_room_data[MAX_MAP_ROOM][40];
extern unsigned short map_current_room;
extern unsigned short num_map_room;

extern unsigned char*  map_add_srf_file;
extern float           map_add_x;
extern float           map_add_y;
extern unsigned short  map_add_rotation;
extern unsigned char   map_add_seed;
extern unsigned char   map_add_twset;
extern unsigned char   map_add_level;
extern unsigned char   map_add_flags;
extern unsigned char   map_add_difficulty;
extern unsigned char   map_add_area;
extern unsigned short  map_add_from_room;
extern unsigned char   map_add_multi_connect;


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
