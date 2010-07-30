#ifndef SOULFU_WATER_H
#define SOULFU_WATER_H

// <ZZ> This file has stuff for drawing the water.
//      Done as a multitextured plane with animated textures...
//      water_generate          Creates a batch of animated tga files for the water...

#define WATER_GENERATE_SIZE 64
#define WATER_GENERATORS 256
#define MAX_WATER_FRAME 32

extern unsigned int texture_water[MAX_WATER_FRAME];
extern unsigned int texture_shimmer[MAX_WATER_FRAME];
extern unsigned char water_layers_active;

extern unsigned int texture_sand;
extern unsigned char drown_delay[256];
void water_generate(unsigned short numer_of_frames);

#endif
