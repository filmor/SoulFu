#ifndef SOULFU_ITEM_H
#define SOULFU_ITEM_H

// <ZZ> This file contains functions related to player inventory & item registry...

#define MAX_ITEM_TYPE 256
extern unsigned char* item_type_script[MAX_ITEM_TYPE];
extern unsigned short global_item_index;
extern unsigned char  global_item_bone_name;

/* item.c */
void item_type_setup(void);
unsigned char item_get_type_name(unsigned short item_type);
unsigned char item_find_random_xyz(unsigned short character_index, unsigned char character_bone_name);
#endif
