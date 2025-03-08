# Inet3101-lab 2: In-Memory Database

## Overview
This program implements an in-memory database for parts records using C's dynamic memory allocation. The database stores information about parts including part number, name, size, size metric, and cost. 

## Design Coument
### Data Structure
The program uses a C structure to hold records with the following fields:
- Part number (int)
- Part name (char array)
- Part size (float)
- Part size metric (char array)
- Part cost (float)

### Memory Management
The program uses dynamic memory allocation to create an in-memory database:
- 'malloc()' creates new memory allocations for the database
- 'free()' releases memory when it's no longer needed
- Memory is manually reallocated when adding or removing records (without using 'realloc()')

### Functionality 
The program provides a menu-driven interface with the following options;
1. Print all records
2. Print number of records
3. Print size of database
4. Add record
5. Delete record
6. Exit

### Implementation Details 
- Records are stored in a contiguous block of memory
- When adding a record, a new larger block is allocated, data is copied, and old memeory is freed
- When deleting a record, a new smaller block is allocated, data is copied, and old memory is freed
- The program supports an empty database state and handles memory allocation failures
