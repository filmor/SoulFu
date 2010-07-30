#ifndef SOULFU_PARTICLE_H
#define SOULFU_PARTICLE_H

// <ZZ> This file contains functions for particles...

/* particle.c */
unsigned char particle_attach_to_character(unsigned short particle, unsigned short character, unsigned char bone_type);
void particle_draw(unsigned char *particle_data);
void particle_draw_below_water(void);
void particle_draw_above_water(void);
void particle_update_all(void);
#endif
