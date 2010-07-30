#ifndef SOULFU_COMMON_H
#define SOULFU_COMMON_H

extern unsigned char* fourthbuffer;
extern unsigned char* roombuffer;
extern unsigned char* mainbuffer;
extern unsigned char* subbuffer;
extern unsigned char* thirdbuffer;

/* common.c */
void timer_start(void);
void timer_end(void);
void main_timer_start(void);
void main_timer_end(void);
void make_uppercase(char *string);
void free_mainbuffer(void);
signed char get_mainbuffer(void);
int count_indentation(char *string);
void datadump(unsigned char *location, int size, signed char append);
void cross_product(float *A_xyz, float *B_xyz, float *C_xyz);
float vector_length(float *A_xyz);
#endif
