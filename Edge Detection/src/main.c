#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for sqrt
#include "argparser.h"
#include "convolution.h"
#include "derivation.h"
#include "gaussian_kernel.h"
#include "image.h"

int main(int const argc, char **const argv) {
    // Parse command line arguments
    parse_arguments(argc, argv);
    printf("Computing edges for image file %s with threshold %i\n", image_file_name, threshold);

    int width, height;
    float *img = read_image_from_file(image_file_name, &width, &height);
    if (!img) {
        fprintf(stderr, "Failed to read image from file.\n");
        return 1;
    }

    // Blur the image using Gaussian kernel
    float *blurred_img = array_init(width * height);
    convolve(blurred_img, img, width, height, gaussian_k, gaussian_w, gaussian_h);
    write_image_to_file(blurred_img, width, height, "out_blur.pgm");

    // Compute the derivatives in both x and y directions
    float *d_x = array_init(width * height);
    float *d_y = array_init(width * height);
    derivation_x_direction(d_x, blurred_img, width, height);
    derivation_y_direction(d_y, blurred_img, width, height);

    // Scale derivatives
    float *scaled_d_x = array_init(width * height);
    float *scaled_d_y = array_init(width * height);
    scale_image(scaled_d_x, d_x, width, height);
    scale_image(scaled_d_y, d_y, width, height);
    write_image_to_file(scaled_d_x, width, height, "out_d_x.pgm");
    write_image_to_file(scaled_d_y, width, height, "out_d_y.pgm");

    // Compute gradient magnitude from the scaled derivatives
    float *magnitude = array_init(width * height);
    gradient_magnitude(magnitude, d_x, d_y, width, height);

    // Scale the gradient magnitude
    float *scaled_magnitude = array_init(width * height);
    scale_image(scaled_magnitude, magnitude, width, height);
    write_image_to_file(scaled_magnitude, width, height, "out_gm.pgm");

    // Apply threshold and write the result
    apply_threshold(magnitude, width, height, threshold);
    write_image_to_file(magnitude, width, height, "out_edges.pgm");

    // Free dynamically allocated memory
    array_destroy(img);
    array_destroy(blurred_img);
    array_destroy(d_x);
    array_destroy(d_y);
    array_destroy(scaled_d_x);
    array_destroy(scaled_d_y);
    array_destroy(magnitude);
    array_destroy(scaled_magnitude);

    return 0;
}
