#define EXECUTABLE_VERSION   "1.5 NICEWARE"

#include "soulfu.h"
#include "gameseed.h"
#include "datafile.h"
#include "dcodesrc.h"
#include "object.h"
#include "input.h"
#include "display.h"
#include "common.h"
#include "map.h"
#include "runsrc.h"

#include <string.h>
#include <stdlib.h>

unsigned short onscreen_draw_count;

//-----------------------------------------------------------------------------------------------
void main_loop(void)
{
    int i, j;
    float x, y, brx, bry;
    char* alt_text;
    unsigned char pause_active = FALSE;


    log_message("INFO:   Starting main loop");
    display_zbuffer_on();
    display_cull_on();


	// Loop as long as escape isn't pressed
    main_game_frame = 0;
    main_video_frame = 0;
    main_video_frame_skipped = 0;
    quitgame=FALSE;
	while(quitgame == FALSE)
    {
        main_timer_start();     // Game timer...


        // Draw the world, if we're actually playing the game...
        color_temp[0] = 0;  color_temp[1] = 0;  color_temp[2] = 0;
        if(play_game_active)
        {
            if(map_current_room < MAX_MAP_ROOM)
            {
                if(map_room_data[map_current_room][13] & MAP_ROOM_FLAG_OUTSIDE)
                {
                    color_temp[0] = 64;  color_temp[1] = 64;  color_temp[2] = 255;
                }
            }
            display_clear_buffers();



            if(key_pressed[SDLK_F9])
            {
                pause_active=!pause_active;
                DEBUG_STRING[0] = 0;
            }
// !!!BAD!!!
// !!!BAD!!!
// !!!BAD!!!
//            #ifdef DEVTOOL
//                if(key_pressed[SDLK_SPACE])
//                {
//                    if(network_on)
//                    {
//                        network_send_room_update();
//                    }
//                }
//                if(key_pressed[SDLK_F8])
//                {
//                    log_message("INFO:   Dumping all particle information...");
//                    repeat(i, MAX_PARTICLE)
//                    {
//                        if(main_particle_on[i])
//                        {
//                            obj_get_script_name(main_particle_script_start[i], DEBUG_STRING);
//                            log_message("INFO:     Particle %d is of type %s.RUN", i, DEBUG_STRING);
//                            DEBUG_STRING[0] = 0;
//                        }
//                        else
//                        {
//                            log_message("INFO:     Particle %d is off", i);
//                        }
//                    }
//                }
//            #endif
// !!!BAD!!!
// !!!BAD!!!
// !!!BAD!!!

            // Move characters around...
            main_frame_skip = 0;
            if(main_timer_length >= 16)
            {
                // Only do up to 4 updates per drawn frame to ensure that the game doesn' get totally
                // hosed from being too slow to update (and constantly has more and more frames
                // to catch up on...)
                while(main_timer_length >= 16 && main_frame_skip < 4)
                {
                    character_local_player_control();
                    if(!pause_active)
                    {
                        if(global_luck_timer > 0)
                        {
                            global_luck_timer--;
                        }
                        character_update_all();
                        character_collide_all();
                        particle_update_all();
                        character_bone_frame_all();
                        character_refresh_items_all();
                    }
                    else
                    {
                        character_bone_frame_all();
                    }


                    main_timer_length-=16;
                    main_game_frame++;
                    main_frame_skip++;
                }
            }
            else
            {
                character_local_player_control();
                character_bone_frame_all();
            }



onscreen_draw_count = 0;


            // Figure out the camera position...
            display_camera_position(main_frame_skip, 0.95f, 0.99f);


            // Rotate the camera...
            display_look_at(camera_xyz, target_xyz);
            // Remember camera facing for automap...  Use side, because fore can look down and
            // that screws up the scaling...
            map_side_xy[0] = camera_side_xyz[0];
            map_side_xy[1] = camera_side_xyz[1];



            // Draw the world scene...
            drawing_world = TRUE;
            room_draw(roombuffer);
            if(volumetric_shadows_on)
            {
                volume_shadow_draw_all();
            }
            else
            {
                character_shadow_draw_all();
            }
            character_draw_all_prime();
            character_draw_all(FALSE, FALSE);
            if(room_water_type == WATER_TYPE_WATER)
            {
                particle_draw_below_water();
            }
            water_draw_room(roombuffer);
            character_draw_all(TRUE, FALSE);
            if(room_water_type == WATER_TYPE_WATER)
            {
                particle_draw_above_water();
            }
            else
            {
                particle_draw_below_water();
                particle_draw_above_water();
            }
            character_draw_all(FALSE, TRUE);






//sprintf(DEBUG_STRING, "%d chars drawn", onscreen_draw_count);


            // Draw axis arrows...
//            #ifdef DEVTOOL
//                if(debug_active)
//                {
//                    display_blend_off();
//                    display_texture_off();
//                    render_axis();
//                    display_marker(blue, 0.0f, 0.0f, 6.0f, 1.0f);  // 6ft height marker...
//                    display_marker(green, 0.0f, 6.0f, 0.1f, 1.0f);  // Y axis marker
//                    display_marker(red, 6.0f, 0.0f, 0.1f, 1.0f);  // X axis marker
//                }
//            #endif
        }
        else
        {
            // Game isn't active, but still run our timers so the window scripts
            // work right...
            pause_active = FALSE;
            display_clear_buffers();
            character_bone_frame_clear();
            main_frame_skip = 0;
            while(main_timer_length >= 16)
            {
                main_frame_skip++;
                main_timer_length-=16;
            }
        }
        main_video_frame_skipped+=main_frame_skip;



        // Draw window stuff...
        drawing_world = FALSE;
        glLoadMatrixf(window_camera_matrix);
        display_zbuffer_off();
        display_texture_on();
        display_blend_trans();
        display_cull_on();


        promotion_count = 0;
        repeat(i, main_used_window_count)
        {
            #ifdef DEVTOOL
                if(i < 0)
                {
                    log_message("ERROR:  ");
                    log_message("ERROR:  ");
                    log_message("ERROR:  Window Poof Count, i == %d", i);
                    log_message("ERROR:  ");
                    log_message("ERROR:  ");
                    exit(0);
                }
            #endif
            j = main_window_order[i];
            main_window_poof_count = 0;
            window3d_order = MAX_WINDOW - ((unsigned char) i);
            fast_run_script(main_window_script_start[j], FAST_FUNCTION_REFRESH, main_window_data[j]);
            #ifdef DEVTOOL
                if(current_object_data != main_window_data[j])
                {
                    sprintf(DEBUG_STRING, "Window current object corrupted...");
                    log_message("ERROR:  Window current object corrupted...");
                }
            #endif
            i-=main_window_poof_count;
        }
        repeat(i, promotion_count)
        {
            promote_window(promotion_buffer[i]);
        }






        // Handle funky enchantment targeting clicks...
        if(enchant_cursor_active)
        {
            // Constantly check for dead character...
            enchant_cursor_active = FALSE;
            if(enchant_cursor_character < MAX_CHARACTER)
            {
                if(main_character_on[enchant_cursor_character])
                {
                    if(main_character_data[enchant_cursor_character][82] > 0)
                    {
                        enchant_cursor_active = TRUE;
                    }
                }
            }
        }
        if(mouse_draw && enchant_cursor_active)
        {
            // Is player still alive?
            if(mouse_pressed[BUTTON0])
            {
                // Was it clicked on a character?
                if(mouse_current_object==NULL && mouse_current_item < MAX_CHARACTER)
                {
                    // Figger out who the target is...
                    enchant_cursor_target = mouse_current_item;
                    enchant_cursor_target_item = 0;  // Means character itself...
                    call_enchantment_function();
                    if(return_int)
                    {
                        // Revert to normal cursor if EnchantUsage() returns TRUE
                        enchant_cursor_active = FALSE;
                    }
                }
            }
        }



        // Handle input changes...
        input_update();


        // Draw the selection box
        #ifdef DEVTOOL
            selection_close_type = 0;
            if(select_pick_on && mouse_down[BUTTON0] == 0)
            {
                select_pick_on = FALSE;
            }
            if(select_move_on && mouse_down[BUTTON0] == 0)
            {
                select_move_on = FALSE;
                selection_close_type = BORDER_MOVE;
            }
            if(selection_box_on)
            {
                // It's on...
                render_box();

                // Close if button released
                if(mouse_down[BUTTON0]==0)
                {
                    selection_box_on = FALSE;
                    selection_close_type = BORDER_SELECT;
                    // Ensure that top left is less than bottom right...
                    if(selection_box_tl[0] > selection_box_br[0])
                    {
                        x = selection_box_tl[0];
                        selection_box_tl[0] = selection_box_br[0];
                        selection_box_br[0] = x;
                    }
                    if(selection_box_tl[1] > selection_box_br[1])
                    {
                        y = selection_box_tl[1];
                        selection_box_tl[1] = selection_box_br[1];
                        selection_box_br[1] = y;
                    }

                }
            }
        #endif





        // Draw the cursor...
        display_pick_texture(texture_ascii);
        if(mouse_idle_timer > 1800 && mouse_alpha > 0)
        {
            mouse_alpha--;
        }
        if(mouse_idle_timer < 30 && mouse_alpha < 255)
        {
            mouse_alpha++;
            mouse_alpha = (mouse_alpha + mouse_alpha + mouse_alpha + 255)>>2;
        }
        color_temp[0] = 255;  color_temp[1] = 255;  color_temp[2] = 255;  color_temp[3] = mouse_alpha;
        display_color_alpha(color_temp);
        if(mouse_draw)
        {
            x = mouse_x;
            y = mouse_y;

            // Draw the cursor
            if(enchant_cursor_active)
            {
                display_string(cursor_target, x-7.5f, y-7.5f, 15);
            }
            else
            {
                if(mouse_down[BUTTON0])
                {
                    // Draw a click cursor...
                    display_string(cursor_click, x, y, 15);
                }
                else
                {
                    // Draw a normal cursor...
                    display_string(cursor_normal, x, y, 15);
                }
            }


            // Draw the alternate text...
            if(mouse_text[0])
            {
                x+=12.0f;
                y+=12.0f;
                alt_text = mouse_text;
                brx = x+script_window_scale*(strlen(alt_text)+1);
                bry = y+(script_window_scale*1.2f);
                if(brx > 400.0f)
                {
                    x = 400.0f - (brx-x);
                    brx = 400.0f;
                }
                display_color_alpha(whiter);
                display_mouse_text_box(x, y, brx, bry, texture_winalt);
                display_color(white);
                display_pick_texture(texture_ascii);
                display_string(alt_text, x+(script_window_scale*.5f), y+(script_window_scale*0.1f), script_window_scale);
                if(mouse_text_timer == 0)
                {
                    mouse_text[0] = 0;
                }
            }
        }


        // Draw the debug string
        display_color(white);
        if(compiler_error)
        {
//            display_string("Compiler error...  See logfile.txt", 0, 290.0f, 10.0f);
        }
        else
        {
            #ifdef DEVTOOL
                if(key_down[SDLK_F11])
                {
                    sprintf(DEBUG_STRING, "Obj == %u, Item == %u", mouse_last_object, mouse_last_item);
                }
                if(!pause_active)
                {
                    display_string(DEBUG_STRING, 0, 290.0f, 10.0f);
                }
            #endif
        }
//#ifndef DEVTOOL
//        display_string("DEVTOOL OFF", 290.0f, 290.0f, 10.0f);
//#endif

        if(pause_active)
        {
            if(play_game_active)
            {
                display_string("-Paused-", 140.0, 15.0f, 15.0f);
            }
        }

#ifdef DEVTOOL
//        if(!pause_active)
//        {
//            if(play_game_active)
//            {
//                display_string("Play", 0.0, 0.0f, 10.0f);
//            }
//            if(main_game_active)
//            {
//                display_string("Main", 50.0, 0.0f, 10.0f);
//            }
//        }
#endif



        // Do fade out effect...
        display_texture_off();
        display_blend_off();
        #ifdef DEVTOOL
            #ifdef SHOW_JOYSTICK_POSITIONS
                repeat(i, MAX_LOCAL_PLAYER)
                {
                    x = (400.0f/(MAX_LOCAL_PLAYER+1)) * (i+1);
                    y = 275.0f;

                    display_color(white);
                    display_start_line();
                        display_vertex_xy(x-2.0f, y);
                        display_vertex_xy(x+2.0f, y);
                    display_end();
                    display_start_line();
                        display_vertex_xy(x, y-2.0f);
                        display_vertex_xy(x, y+2.0f);
                    display_end();

                    display_color(instrument_color[i]);
                    display_start_line();
                        display_vertex_xy(x, y);
                        x+=player_device_xy[i][0]*25.0f;
                        y+=player_device_xy[i][1]*25.0f;
                        display_vertex_xy(x, y);
                    display_end();
                }
            #endif
        #endif
        display_shade_on();
        display_fade();
        display_shade_off();
        display_zbuffer_on();



        // Display everything once it's drawn...
		display_swap();


        // Reset our input...  Do once per display
        input_reset_window_key_pressed();
        input_read();
        fill_music();
        fill_sound_buffer();
// !!!BAD!!!
// !!!BAD!!!
// !!!BAD!!!
//        network_listen();
// !!!BAD!!!
// !!!BAD!!!
// !!!BAD!!!


        // Handle camera controls...
        input_camera_controls();



        main_video_frame++;
        #ifdef DEVTOOL
            if(key_pressed[SDLK_F10])
            {
                debug_active = (debug_active+1)&1;
            }
//            if(key_pressed[SDLK_F4])
//            {
//                display_start_fade(FADE_TYPE_FULL, FADE_OUT, 0, 0, black);
//            }
//            if(key_pressed[SDLK_F3])
//            {
//                display_start_fade(FADE_TYPE_WARNING, FADE_OUT, 0, 0, cyan);
//            }
//            if(key_pressed[SDLK_F2])
//            {
//                display_start_fade(FADE_TYPE_CIRCLE, FADE_OUT, 200.0f, 150.0f, black);
//            }
        #endif
        main_timer_end();
    }
}

