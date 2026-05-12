#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tag.h"

int edit_tag(FILE *mp3_ptr, int argc, char *argv[])
{
    // Create temporary file to store updated data
    FILE *temp_ptr = fopen("Temp.mp3", "wb");
    if(temp_ptr == NULL)
    {
        printf("Temp file creation failed\n");
        return 1;
    }

    // Command line tag options
    char *arr1[6] = {"-t","-A","-a","-y","-c","-C"};
    // Corresponding ID3 frame IDs
    char *arr2[6] = {"TIT2","TPE1","TALB","TYER","TCON","COMM"};

    char user_tag[5] = {0};
    int found = 0;

    // Find matching frame ID for user input
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(arr1[i], argv[2]) == 0)
        {
            strncpy(user_tag, arr2[i], 4);
            found = 1;
            break;
        }
    }

    // If invalid edit option
    if(!found)
    {
        printf("Invalid edit option\n");
        fclose(mp3_ptr);
        fclose(temp_ptr);
        return 1;
    }

    // Copy ID3 header (first 10 bytes)
    char header[10];
    fread(header, 1, 10, mp3_ptr);
    fwrite(header, 1, 10, temp_ptr);

    // Process each frame
    while(1)
    {
        char frame_id[5];

        // Read frame ID
        if(fread(frame_id, 1, 4, mp3_ptr) != 4)
            break;

        // Stop if padding reached
        if(frame_id[0] == '\0')
            break;

        frame_id[4] = '\0';

        // Read frame size
        unsigned char size_buf[4];
        fread(size_buf, 1, 4, mp3_ptr);

        unsigned int size = 0;
        for(int i = 0; i < 4; i++)
            size = (size << 8) | size_buf[i];

        // Read frame flags
        char flags[2];
        fread(flags, 1, 2, mp3_ptr);

        // If this is the frame to be edited
        if(strcmp(frame_id, user_tag) == 0)
        {
            fwrite(frame_id, 1, 4, temp_ptr);

            // Calculate new size (including encoding byte)
            unsigned int new_size = strlen(argv[3]) + 1;
            unsigned char new_size_buf[4];

            // Convert new size to big endian
            for(int i = 3; i >= 0; i--)
            {
                new_size_buf[i] = new_size & 0xFF;
                new_size >>= 8;
            }

            fwrite(new_size_buf, 1, 4, temp_ptr);
            fwrite(flags, 1, 2, temp_ptr);

            // Write encoding byte
            fputc(0x00, temp_ptr);
            // Write new tag data
            fwrite(argv[3], 1, strlen(argv[3]), temp_ptr);

            // Skip old frame data
            fseek(mp3_ptr, size, SEEK_CUR);
        }
        else
        {
            // Copy frame as it is
            fwrite(frame_id, 1, 4, temp_ptr);
            fwrite(size_buf, 1, 4, temp_ptr);
            fwrite(flags, 1, 2, temp_ptr);

            char *buffer = malloc(size);
            fread(buffer, 1, size, mp3_ptr);
            fwrite(buffer, 1, size, temp_ptr);
            free(buffer);
        }
    }

    // Copy remaining data (audio part)
    char ch;
    while(fread(&ch, 1, 1, mp3_ptr))
        fwrite(&ch, 1, 1, temp_ptr);

    fclose(mp3_ptr);
    fclose(temp_ptr);

    // Replace original file with updated file
    remove(argv[4]);
    rename("Temp.mp3", argv[4]);

    printf("Tag edited successfully\n");
    return 0;
}