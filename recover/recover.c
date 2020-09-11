/*
Even though JPEGs are more complicated than BMPs, JPEGs have “signatures,” patterns of bytes that can distinguish them from other file formats. Specifically, the first three bytes of JPEGs are

0xff 0xd8 0xff

from first byte to third byte, left to right. The fourth byte, meanwhile, is either
0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef. Put another way, the fourth byte’s first four bits are 1110.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
int filenum = 0;
char filename[8];
FILE *image = NULL;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("The program should have only one argument which is the name of a forensic image from which to recover JPEGs\n");
        return 1;
    }

    FILE *memorycard = fopen(argv[1], "r");
    if (memorycard == NULL)
    {
        printf("The file cannot be opened\n");
        return 1;
    }

    BYTE *read = malloc(sizeof(BYTE) * 512);
    while (fread(read, sizeof(BYTE), 512, memorycard) == 512)
    {
        if (read[0] == 0xff && read[1] == 0xd8 && read[2] == 0xff && ((read[3] & 0xf0) == 0xe0))
        {
            if (filenum != 0)
            {
                fclose(image);
            }

            sprintf(filename, "%.3d.jpg", filenum);
            image = fopen(filename, "w");
            fwrite(read, sizeof(BYTE), 512, image);
            filenum++;

        }

        else if (filenum != 0)
        {
            fwrite(read, sizeof(BYTE), 512, image);
        }

    }
    fclose(image);
    free(memorycard);
    free(image);
}