//-----------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    int i;
    unsigned char* script;
    unsigned char* config;
    unsigned char bit_depth;
    unsigned char z_depth;    
    unsigned char full_screen;
    unsigned char screen_size;
    unsigned char* data;


    open_logfile();
    log_message("INFO:   ------------------------------------------");
    if(!get_mainbuffer()) { log_message("ERROR:  get_mainbuffer() failed");  exit(1); }
    if(!sdf_load()) { log_message("ERROR:  sdf_load() failed"); exit(1); }
// !!!BAD!!!
// !!!BAD!!!
// !!!BAD!!!
//    network_setup();
// !!!BAD!!!
// !!!BAD!!!
// !!!BAD!!!
    display_kanji_setup();
    data = sdf_find_filetype("VERSION", SDF_FILE_IS_DAT);
    if(data)
    {
        data = (unsigned char*) sdf_read_unsigned_int(data);
    }
    log_message("INFO:   SoulFu version %s", EXECUTABLE_VERSION);
    generate_game_seed();
    log_message("INFO:   ------------------------------------------");


    // Make sure the game is turned off...
    play_game_active = FALSE;
    main_game_active = FALSE;


    // Try to not break it too bad...
    #ifdef DEVTOOL
        sdf_save("backup.sdf");
    #endif


    // Load the config file from disk, if there is one...
    sdf_add_file("CONFIG.DAT");


    // Read the display settings from the config file...
    config = sdf_find_filetype("CONFIG", SDF_FILE_IS_DAT);
    if(config)
    {
        config = (unsigned char*) sdf_read_unsigned_int(config);
        screen_size = (*(config+68)) & (MAX_SCREEN_SIZES-1);
        bit_depth = *(config+69);
        z_depth = *(config+70);
        volumetric_shadows_on = (*(config+71))&1;
        full_screen = *(config+72);
        mip_map_active = (*(config+98));
        fast_and_ugly_active = (*(config+101));
        log_message("INFO:   Config file read okay...");
        if(!display_setup(screen_sizes_xy[screen_size][0], screen_sizes_xy[screen_size][1], bit_depth, z_depth, full_screen)) { log_message("ERROR:  display_setup() failed");  exit(1); }
    }
    else
    {
        log_message("ERROR:  No config file present");
        exit(1);
    }


    // Draw a please wait type of thing onscreen...
    display_loadin(0.0f);


