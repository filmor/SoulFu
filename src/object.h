#ifndef SOULFU_OBJECT_H
#define SOULFU_OBJECT_H

// <ZZ> This file contains functions related to characters, particles, and windows...
//      obj_setup           - Gets ready to spawn stuff
//      obj_spawn           - Creates a new object of the desired type
//      obj_reset_property  - Gets ready to use properties
//      obj_add_property    - Registers a property name...  for window.x type stuff in script
//      obj_get_property    - Searches for a property name...  Returns index or -1 if not found
//      obj_get_script_name - Helper for the recompile functions
//      obj_recompile_start - Figures out which script each object is attached to
//      obj_recompile_end   - Gets the new script address for each object

#include "soulfu.h"

#define CHARACTER 0         // Object types...
#define PARTICLE 1          //
#define WINDOW 2            //

#define CHARACTER_SIZE 616  // The number of bytes for a character's data
#define PARTICLE_SIZE 88    // The number of bytes for a particle's data
#define MAX_WINDOW 16       // The maximum number of windows a machine can have open
#define WINDOW_SIZE 616     // The number of bytes for a window's data

// Must be 256...  Or else script props need to have 2 byte extensions...
#define MAX_PROPERTY 256
extern int obj_num_property;
extern char property_type[MAX_PROPERTY];
extern unsigned char* main_window_script_start[MAX_WINDOW];
extern unsigned char main_window_data[MAX_WINDOW][WINDOW_SIZE];
extern unsigned short main_unused_particle_count;
extern unsigned char main_character_data[MAX_CHARACTER][CHARACTER_SIZE]; 
extern unsigned char main_character_on[MAX_CHARACTER];
extern unsigned char* main_character_script_start[MAX_CHARACTER];
extern unsigned short main_used_window_count;
extern unsigned short main_window_order[MAX_WINDOW];

extern unsigned char  main_character_on[MAX_CHARACTER];
extern unsigned char  main_character_reserve_on[MAX_CHARACTER];
extern unsigned char  main_particle_on[MAX_PARTICLE];
extern unsigned short main_unused_window[MAX_WINDOW];
extern unsigned short main_window_order[MAX_WINDOW];

extern unsigned short main_unused_character_count;
extern unsigned short main_unused_particle_count;
extern unsigned short main_unused_window_count;
extern unsigned short main_used_window_count;
extern unsigned short main_window_poof_count;

extern unsigned char main_particle_data[MAX_PARTICLE][PARTICLE_SIZE];

extern unsigned char* main_character_script_start[MAX_CHARACTER];
extern unsigned char* main_particle_script_start[MAX_PARTICLE];
extern unsigned char* main_window_script_start[MAX_WINDOW];

extern char main_character_script_name[MAX_CHARACTER][8];
extern char main_particle_script_name[MAX_PARTICLE][8];
extern char main_window_script_name[MAX_WINDOW][8];

extern unsigned short global_spawn_owner;
extern unsigned short global_spawn_target;
extern unsigned char global_spawn_team;
extern unsigned char global_spawn_subtype;
extern unsigned char global_spawn_class;

#define MAX_PROPERTY 256
extern unsigned short property_offset[MAX_PROPERTY];

extern unsigned short promotion_buffer[MAX_WINDOW];
extern unsigned short promotion_count;

void obj_setup(void);
void obj_get_script_name(unsigned char *file_start, unsigned char *file_name);
unsigned char *obj_spawn(unsigned char type, float x, float y, float z, unsigned char *script_file_start, unsigned short force_index);
void obj_destroy(unsigned char *object_data);
void obj_poof_all(unsigned char type);
void promote_window(int window);
void obj_reset_property(void);
void obj_add_property(char *tag, char type, char *offset);
int obj_get_property(char *token);
void obj_recompile_start(void);
void obj_recompile_end(void);

#endif
