# Project 3: PageRank

## Project Context
The project focuses on graph theory, file parsing, and probabilistic algorithms in C.

The core objective was to analyze directed graphs (representing websites and hyperlinks) and compute PageRank scores to determine the relevance of each node in the network.

## Tech Stack
* C (C11 Standard)
* GCC, Make
* DOT Graph Format parsing

## My Contributions

* **Graph Parsing & Data Structures:** 
  Developed a custom parser to read directed graphs in the `.dot` format into dynamically allocated memory.
* **Network Statistics:** 
  Implemented logic to compute and print network statistics for the parsed graph, including total node/edge counts and minimum/maximum in/out degrees.
* **Random Surfer Simulation:** 
  Implemented the "Random Surfer" model to approximate PageRank scores. The program simulates a user clicking random links (or getting bored and jumping to a random page with probability $p$) over $N$ steps, tracking the visit frequencies of each node to calculate the final rank.
* **Error Detection (Bonus):** 
  Implemented robust error handling to validate command-line arguments, check file existence, and verify correct input file formats, ensuring the program exits gracefully with the correct status codes.
