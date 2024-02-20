#ifndef POULTRY_C_
#define POULTRY_C_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define return_defer(value) do {result = (value); goto defer;} while (0)

typedef int Errno;


void poultry_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color) {
    for (size_t i = 0; i < width * height; ++i) {
            pixels[i] = color;
    }
}

Errno poultry_save_to_ppm_file(uint32_t *pixels, size_t width, size_t height, const char *file_path) {
    int result = 0;
    FILE *f = NULL;
    {
        f = fopen(file_path, "wb");
        if (f == NULL) return_defer(errno);

        fprintf(f, "P6\n%lu %lu 255\n", (unsigned long)width, (unsigned long)height);
        if (ferror(f)) return_defer(errno); 

        for (size_t i = 0; i < width * height; ++i) {
            uint32_t pixel = pixels[i];
            uint8_t bytes[3] = {
                (pixel >> (8 * 0)) & 0xFF,
                (pixel >> (8 * 1)) & 0xFF,
                (pixel >> (8 * 2)) & 0xFF,
               // (pixel >> 8 * 3) &0xFF,
            };

            fwrite(bytes, sizeof(bytes), 1,  f);
            if(ferror(f)) return_defer(errno);
        }
    }
defer:
    if (f) fclose(f);
    return result;
}

#endif // POULTRY_C_