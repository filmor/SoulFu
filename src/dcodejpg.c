// <ZZ> This file contains functions to convert JPEG files to RGB
//  **  my_error_mgr            - A structure for the JPEG thing's error handling (ignore)
//  **  my_error_exit           - A function for the JPEG thing's error handling (ignore)
//  **  put_scanline_someplace  - Fills in the RGB file with data, Runs line by line (helper)
//  **  decode_jpg              - The main function to do a JPG conversion
#define TEXTURE_NO_ALPHA       0    // Normal texture
#define TEXTURE_ALPHA          1    // Color keyed transparency, Prefix '-'
#define TEXTURE_SUPER_ALPHA    2    // Color keyed with edge blur, Prefix '='
#define TEXTURE_DONT_LOAD      3    // Not supposed to load this onto card, Prefix '+'
#define TEXTURE_ON_CARD        4    // Has been loaded onto the card

unsigned char file_is_a_heightmap;
//-----------------------------------------------------------------------------------------------
struct my_error_mgr
{
    // <ZZ> Helper for the JPEG library.
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};
typedef struct my_error_mgr* my_error_ptr;

//-----------------------------------------------------------------------------------------------
METHODDEF(void) my_error_exit (j_common_ptr cinfo)
{
    // <ZZ> Helper for the JPEG library.
    my_error_ptr myerr = (my_error_ptr) cinfo->err;
    log_message("ERROR:  Had a problem decompressing JPEG file");
    longjmp(myerr->setjmp_buffer, 1);
}

