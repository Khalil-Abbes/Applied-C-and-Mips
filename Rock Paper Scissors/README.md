# Project 1: Rock Paper Scissors

**Course:** Programming 2, Saarland University  

## Project Context
This repository contains my submission for the first mini-project in the Programming 2 course. The project focuses on low-level programming and pseudorandom number generation using MIPS assembly. 

The core objective was to implement a simulation of the game Rock Paper Scissors, where the computer plays against itself by generating random moves and determining the winner.

## Tech Stack
* MIPS Assembly
* MARS Simulator

## My Contributions

* **Random Number Generation (`gen_bit` / `gen_byte`):** 
  Implemented functions to query the MIPS random number generator and uniformly sample game moves using only bit-level randomness. I wrote the logic to discard invalid bit patterns to ensure all three moves (Rock, Paper, Scissors) had an equal probability of being selected.
* **Game Simulation (`play_game_once`):** 
  Built the logic to simulate a single round of the game, compare the generated moves for player 1 and player 2, and determine the winner (or tie) based on standard Rock Paper Scissors rules.
* **Cellular Automaton Simulation (`print_tape` / `simulate_automaton`):** 
  Replaced the built-in random number generator by implementing an Elementary Cellular Automaton (ECA) on a 1-dimensional tape. I wrote the logic to simulate the transition rules generation by generation and print the visual state of the tape to the console.

*Note: All implementations strictly adhered to MIPS calling conventions.*
