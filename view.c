#include <stdio.h>
#include <string.h>
#include "tag.h"

void view_tag(FILE *mp3_ptr)
{
    // Skip ID3 header (first 10 bytes)
    fseek(mp3_ptr, 10, SEEK_SET);

    char arr[100];
    // Array of tag names to display
    char *tags_arr[6] = {"Title", "Artist", "Album", "Year", "Content type", "Comment"};

    // Loop through 6 standard ID3 frames
    printf("\n==================================================\n");
    printf("                 ID3 v2.3\n");
    printf("==================================================\n");
    for(int i = 0; i < 6; i++)
    {
        char tag[5];
        unsigned char size_buf[4];
        unsigned int size = 0;

        // Read frame ID (4 bytes)
        fread(tag, 1, 4, mp3_ptr);
        tag[4] = '\0';

        // Read frame size (4 bytes)
        fread(size_buf, 1, 4, mp3_ptr);

        // Convert size from big endian to integer
        for(int j = 0; j < 4; j++)
            size = (size << 8) | size_buf[j];

        // Skip 2 bytes of frame flags
        fseek(mp3_ptr, 2, SEEK_CUR);

        // Check if data size exceeds buffer limit
        if(size >= sizeof(arr))
        {
            printf("%-13s : Data too large\n", tags_arr[i]);
            fseek(mp3_ptr, size, SEEK_CUR);
            continue;
        }

        // Read tag data
        fread(arr, 1, size, mp3_ptr);
        arr[size] = '\0';

        // Print tag value (skip encoding byte)
        printf("%-13s : %-50s\n", tags_arr[i], arr + 1);
    }

}