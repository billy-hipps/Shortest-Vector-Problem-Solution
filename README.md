# List Sieving Implementation in C for the Shortest Vector Problem

## Overview

This repository contains the implementation of a heuristic solution for the Exact Shortest Vector Problem (SVP) using the List Sieving algorithm. The project was developed as part of a Systems Programming assignment attached to the Level 2 Programming Paradigms module and achieved a mark of 60%.

## Project Structure

### Source Files
- **Main Program:**
  - `main.c`: Contains the entry point of the program and orchestrates the execution of the List Sieving algorithm.

- **Supporting Modules:**
  - `checkArgs.c`: Handles command-line argument validation and processing.
  - `common.c`: Includes common functions and utilities used across the project.
  - `cosScore.c`: Computes the mean cosine similarity of the input basis vectors.
  - `getBasis.c`: Handles the input and initialization of the lattice basis.
  - `listSieve.c`: Implements the core List Sieving algorithm and related subroutines.
  - `reduce.c`: Contains the subroutines for reducing lattice vectors.
  - `sample.c`: Generates sample vectors within the lattice.

### Build Files
- `Makefile`: Defines the build process for compiling the source files into an executable.

### Documentation
- `Report.pdf`: Provides detailed documentation of the project, including the algorithm description, optimizations, performance analysis, and references.

### Timing and Performance Analysis
- **Timing Data and Scripts:**
  - `timing/`
    - `reduceTimes.xlsx`: Contains timing data for the `reduce` subroutine.
    - `sampleTimes.xlsx`: Contains timing data for the `sample` subroutine.
    - `test.sh`: Script to run tests and collect timing data.
    - `timing_results.txt`: Raw timing results from executing the program.
    - `timing.sh`: Main script for executing the timing tests.
    - `timingFuncs.sh`: Helper functions for timing tests.
    - `timingVis.py`: Python script for visualizing timing data.
    - `visualise.ipynb`: Jupyter Notebook for analyzing and visualizing the timing data.

## Algorithm

The List Sieving algorithm involves random sampling of lattice vectors and exploits the property that any linear combination of lattice vectors is also a lattice vector. The method iteratively reduces sampled vectors until a shorter vector cannot be identified after \(2^{cn}\) samples, where \(n\) is the dimension of the lattice basis. The algorithm has an optimal time complexity of \(O(2^{1.325n})\).

### Alterations

1. **Addition of CosScore Subroutine:**
   - Computes the mean cosine similarity of the input basis vectors and maps it to an integer \(c\), used to bound the number of sample vectors produced. This aims to save time and memory for highly orthogonal bases.

2. **Alteration to Sample Subroutine:**
   - Generates random linear combinations of basis vectors with a length less than twice the length of the longest basis vector, simplifying the implementation while maintaining effectiveness.

3. **Alteration to ListSieve:**
   - Initializes \(\mu\) to the Euclidean norm of the shortest basis vector and updates it recursively as shorter vectors are found.

## Optimizations

- Memory for the list of reduced lattice vectors is allocated and deallocated outside the ListSieve function to minimize the impact of memory reallocation on running time.
- Memory management is performed in caller functions where possible to improve pointer safety and simplify deallocation.

## Performance Analysis

The performance analysis showed a greater-than-exponential increase in running time from eight to nine dimensions. The sample subroutine was identified as the primary cause of this disproportionate increase.

### Timing Analysis Scripts

- **Timing Data Collection:**
  - `timing/test.sh` and `timing/timing.sh` are used to run tests and collect timing data.
  - `timing/reduceTimes.xlsx` and `timing/sampleTimes.xlsx` contain the collected timing data for the `reduce` and `sample` subroutines, respectively.

- **Visualization:**
  - `timing/timingVis.py` and `timing/visualise.ipynb` are used for analyzing and visualizing the timing data to identify performance bottlenecks.

## Future Improvements

To improve the time complexity, the original form of the sample subroutine could be used to create an array of sample vectors, which can then be split into smaller chunks optimized for multi-threading. Developing a communication system to update the current shortest vector across threads would also improve extensibility and processing speed for large and complicated lattices.

## References

- Galbraith, S. (2014). Chapter 17 Lattice Basis Reduction. Retrieved November 2023, from University of Auckland.
- Micciancio, D. (2021). CSE 206A: Lattice Algorithms and Applications. Retrieved November 2023, from University of California San Diego.

---

## Instructions for Running the Program

- 1. Install the prerequistites.
- 2. Construct the Docker container. 
- 3. Make and run the program. 

### Prerequisites

Ensure you have `gcc` and `make` installed on your system.

## Docker Container Instructions

### Building the Docker Container

To build the Docker container, ensure you have Docker installed on your system. Navigate to the directory containing the `Dockerfile` and run the following command:

```sh
docker build -t svp-listsieve
```

### Running the Docker Container

To run the Docker container, use the following command:

```sh
docker run -it svp-listsieve
```

This Dockerfile sets up an Ubuntu-based container with all the necessary dependencies to compile and run the List Sieving algorithm. The source code is copied into the `/code` directory within the container, and the working directory is set to `/code`. The container starts with the Bash shell.

### Compilation

To compile the program, navigate to the directory containing the source files and the Makefile, and run the following command:

```sh
make
```

This will compile the source files and produce an executable named `runme`.

### Running the Program

To run the compiled program on a three dimensional lattice for example, execute the following command:

```sh
./runme [1.0 0.0 0.0] [0.0 1.0 0.0] [0.0 0.0 1.0]
```

### Cleaning Up

To clean up the compiled objects and executables, use the following command:

```sh
make clean
```

---