//    sdf_add_file("DEFINE.TXT");  // !!!BAD!!!  Allow me to constantly update the global defines

    sine_table_setup();
    if(!random_setup(game_seed)) { log_message("ERROR:  random_setup() failed");  exit(1); }
    if(!src_define_setup()) { log_message("ERROR:  src_define_setup() failed"); exit(1); }


#ifdef DEVTOOL
//    sdf_delete_all_files(SDF_FILE_IS_RUN, NULL);
    sdf_list_all_files(SDF_FILE_IS_SRC, NULL, FALSE);
    sdf_list_all_files(SDF_FILE_IS_SRF, NULL, FALSE);
    sdf_list_all_files(SDF_FILE_IS_DDD, NULL, FALSE);
    sdf_list_all_files(SDF_FILE_IS_JPG, NULL, FALSE);
    sdf_list_all_files(SDF_FILE_IS_PCX, NULL, FALSE);
    sdf_list_all_files(SDF_FILE_IS_OGG, NULL, FALSE);
    sdf_list_all_files(SDF_FILE_IS_MUS, NULL, FALSE);
//    sdf_list_all_files(SDF_FILE_IS_SRC, NULL, TRUE);
//    sdf_list_all_files(SDF_FILE_IS_OGG, NULL, TRUE);
#endif

    // Decode all of the files...
    sdf_decode(SDF_ALL, TRUE);


    ddd_magic_update_thing(SDF_ALL);
    display_loadin(0.50f);
    render_crunch_all(SDF_ALL);
    display_loadin(0.60f);
    sdf_flag_clear(SDF_FLAG_WAS_UPDATED);

    // Compile all of the script files
    message_reset();
    message_setup();
    compiler_error = FALSE;
