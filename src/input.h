#ifndef SOULFU_INPUT_H
#define SOULFU_INPUT_H

#include <SDL_keysym.h>
#include "soulfu.h"

#define MAX_KEY SDLK_LAST                       // The number of keys
#define MAX_KEY_BUFFER 256                      // Must be 256
#define MAX_ASCII 128                           // Must be 128
extern int num_joystick;
extern unsigned char mouse_draw;
extern unsigned char key_down[MAX_KEY];                // TRUE if key is held down
extern unsigned char key_pressed[MAX_KEY];             // TRUE if key was just pressed (updated once per timing cycle)
extern unsigned char key_unpressed[MAX_KEY];           // TRUE if key was just released (updated once per timing cycle)
extern unsigned char window_key_pressed[MAX_KEY];      // TRUE if key was just pressed (updated once per display)
extern unsigned char key_buffer[MAX_KEY_BUFFER];       // For reading keyboard strings
extern unsigned char key_buffer_read;                  // FIFO read position
extern unsigned char key_buffer_write;                 // FIFO write position
extern unsigned char key_shift[MAX_ASCII];             // Convert an SDLK_ to ASCII caps
extern unsigned short last_key_pressed;            // The sdlk value of the last key pressed...

#define MOUSE_TEXT_TIME 10                      // Number of ticks mouse text should show after taking off of character...
#define MAX_MOUSE_BUTTON 4
#define BUTTON0    0
#define BUTTON1    1
#define BUTTON2    2
#define BUTTON3    3
extern unsigned char mouse_pressed[MAX_MOUSE_BUTTON];
extern unsigned char mouse_unpressed[MAX_MOUSE_BUTTON];
extern unsigned char* mouse_current_object;
extern unsigned short mouse_current_item;
extern unsigned short last_input_item;
extern unsigned char* last_input_object;
extern signed int last_input_cursor_pos;
extern char mouse_text[MAX_STRING_SIZE];
extern unsigned short mouse_last_item;

extern float mouse_x;
extern float mouse_y;
extern float mouse_last_x;
extern float mouse_last_y;
extern unsigned char mouse_down[MAX_MOUSE_BUTTON];
extern unsigned char* mouse_last_object;



#endif
