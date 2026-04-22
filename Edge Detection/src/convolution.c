#include "convolution.h"

#include <stdlib.h>

#include "image.h"

void convolve(float *result, const float *img, int w, int h, const float *M, int wM, int hM) {
    int a = wM / 2;
    int b = hM / 2;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            float sum = 0.0;
            for (int j = 0; j < hM; j++) {
                for (int i = 0; i < wM; i++) {
                    int xIndex = x - a + i;
                    int yIndex = y - b + j;
                    float pixelValue = get_pixel_value(img, w, h, xIndex, yIndex);
                    float current = M[j * wM + i];
                    sum += current * pixelValue;
                }
            }
            result[y * w + x] = sum;
        }
    }
}

