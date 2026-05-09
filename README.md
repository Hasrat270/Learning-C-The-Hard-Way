# Learn C The Hard Way - Exercises

This repository contains my implementation of the exercises from Zed Shaw's book **"Learn C The Hard Way"**. Each exercise has been implemented with 100% fidelity to the book's logic, including comments and exact code structure.

## 🚀 Project Overview
The code is organized into logical folders following the learning sequence of the book. It covers everything from basic C syntax to advanced data structures and networking.

## 📁 Directory Structure
- **01-Introduction**: Basic syntax, variables, and loops (Ex 1-7).
- **02-Control_Flow**: Switch statements and arrays (Ex 8-11).
- **03-Pointers_and_Functions**: The "dreaded" pointers and function basics (Ex 12-13).
- **04-Memory_and_Structs**: Heap vs Stack and complex structures (Ex 14-16).
- **05-Debugging_and_Macros**: Robust error handling using `18-DebugMacros.h` (Ex 17-19).
- **06-Advanced_Types_and_Scope**: Duff's Device and scope rules (Ex 20-22).
- **07-IO_and_Varargs**: File I/O and variable arguments (Ex 23-24).
- **08-Project_Logfind**: System administration tools (Ex 25-26).
- **09-Build_Systems**: Intermediate Makefiles and Libraries (Ex 27-28).
- **10-Automated_Testing**: Unit testing framework (Ex 29).
- **11-Lists_and_Algos**: Double Linked Lists and Sorting (Ex 30-31).
- **12-Dynamic_Arrays**: Resizable arrays and searching (Ex 32-33).
- **13-Safer_Strings**: Using `bstrlib` for secure string handling (Ex 34).
- **14-Hashmaps**: Jenkins Hash and Bucket systems (Ex 35-36).
- **15-String_Algorithms**: Boyer-Moore-Horspool search (Ex 37).
- **16-Trees**: Binary and Ternary Search Trees with URL routing (Ex 38, 44, 45).
- **17-Stacks_and_Queues**: List-based data disciplines (Ex 39-40).
- **18-Devpkg**: Package management system using APR (Ex 41).
- **19-Ring_Buffer**: Asynchronous I/O buffers (Ex 42).
- **20-Stats_Engine**: Rolling statistics (Ex 43).
- **21-Networking**: TCP/IP Client implementation (Ex 45).

## 🛠️ How to Compile
A central `Makefile` is provided in the root directory to handle all exercises.

- **Compile all exercises:**
  ```bash
  make all
  ```
- **Compile a specific exercise:**
  ```bash
  make 14-Hashmaps/35-Hashmaps
  ```
- **Clean build artifacts:**
  ```bash
  make clean
  ```

## ⚖️ License
This code is for educational purposes based on the "Learn C The Hard Way" curriculum.
