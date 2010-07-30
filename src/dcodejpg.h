#ifndef SOULFU_DCODEJPG_H
#define SOULFU_DCODEJPG_H

#define TEXTURE_NO_ALPHA       0    // Normal texture
#define TEXTURE_ALPHA          1    // Color keyed transparency, Prefix '-'
#define TEXTURE_SUPER_ALPHA    2    // Color keyed with edge blur, Prefix '='
#define TEXTURE_DONT_LOAD      3    // Not supposed to load this onto card, Prefix '+'
#define TEXTURE_ON_CARD        4    // Has been loaded onto the card

// <ZZ> This file contains functions to convert JPEG files to RGB
//  **  my_error_mgr            - A structure for the JPEG thing's error handling
//                                (ignore)
//  **  my_error_exit           - A function for the JPEG thing's error handling
//                                (ignore)
//  **  put_scanline_someplace  - Fills in the RGB file with data, Runs line by line
//                                (helper)
//  **  decode_jpg              - The main function to do a JPG conversion

signed char decode_jpg(unsigned char* index, unsigned char* filename);

#endif
