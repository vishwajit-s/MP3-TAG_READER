/* NAME : VISHWAJIT SAWANT
   BATCH : 25036A
   DATE: 25/02/2026
   DESCRIPTION : program is a simple MP3 tag editor that allows viewing and modifying ID3v2 metadata in an .mp3 file. 
                 It reads frame headers, extracts tag information like Title and Artist, and updates selected frames by rewriting the
                 file through a temporary copy. The program uses file handling, big-endian size conversion, and command-line argument
                 processing to manage tag operations.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tag.h"

int main(int argc, char *argv[])
{
    // Check if minimum command line arguments are passed
    if(argc < 2)
    {
        printf("Not enough CLA passed\n");
        return 1;
    }

    // Determine operation type based on first argument
    Tag oper = check(argv[1]);

    // If operation is view
    if(oper == e_view)
    {
        // Validate number of arguments for view option
        if(argc != 3)
        {
            printf("Usage: ./mp3tag -v <filename>\n");
            return 1;
        }

        // Check if file format is .mp3
        if(strstr(argv[2], ".mp3") == NULL)
        {
            printf("Invalid file format\n");
            return 1;
        }

        // Open mp3 file in read binary mode
        FILE *mp3_ptr = fopen(argv[2], "rb");
        if(mp3_ptr == NULL)
        {
            printf("File open failed\n");
            return 1;
        }

        // Call function to view tags
        view_tag(mp3_ptr);
        fclose(mp3_ptr);   // Close file after viewing
    }
    // If operation is edit
    else if(oper == e_edit)
    {
        // Validate number of arguments for edit option
        if(argc != 5)
        {
            printf("Usage: ./mp3tag -e <tag> <new_data> <filename>\n");
            return 1;
        }

        // Check if file format is .mp3
        if(strstr(argv[4], ".mp3") == NULL)
        {
            printf("Invalid file format\n");
            return 1;
        }

        // Open mp3 file in read binary mode
        FILE *mp3_ptr = fopen(argv[4], "rb");
        if(mp3_ptr == NULL)
        {
            printf("File open failed\n");
            return 1;
        }

        // Call function to edit tag
        edit_tag(mp3_ptr, argc, argv);
    }
    // If help option is selected
    else if(oper == e_help)
    {
        printf("Help Menu:\n");
        printf("-v  View tags\n");
        printf("-e  Edit tags\n");
        printf("  -t  Title\n");
        printf("  -A  Artist\n");
        printf("  -a  Album\n");
        printf("  -y  Year\n");
        printf("  -c  Content\n");
        printf("  -C  Comment\n");
    }
    // If unsupported option is given
    else
    {
        printf("Unsupported operation\n");
    }

    return 0;   // End of program
}

// Function to check operation type
Tag check(char *symbol)
{
    if(strcmp(symbol, "-v") == 0)
        return e_view;        // Return view option
    else if(strcmp(symbol, "-e") == 0)
        return e_edit;        // Return edit option
    else if(strcmp(symbol, "-h") == 0)
        return e_help;        // Return help option
    else
        return e_unsupported; // Return unsupported option
}