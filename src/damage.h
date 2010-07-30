#ifndef SOULFU_DAMAGE_H
#define SOULFU_DAMAGE_H

#define MAX_DAMAGE_TYPE 7
#define DAMAGE_EDGE      0
#define DAMAGE_BASH      1
#define DAMAGE_ACID      2
#define DAMAGE_FIRE      3
#define DAMAGE_ICE       4
#define DAMAGE_VOLT      5
#define DAMAGE_WOUND     6

extern unsigned char* pnumber_file;
extern unsigned int global_attacker;
extern unsigned short global_attack_spin;
extern unsigned char damage_color_rgb[MAX_DAMAGE_TYPE][3];

/* damage.c */
void damage_setup(void);
void damage_character(unsigned short character, unsigned char damage_type, unsigned short damage_amount, unsigned short wound_amount, unsigned char attacker_team);
#endif
