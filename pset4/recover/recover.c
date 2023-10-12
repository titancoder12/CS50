#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint8_t BYTE;


bool startsWithHeader(BYTE *buffer)
{
    return (buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0);
}


int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if ((argc < 2) || (argc > 2))
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[512];
    int filecounter = 0;
    char filename[8];
    int nextfile = 1;
    int loopcounter = 0;
    //FILE *file2 = fopen("file", "w");
    //fclose(file2);

    // Whenever the block starts with header, we know that block belongs to a new file.
    // So, when the block starts with header, we create a new file, and write the whole block to that file.

    // if a block does NOT start with the header, there are two possibilities:
    // 1. We have not found the first file yet. In which case, we continue to look for it.
    // 2. We are in the middle of writing to a file. We write this block to the current opened file.
    FILE *recoveredfile;
    while (fread(buffer, sizeof(BYTE), 512, file) >= 512)
    {
        if (startsWithHeader(buffer))
        {
            //change file name to ###.jpg
            sprintf(filename, "%03i.jpg", filecounter);

            if (filecounter == 0)
            {
                //open new file
                recoveredfile = fopen(filename, "w");
                //write to file

            }
            else
            {
                //close old file
                fclose(recoveredfile);
                //open new file
                recoveredfile = fopen(filename, "w");

            }
            //write to file
            fwrite(buffer, sizeof(BYTE), 512, recoveredfile);
            filecounter++;

        }
        else
        {
            //write to file
            if (filecounter >= 1)
            {
                fwrite(buffer, sizeof(BYTE), 512, recoveredfile);

            }

        }
    }




}