//-----------------------------------------------------------------------------------------------
void put_scanline_someplace(JSAMPLE* read, unsigned char* newdata, int samples, int bytes_per_sample)
{
    // <ZZ> This function sticks a decoded scanline (at read) into a location (at newdata).  This
    //      is a helper for the JPEG decode thing.
    int i;
    unsigned char r, g, b;
//    unsigned char hi, lo;

    // Are we doing a heightmap?
    if(file_is_a_heightmap)
    {
        // Yup...  We'll want to leave everything as an 8-bit greyscale...
        if(bytes_per_sample == 3)
        {
            repeat(i, samples)
            {
                g = *read;  read+=3;
                *newdata = g;   newdata++;
            }
        }
        else
        {
            repeat(i, samples)
            {
                g = *read;  read++;
                *newdata = g;   newdata++;
            }
        }
    }
    else
    {
        // Is the image color or greyscale?
        if(bytes_per_sample == 3)
        {
            // Do the color loop
            repeat(i, samples)
            {
                r = *read;  read++;
                g = *read;  read++;
                b = *read;  read++;
//                convert_24bit_to_16bit(r, g, b, hi, lo);
//                *newdata = hi;   newdata++;
//                *newdata = lo;   newdata++;
                *newdata = r;   newdata++;
                *newdata = g;   newdata++;
                *newdata = b;   newdata++;
            }
        }
        else
        {
            // Do the greyscale loop
            repeat(i, samples)
            {
                g = *read;  read++;
                *newdata = g;   newdata++;
                *newdata = g;   newdata++;
                *newdata = g;   newdata++;
//                convert_24bit_to_16bit(g, g, g, hi, lo);
//                *newdata = hi;   newdata++;
//                *newdata = lo;   newdata++;
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------
signed char decode_jpg(unsigned char* index, unsigned char* filename)
{
    // <ZZ> This function decompresses a jpg file that has been stored in memory.  Index is a
    //      pointer to the start of the file's index in sdf_index, and can be gotten from
    //      sdf_find_index.  If the function works okay, it should create a new RGB file in the
    //      index and return TRUE.  It might also delete the original compressed file to save
    //      space, but that's a compile time option.  If it fails it should return FALSE, or
    //      it might decide to crash.
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;
    JSAMPARRAY buffer;      // Output row buffer
    int row_stride;         // physical row width in output buffer
    unsigned char* data;    // Compressed
    unsigned int size;      // Compressed
    unsigned char* newdata; // Decompressed
    unsigned int newsize;   // Decompressed
    int j;


    // Log what we're doing
    file_is_a_heightmap = FALSE;
    #ifdef VERBOSE_COMPILE
        log_message("INFO:     Decoding %s.JPG to %s.RGB", filename, filename);
    #endif
    if(filename[0] == 'H' && filename[1] == 'I' && filename[2] == 'T' && filename[3] == 'E')
    {
        file_is_a_heightmap = TRUE;
    }


    // Find the location of the file data, and its size...
    data = (unsigned char*) sdf_read_unsigned_int(index);
    size = sdf_read_unsigned_int(index+4) & 0x00FFFFFF;
    newdata = NULL;


    // Setup the custom error handler
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;
    if (setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);
        if(newdata)
        {
            #ifdef KEEP_COMPRESSED_FILES
                sdf_num_files--;
                sdf_extra_files++;
            #endif
            free(newdata);
        }
        return FALSE;
    }


    // Decompress the data
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, data, size);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);



    // Make sure we have room in the index for a new file
    #ifdef KEEP_COMPRESSED_FILES
        if(sdf_extra_files <= 0)
        {
            log_message("ERROR:  No room left to add file, program must be restarted");
            jpeg_destroy_decompress(&cinfo);
            return FALSE;
        }
    #endif



    // Allocate memory for the new file...  2 byte flags, 4 byte texture, 2 byte x, 2 byte y, x*y*3 bytes for data (x*y bytes for heightmap)
    newsize = 10;
    if(file_is_a_heightmap)
    {
        newsize+=((cinfo.output_width)*(cinfo.output_height));
    }
    else
    {
//        newsize+=(2*(cinfo.output_width)*(cinfo.output_height));
        newsize+=(3*(cinfo.output_width)*(cinfo.output_height));
    }
    newdata = malloc(newsize);
    if(newdata)
    {
        // Do we create a new index?
        #ifdef KEEP_COMPRESSED_FILES
            index = sdf_index+(sdf_num_files<<4);
            sdf_num_files++;
            sdf_extra_files--;
        #endif


        // Write the index...
        sdf_write_unsigned_int(index, (unsigned int) newdata);
        sdf_write_unsigned_int(index+4, newsize);
        *(index+4) = SDF_FILE_IS_RGB;
        repeat(j, 8) { *(index+8+j) = 0; }
        memcpy(index+8, filename, strlen(filename));



        // Write the texture info and file dimensions to the first 10 bytes
        sdf_write_unsigned_short(newdata, (unsigned short) 0);   newdata+=2;
        sdf_write_unsigned_int(newdata, (unsigned int) 0);   newdata+=4;
        sdf_write_unsigned_short(newdata, (unsigned short) cinfo.output_width);   newdata+=2;
        sdf_write_unsigned_short(newdata, (unsigned short) cinfo.output_height);  newdata+=2;
    }
    else
    {
        log_message("ERROR:  Not enough memory to decompress");
        jpeg_destroy_decompress(&cinfo);
        return FALSE;
    }


    // Continue decompressing
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        put_scanline_someplace(buffer[0], newdata, cinfo.output_width, cinfo.output_components);
        if(file_is_a_heightmap)
        {
            newdata+=cinfo.output_width;  // 1 byte per sample in the finished data
        }
        else
        {
//            newdata+=(cinfo.output_width<<1);  // 2 bytes per sample in the finished data
            newdata+=(cinfo.output_width*3);  // 3 bytes per sample in the finished data
        }
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);


    // Decide if we should get rid of the compressed file or not...
    #ifndef KEEP_COMPRESSED_FILES
        // Don't need to worry about index, since it should've been overwritten
        free(data);
        sdf_can_save = FALSE;
    #endif


    return TRUE;
}

//-----------------------------------------------------------------------------------------------

