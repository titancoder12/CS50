// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t SAMPLE_SIZE;
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    //copying header file
    BYTE c[44];

    fread(c, sizeof(BYTE), 44, input);
    fwrite(c, sizeof(BYTE), 44, output);

    //copying samples
    SAMPLE_SIZE d[1];
    int counter = 0;

    while (fread(d, sizeof(SAMPLE_SIZE), 1, input))
    {
        d[0] = factor * d[0];
        fwrite(d, sizeof(SAMPLE_SIZE), 1, output);
        counter += 1;
    }


    // Close files
    fclose(input);
    fclose(output);
}
