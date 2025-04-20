# Project 2: Thread-Based Process Simulation and Synchronization

This project uses threads to simulate the Producer-Consumer problem in C. Producers and consumers interact with a shared circular buffer using semaphores and mutex locks.

Files
- src/sync_threads.c: Main program
- input/processes.txt: Input with thread sleep times
- output/sample_output.txt: Example output
- docs/Report P2.pdf: Report explaining the project
- Makefile: For compiling the program
- .gitignore: Files to ignore on GitHub
- README.md: This file

Input Format (processes.txt)
Each line contains two numbers:
thread_id sleep_time
Example:
1 3
2 2
3 1

How to Compile and Run
Using Makefile:
  make

Manually:
  gcc -o sync_threads src/sync_threads.c -lpthread

Run:
  ./sync_threads

Sample Output
[Producer 1] Produced item: 57 at index 0
[Consumer 1] Consumed item: 57 at index 0
...

Summary
This project shows how threads can work together safely using synchronization tools like semaphores and mutexes. The program runs without race conditions or deadlocks.
