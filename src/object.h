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

extern unsigned char main_character_data[MAX_CHARACTER][CHARACTER_SIZE]; 


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
