# Palestine Districts — Radix Sort

A C project developed as part of the Data Structures and Algorithms course. It builds a 2-level hierarchy of Palestinian districts and their towns using a doubly linked list, sorts districts alphabetically using Radix Sort, and sorts towns by population using Bubble Sort.
## Overview

The program reads district and town data from an input file, stores it in a doubly linked list, and provides a menu-driven interface to sort, search, modify, and export the data.

## Data Structure

The program uses two doubly linked lists:

- **Districts list** — each node holds a district name, total population, and a pointer to its towns list
- **Towns list** — each district node has its own doubly linked list of towns, each holding a town name and population

## Input Format

The input file (`districts.txt`) uses pipe-separated values, one entry per line:

```
Hebron | Dura | 100000
Hebron | Halhul | 40000
Jenin | Jaba | 7000
Gaza | Jabalia | 20000
```

## Output Format

The output file (`sorted_districts.txt`) lists each district with its total population followed by its towns sorted in ascending order by population:

```
Gaza District, Population = 70000
Beit Hanoon, 50000
Jabalia, 20000
Hebron District, Population = 140000
...
```

## Menu Options

1. Load the input file
2. Print loaded data (before sorting)
3. Sort districts alphabetically using Radix Sort
4. Sort towns by population in ascending order
5. Print sorted data
6. Add a new district
7. Add a new town to a district
8. Delete a town from a district
9. Delete a complete district (and all its towns)
10. Calculate total population of Palestine, max and min town population
11. Print districts and their total population only
12. Change the population of a town
13. Save to output file
14. Exit

## Algorithms

- **Radix Sort** — used to sort district names alphabetically, character by character
- **Bubble Sort** — used to sort towns within each district by population in ascending order

## How to Compile and Run

```bash
gcc project1.c -o project1
./project1
```

Make sure `districts.txt` is in the same directory as the executable.
