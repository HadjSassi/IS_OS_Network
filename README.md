# TP1 – Memory Segmentation
**3rd year IS – Systems and Networks**  
By Chahrazed Baatout & HADJ SASSI Mahdi
Instructor: C. Barès

---

## Exercise 1 – Memory Segmentation in C

### Objective
The goal of this exercise is to display addresses of variables located in different memory segments of a C program under Linux, and to verify them with the `pmap -X` command.

### Segments illustrated in this program
- **Data segment**: initialized global variables.
- **BSS segment**: uninitialized (or zero-initialized) global variables.
- **Read-only data (.rodata)**: string literals stored in the executable.

### Implementation details
We wrote a simple program that:
1. Declares three global variables to represent Data, BSS, and str.
2. Prints their addresses using `printf("%p")`.
3. Calls the Linux command `pmap -X <PID>` via `system()` to display the full memory map of the process.  
