# TP1 – Memory Segmentation and Linked Lists
**3rd year IS – Systems and Networks**  
By Chahrazed Baatout & HADJ SASSI Mahdi  
Instructor: C. Barès

---

## 📂 Project Structure
- **Ex1.c** → Memory segmentation in C (Data, BSS, Str, Heap, Stack, Main, LibC, Mmap).
- **Ex2.c** → File mapping with `mmap` and in-memory content modification.
- **Ex3.c** → Singly linked list with basic operations (create, display, add/remove, concat, apply function).
- **Ex3DoubleLinkedCircular.c** → Doubly circular linked list with insertion, deletion, traversal, and concatenation.
- **main.c** → Entry point
- **Makefile** → Generic compilation of all `.c` files.

---

##  Exercises Summary

### Exercise 1 – Memory Segmentation
We displayed the addresses of variables in different memory segments of a process and verified them with `pmap -X`.

## Exercise 2 – File Mapping with mmap
We created a program that writes text into a file, maps it into memory with `mmap`, reverses its content in place, and shows the result.

### Exercise 3 – Singly Linked Lists
We created a linked list of integers with operations to measure size, display nodes, add/remove at head or tail, concatenate lists, and apply functions (e.g., square).

### Doubly Circular Linked Lists
We extended the implementation to circular doubly linked lists with robust insertion, deletion, concatenation, and traversal in both directions.



