#include "image.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apply_threshold(float *img, int w, int h, int T) {
    
    for (int i = 0; i < w * h ; i++ ) {
        if (img[i] <= T) {
            img[i] = 0;
        } else { img[i] = 255;}
    }

}

void scale_image(float *result, const float *img, int w, int h) {
    float max = 0 , min = 255;
    for (int i = 0; i < w * h; i++) {
        if (img[i] > max) {
            max = img[i];
        }
        if (img[i] < min) {
            min = img[i];
        }
    }

if (max == min) {
        for (int i = 0; i < w * h; i++) {
            result[i] = 0;
        }} else {
for (int i = 0 ; i < w * h ; i++) {
    result[i] = ((img[i] - min)/(max - min)) * 255.0f;
}
        }


}

float get_pixel_value(const float *img, int w, int h, int x, int y) {
    // Adjust x and y to mirror correctly at the boundaries
    if (x < 0) {
        x = -x - 1;  // Mirror left edge
    } else if (x >= w) {
        x = 2*w - x - 1;  // Mirror right edge
    }

    if (y < 0) {
        y = -y - 1;  // Mirror top edge
    } else if (y >= h) {
        y = 2*h - y - 1;  // Mirror bottom edge
    }

    // Return the mirrored value within the boundaries
    return img[y * w + x];
}




float* array_init(int size) {
    // Allocate memory for the array using malloc
    float* array = (float*) malloc(size * sizeof(float));
    
    // Optional: Initialize the array elements to zero
    if (array != NULL) {
        for (int i = 0; i < size; i++) {
            array[i] = 0.0f;
        }
    }

    return array;
}


void array_destroy(float *m) {
    // Free the allocated memory
    if (m != NULL) {
        free(m);
    }
}

float* read_image_from_file(const char *filename, int *w, int *h) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        // Handle file open error silently
        return NULL;
    }

    int maxval;
    char format[3];
    if (fscanf(file, "%2s", format) != 1 || format[0] != 'P' || format[1] != '2') {
        // Handle invalid format silently
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d %d %d", w, h, &maxval) != 3 || *w <= 0 || *h <= 0 || maxval != 255) {
        // Handle invalid header data silently
        fclose(file);
        return NULL;
    }

    float *img = (float *)malloc((*w) * (*h) * sizeof(float));
    if (!img) {
        // Handle memory allocation failure silently
        fclose(file);
        return NULL;
    }

    int pixel;
    for (int i = 0; i < (*w) * (*h); i++) {
        if (fscanf(file, "%d", &pixel) != 1 || pixel < 0 || pixel > 255) {
            // Handle pixel data errors silently
            free(img);
            fclose(file);
            return NULL;
        }
        img[i] = (float)pixel;
    }

    // Check for extra data in the file
    if (fscanf(file, "%d", &pixel) != EOF) {
        // Handle extra data beyond expected pixel count silently
        free(img);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return img;
}



void write_image_to_file(const float *img, int w, int h, const char *filename) {
    // Open the file in write mode
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open the file for writing.\n");
        return;
    }

    // Write the header for a P2 PGM file
    fprintf(file, "P2\n%d %d\n255\n", w, h);

    // Write the image data: converting float to int, rounding down
    for (int i = 0; i < w * h; i++) {
        // Rounding down the pixel value to the nearest integer
        int pixel = (int)img[i];
        fprintf(file, "%d\n", pixel);
    }

    // Close the file
    fclose(file);
}

