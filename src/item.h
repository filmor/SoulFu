#ifndef SOULFU_ITEM_H
#define SOULFU_ITEM_H

// <ZZ> This file contains functions related to player inventory & item registry...

#define MAX_ITEM_TYPE 256
extern unsigned short global_item_index;
extern unsigned char  global_item_bone_name;

extern unsigned char* item_type_script[MAX_ITEM_TYPE];
extern unsigned char* item_type_icon[MAX_ITEM_TYPE];
extern unsigned char* item_type_overlay[MAX_ITEM_TYPE];
extern signed short   item_type_price[MAX_ITEM_TYPE];
extern unsigned short item_type_flags[MAX_ITEM_TYPE];
extern unsigned char  item_type_str[MAX_ITEM_TYPE];
extern unsigned char  item_type_dex[MAX_ITEM_TYPE];
extern unsigned char  item_type_int[MAX_ITEM_TYPE];
extern unsigned char  item_type_mana[MAX_ITEM_TYPE];
extern unsigned char  item_type_ammo[MAX_ITEM_TYPE];

extern float weapon_refresh_xyz[3];
extern unsigned short weapon_setup_grip;

/* item.c */
void item_type_setup(void);
unsigned char item_get_type_name(unsigned short item_type);
unsigned char item_find_random_xyz(unsigned short character_index, unsigned char character_bone_name);
#endif
