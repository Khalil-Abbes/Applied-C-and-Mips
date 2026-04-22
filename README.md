# Programming 2

**Course:** Programming 2, Saarland University
**Instructor:** Prof. Dr.-Ing. Holger Hermanns

## Overview
This repository contains my submissions for the bi-weekly mini-projects assigned during the Programming 2 course. The projects cover a range of low-level and systems programming concepts, including assembly programming, memory management, image processing, and graph algorithms in C and MIPS assembly. 

Below is a summary of the projects and my contributions to each.

---

### [Project 1: Rock Paper Scissors](./Rock%20Paper%20Scissors/)

This project involved writing MIPS assembly code to simulate the game of Rock Paper Scissors, where the computer plays against itself using pseudorandom number generation. 

**My Core Contributions:**
* **Random Number Generation (`gen_bit` / `gen_byte`):** Implemented functions to query the MIPS random number generator and uniformly sample game moves using only bit-level randomness.
* **Game Simulation (`play_game_once`):** Built the logic to simulate a single round of the game, compare the selected moves, and determine the winner based on the rules of Rock Paper Scissors.
* **Cellular Automaton Simulation (`print_tape` / `simulate_automaton`):** Implemented an Elementary Cellular Automaton (ECA) on a 1-dimensional tape. I wrote the logic to print the tape state to the console and simulate the transition rules generation by generation.

---

### [Project 2: Edge Detection](./Edge%20Detection/)

This project focused on implementing an edge detection algorithm for images in C, utilizing discrete derivatives and image convolution.

**My Core Contributions:**
* **Thresholding & Gradient Magnitude:** Implemented functions to apply gray-scale thresholds and calculate the magnitude of gradient vectors using partial derivatives ($D_x$ and $D_y$).
* **Image Scaling:** Scaled intermediate gray-scale computations back to the standard $0–255$ pixel value range.
* **Matrix Convolution:** Implemented a robust 2D convolution function using a mirror edge-handling strategy to apply Gaussian (blur) and Sobel (derivative) kernels to the image.
* **File I/O and Memory Management:** Handled dynamic memory allocation for 2D images and wrote robust functions to read/write `.pgm` (portable graymap) files, including error detection for corrupted or missing files.
* **Algorithm Pipeline (`main`):** Combined all steps into a cohesive pipeline inside the `main` function, managing intermediate memory allocations and ensuring no memory leaks.

---

### [Project 3: PageRank](./PageRank/)

This project involved parsing directed graphs (representing websites and hyperlinks) and computing PageRank scores using C.

**My Core Contributions:**
* **Graph Parsing & Statistics:** Developed a parser to read directed graphs in the `.dot` format into dynamically allocated memory. Implemented logic to compute and print network statistics, including node/edge counts and min/max in/out degrees.
* **Random Surfer Simulation:** Implemented the "Random Surfer" model to approximate PageRank. The program simulates a user clicking random links (or getting bored and jumping to a random page with probability $p$) over $N$ steps, tracking visit frequencies to calculate the final rank.
* **Error Detection (Bonus):** Implemented robust error handling to validate command-line arguments, check file existence, and verify correct input file formats, ensuring the program exits gracefully with the correct status codes.

---

## Tech Stack
* C (C11 Standard)
* MIPS Assembly (MARS Simulator)
* Custom parsing (PGM images, DOT graph format)
* GCC, Make, GDB
