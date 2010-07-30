#ifndef SOULFU_DATAFILE_H
#define SOULFU_DATAFILE_H

#define SDF_INSTRUMENT      '-' // .OGG files prefixed with this are treated as instruments
#define SDF_NO_ECHO         '=' // .OGG files prefixed with this are not given an echo
#define SDF_ECHO_LOOP       '+' // .OGG files prefixed with this are echoed for loop playback
#define SDF_ECHO            'E' // Not a prefix
#define SDF_HEADER_SIZE     64  // Size of the datafile.sdf header
#define SDF_EXTRA_INDEX  32768  // Allow up to (##/16) files to be sdf_add_file()'d to the index
#define SDF_ALL            255  // For decompressing all files...
#define SDF_FLAG_WAS_UPDATED 128  // Upper 4 bits...
#define SDF_FLAG_NO_UPDATE  64  // Upper 4 bits...
#define SDF_FLAG_C          32  // Upper 4 bits...
#define SDF_FLAG_D          16  // Upper 4 bits...
#define SDF_FILETYPE_COUNT  16  // The number of defined extensions
#define SDF_FILE_IS_UNUSED 0  // Lower 4 bits...  File was deleted (don't save index to disk)
#define SDF_FILE_IS_TXT    1  // Lower 4 bits...  File is a text or random naming file
#define SDF_FILE_IS_JPG    2  // Lower 4 bits...  File is a JPEG texture
#define SDF_FILE_IS_OGG    3  // Lower 4 bits...  File is an Ogg Vorbis sound
#define SDF_FILE_IS_RGB    4  // Lower 4 bits...  File is a decompressed texture (don't save)
#define SDF_FILE_IS_RAW    5  // Lower 4 bits...  File is a decompressed sound (don't save)
#define SDF_FILE_IS_SRF    6  // Lower 4 bits...  File is a Supercool Room Format File
#define SDF_FILE_IS_MUS    7  // Lower 4 bits...  File is a Music file (my format)
#define SDF_FILE_IS_DAT    8  // Lower 4 bits...  File is a Data file (raw data)
#define SDF_FILE_IS_SRC    9  // Lower 4 bits...  File is a script source file
#define SDF_FILE_IS_RUN   10  // Lower 4 bits...  File is a compiled script file
#define SDF_FILE_IS_PCX   11  // Lower 4 bits...  File is a PCX texture
#define SDF_FILE_IS_LAN   12  // Lower 4 bits...  File is a Language text file
#define SDF_FILE_IS_DDD   13  // Lower 4 bits...  File is a 3D model file
#define SDF_FILE_IS_RDY   14  // Lower 4 bits...  File is a 3D model file, ready for use
//  #define SDF_FILE_IS_TIL   15  // Lower 4 bits...  File is a 3D model file, used for tiles
#define TEXT_SIZE 131072
#define OBFUSCATEA ((unsigned char) 97)
#define OBFUSCATEB ((unsigned char) 11)
#define OBFUSCATEC ((unsigned char) 53)
#define OBFUSCATED ((unsigned char) 37)
#ifdef DEVTOOL
    #define EXPORTRDYASDDD
    #define TELL_ME_ABOUT_EXPORT
#endif

extern int sdf_read_line_number;
extern int sdf_read_remaining;
extern int sdf_num_files;
// !!!BAD!!! Noone should see the actual file ...
extern char* sdf_read_file;
extern unsigned char* sdf_index;

/* datafile.c */
float sdf_read_float(unsigned char *location);
unsigned int sdf_read_unsigned_int(unsigned char *location);
void sdf_write_unsigned_int(unsigned char *location, unsigned int value);
unsigned short sdf_read_unsigned_short(unsigned char *location);
void sdf_write_unsigned_short(unsigned char *location, unsigned short value);
signed char sdf_get_filename(int index, char *filename, unsigned char *filetype);
void sdf_unload(void);
void sdf_flag_clear(unsigned char flag);
signed char sdf_load(void);
signed char sdf_fix_filename(char *filename, char *newfilename, unsigned char *newfiletype);
unsigned char *sdf_find_index(char *filename);
unsigned char *sdf_find_filetype(char *filename, char filetype);
signed char sdf_delete_file(char *filename);
signed char sdf_add_file(char *filename);
signed char sdf_new_file(char *filename);
signed char sdf_save(char *filename);
signed char sdf_export_file(char *filename);
void sdf_decode(unsigned char mask, unsigned char draw_loadin);
signed char sdf_open(char *filename);
signed char sdf_read_line(void);
void sdf_flag_set(unsigned char *filename, unsigned char flag);
unsigned int sdf_checksum(unsigned char *data, int size);
void sdf_delete_all_files(unsigned char type_to_delete, unsigned char *prefix_string);
void sdf_list_all_files(unsigned char type_to_list, unsigned char *prefix_string, unsigned char export_too);
void sdf_reorganize_index(void);
int sdf_find_index_by_data(unsigned char *file_start);
#ifdef DEVTOOL
signed char sdf_insert_data(unsigned char* file_pos, unsigned char* data_to_add, int bytes_to_add);
#endif

#endif
