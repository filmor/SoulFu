// <ZZ> This file contains functions pertaining to random numbers
//      random_setup            - Sets up the random number table
//      random_number           - Returns a random number from 0 to 255
//      random_dice             - Simulates a dice roll

#include "random.h"

int random_setup(int seed)
{
    return srand(seed);
}


unsigned char random_number()
{
    return (unsigned char) (rand() * 256.0 / RAND_MAX);
}


unsigned short random_dice(unsigned char number, unsigned short sides)
{
    // <ZZ> This function rolls some dice and returns the result.
    // random_dice(2, 6) == 2d6...
    unsigned char i;
    unsigned short value = 0;

    if(sides > 0)
    {
        repeat(i, number)
        {
            // Roll one die...
            // And add it to the running total
            value += random_number() * sides / 256.0 + 1;
        }
    }
    return value;
}


unsigned char* random_name(unsigned char* filedata)
{
    // <ZZ> This function returns a pointer to a random name string (NAME_STRING) from
    //      one of the random naming datafiles.  Data is in the format of a
    //      null-terminated text file, with commas seperating random choices and new
    //      lines (null terms) seperating segment blocks.  The '-' character is used
    //      to repeat the last value in the preceding block...  "Dun-agorn" becomes
    //      "Dunnagorn"...
    #define MAX_NAME_SEGMENT 8
    unsigned short segment, num_segment;
    unsigned short num_choice[MAX_NAME_SEGMENT];
    unsigned char* segment_start[MAX_NAME_SEGMENT];
    unsigned short index, choice;
    unsigned char* read;
    unsigned char last_value;
    int filesize;
    int i;
    unsigned short name_size;

//log_message("INFO:   Generating random name...");

    NAME_STRING[0] = 0;
    name_size = 0;
    index = sdf_find_index_by_data(filedata);
    if(index != 65535)
    {
        // Found the file in the SDF datafile...
        filesize = sdf_read_unsigned_int(sdf_index+(index<<4)+4) & 0x00FFFFFF;


        // Clear out our totals...
        num_segment = 0;
        repeat(i, MAX_NAME_SEGMENT)
        {
            num_choice[i] = 0;
            segment_start[i] = filedata;
        }


        // Read through the text file, looking for commas and null terms...
        read = filedata;
        last_value = 0;
        repeat(i, filesize)
        {
            if(*read == ',')
            {
                // We found a new choice...
                num_choice[num_segment]++;
//log_message("INFO:       Found choice");
            }
            else if(*read == 0)
            {
                // Was the last value a null term too?
                if(last_value == 0)
                {
                    // Yup, that means we're all done with our preliminary scan...
                    // Two returns in a row should only happen at end of file...
                    i = filesize;
                }
                else
                {
                    // We found a new choice and segment...
//log_message("INFO:     Found segment");
                    num_choice[num_segment]++;
                    num_segment++;
                    if(num_segment >= MAX_NAME_SEGMENT)
                    {
                        // We can't handle any more segments...  Time to quit...
                        i = filesize;
                    }
                    else
                    {
                        // Remember where the next segment starts...
                        segment_start[num_segment] = read+1;
                    }
                }
            }


            last_value = *read;
            read++;
        }

//log_message("INFO:   Picking segments...");

        // Should now have a rough idea of how many name segments and stuff we're
        // lookin' at...
        // Lets randomly pick some...
        repeat(segment, num_segment)
        {
//log_message("INFO:     Segment %d", segment);
            // Pick a random choice for each segment...
            if(num_choice[segment] > 0)
            {
                choice = random_number() % num_choice[segment];
//log_message("INFO:       Choice %d (of %d)", choice, num_choice[segment]);


                // Now search for the selected choice by reading through where
                // commas are...
                read = segment_start[segment];
                i = 0;
                while(i < choice)
                {
                    if(*read == ',')
                    {
                        i++;
                    }
                    read++;
                }


                // Read should now be at the start of our segment choice... 
                // Copy it into the name string...
                while(*read != ',' && *read != 0 && name_size < 100)
                {
                    NAME_STRING[name_size] = *read;
                    if(NAME_STRING[name_size] == '-' && name_size > 0 && segment > 0)
                    {
                        NAME_STRING[name_size] = NAME_STRING[name_size-1];
                    }
                    read++;
                    name_size++;
                }
                NAME_STRING[name_size] = 0;
            }
        }
    }

    NAME_STRING[15] = 0;  // Never allow names longer than 15 characters...
//log_message("INFO:   New name is %s", NAME_STRING);
    return NAME_STRING;
}


/*
log_message("INFO:   Getting random name...");


    index = sdf_find_index_by_data(filedata);
    if(index != 65535)
    {
        // Found the file in the SDF datafile...
        filesize = sdf_read_unsigned_int(sdf_index+(index<<4)+4) & 0x00FFFFFF;


        count = filesize >> 4;
log_message("INFO:     %d names in file...", count);
        if(count > 0)
        {
            count = random_number;
            count = count % (*filedata);
            filedata+=(count << 4) + 16;
        }
    }
    return filedata;
*/

