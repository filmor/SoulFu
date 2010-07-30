#ifndef SOULFU_DISPLAY_H
#define SOULFU_DISPLAY_H

// <ZZ> This file has all the stuff for displaying the screen...  3D card does everything...
//      These are the more general purpose functions, wrappers, and 2D windowing stuff...
//      Render.c has the 3D model rendering stuff...
//  x   display_clear_zbuffer       - Clears the zbuffer
//  x   display_clear_buffers       - Clears the zbuffer and the display
//  x   display_swap                - Swaps the display onto the screen after we've rendered it
//  x   display_viewport            - Tells us where to render on the screen
//  x   display_zbuffer_on          - Turns on zbuffering
//  x   display_zbuffer_off         - Turns off zbuffering
//  x   display_cull_on             - Turns on backface culling
//  x   display_cull_off            - Turns off backface culling
//  x   display_shade_on            - Turns on smooth shading
//  x   display_shade_off           - Turns off smooth shading
//      display_blend_trans         - Turns on transparency style average blending
//      display_blend_light         - Turns on light style additive blending
//      display_blend_off           - Turns off blending
//      display_depth_scene         - Sets up depth buffering range for the main 3D stuff
//      display_depth_overlay       - Sets up depth buffering range for windows
//  x   display_texture_on          - Turns on texturing
//  x   display_texture_off         - Turns off texturing
//  x   display_pick_texture        - Picks the texture to use
//  x   display_start_strip         - Starts a triangle strip
//  x   display_start_fan           - Starts a triangle fan
//  x   display_color               - Sets the color for the next vertex
//      display_texpos              - Sets the texture position for the next vertex
//  x   display_vertex              - Adds a vertex
//  x   display_end                 - Ends a triangle strip or fan
//      display_slider              - Draws a horizontal or vertical slider bar...
//      display_highlight           - Draws a white rectangle for selection lists...
//      display_window
//      display_image               - Draws a 2D textured image
//      display_font
//      display_kanji
//      display_string
//      display_mini_list
//      display_input
//      display_emacs
//  x   blurry_alpha_helper         - Helper for display_load_texture
//  x   display_load_texture        - Loads an RGB file onto the graphics card as a texture
//  x   display_load_all_textures   - Loads all of the textures onto the card
//  x   display_setup               - Sets up all of the mandatory silly stuff for SDL/GL/whatever else
//      display_render              - The main function for rendering a scene
//      display_start_fade          - Starts to fade out the screen (circle effect)
//      display_fade                - Draws the fade effect
//      display_look_at             - Sets up the camera matrix...

#define ZNEAR 0.625f                     // The near frustum plane
#define ALPHA_TOLERANCE 64              // Tolerance for color key transparency
#define ALPHA_BLUR 75                   // Amount to fade neighbors in '=' prefixed files
#define ALPHA_MIN  0                    // Minimum alpha allowed for neighbors

#define FADE_IN             -4          //
#define FADE_OUT            4           //
#define FADE_TYPE_NONE      0           // No fade
#define FADE_TYPE_CIRCLE    1           // Circle fade
#define FADE_TYPE_WARNING   2           // Warning flash
#define FADE_TYPE_FULL      3           // Fullscreen fade
#define CIRCLE_QUARTER 8                // Points in a quarter circle
#define CIRCLE_POINTS (CIRCLE_QUARTER*4)// Number of points in the circle fade effect
#define CIRCLE_TOTAL_POINTS (CIRCLE_POINTS + 5)  // 4 for corners, 1 redundant
#define WARNING_SIZE 20.0f              //

extern unsigned int texture_ascii;
extern unsigned int texture_bookfnt;
extern float window_camera_matrix[16];
extern float screen_frustum_x;
extern float screen_frustum_y;
extern float camera_to_distance;
extern int camera_rotation_add_xy[2];
extern unsigned char display_full_screen;
extern float camera_fore_xyz[3];               // The forward vector of the camera
extern float camera_side_xyz[3];
extern float camera_xyz[3];
extern float map_side_xy[2];
#endif
