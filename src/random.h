#ifndef SOULFU_RANDOM_H
#define SOULFU_RANDOM_H

#include <stdlib.h>

int random_setup (int seed);

unsigned char random_number();

unsigned short random_dice(unsigned char number, unsigned short sides);

unsigned char* random_name(unsigned char* filedata);

#endif
