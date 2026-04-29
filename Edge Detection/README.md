# Project 2: Edge Detection

## Project Context
The project focuses on image processing, memory management, and mathematical operations in C.

The core objective was to implement an edge detection algorithm that reads an image, applies a Gaussian blur, computes discrete derivatives using Sobel kernels, and outputs a high-contrast image highlighting borders between homogeneous areas.

## Tech Stack
* C (C11 Standard)
* GCC, Make
* PGM Image Format parsing

## My Contributions

* **Matrix Convolution:** 
  Implemented a robust 2D convolution function (`convolve`) using a mirror edge-handling strategy. This was used to apply Gaussian (blur) and Sobel (derivative) kernels to the image.
* **Gradient Computation & Thresholding:** 
  Implemented functions to calculate the magnitude of gradient vectors using partial derivatives ($D_x$ and $D_y$) and applied gray-scale thresholds to isolate prominent edges.
* **Image Scaling:** 
  Scaled intermediate gray-scale computations back to the standard $0–255$ pixel value range to ensure valid image output.
* **File I/O and Memory Management:** 
  Handled dynamic memory allocation for 2D images and wrote robust functions to read/write `.pgm` (portable graymap) files, including robust error detection for corrupted files, invalid headers, or missing paths.
* **Algorithm Pipeline (`main`):** 
  Combined all mathematical and memory operations into a cohesive pipeline inside the `main` function, managing intermediate memory allocations and ensuring a leak-free program.
