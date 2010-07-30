#ifndef SOULFU_RUNSRC_H
#define SOULFU_RUNSRC_H

// <ZZ> This file contains functions to run scripts after they've been compiled
//      run_script                  - The main function to run a script

/* runsrc.c */
void call_enchantment_function(void);
void autoaim_helper(float speed_xy, float speed_z, unsigned short spin, unsigned char team, unsigned char dexterity, unsigned short cone, unsigned char height, unsigned char function);
void script_matrix_good_bone(unsigned char bone, unsigned char *data_start, unsigned char *data);
void script_matrix_from_bone(unsigned char bone_name);
signed char run_script(unsigned char *address, unsigned char *file_start, unsigned char num_int_args, signed int *int_arg_stack, unsigned char num_float_args, float *float_arg_stack);
#endif