//    #ifdef DEVTOOL
//        // RUN files should be saved in the datafile, so these two parts shouldn't be needed
//        // most of the time...
//        src_stage_compile(SRC_HEADERIZE, SDF_ALL);
//        display_loadin(0.70f);
//        src_stage_compile(SRC_COMPILERIZE, SDF_ALL);
//        display_loadin(0.80f);
//    #endif
    while(src_stage_compile(SRC_FUNCTIONIZE, SDF_ALL) == FALSE);  // Keep linking until all of the errors go away...
    display_loadin(0.90f);


    damage_setup();
    input_setup();
    sound_setup();
    page_setup();
    render_shadow_setup();
    item_type_setup();
    water_setup();
    water_drown_delay_setup();
    character_action_setup();
    display_load_all_textures();
    display_loadin(1.00f);



    // Flag certain files to not be updated...  (This is outdated sorta stuff...  No longer do FTP stuff...)
    sdf_flag_set("RANDOM.DAT", SDF_FLAG_NO_UPDATE);
    sdf_flag_set("CONFIG.DAT", SDF_FLAG_NO_UPDATE);





    // Start by spawning the first window object...  Main menu/Title...
    obj_setup();
    promotion_count = 0;
    script = sdf_find_filetype("WSTART", SDF_FILE_IS_RUN);
    if(script)
    {
        script = (unsigned char*) sdf_read_unsigned_int(script);
        obj_spawn(WINDOW, 200.0f, 150.0f, 0, script, MAX_WINDOW);
        repeat(i, promotion_count)
        {
            promote_window(promotion_buffer[i]);
        }
    }


// !!!BAD!!!
// !!!BAD!!!  SUPER BAD!!!  Used to get rid of all script texts for final release...
// !!!BAD!!!
//    sdf_delete_all_files(SDF_FILE_IS_SRC, NULL);
// !!!BAD!!!
// !!!BAD!!!
// !!!BAD!!!



    // Do the main loop...
    main_loop();


    // Export the config file to disk, so we don't need to save the whole datafile
    sdf_export_file("CONFIG.DAT");



    return 0;
}

//-----------------------------------------------------------------------------------------------
