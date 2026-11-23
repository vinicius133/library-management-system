# 📚 Library Management System (LMS)

<p align="left">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Badge">
  <img src="https://img.shields.io/badge/Build-Makefile-427819?style=for-the-badge&logo=gnu-make&logoColor=white" alt="Makefile Badge">
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-purple?style=for-the-badge" alt="Platform Badge">
  <img src="https://img.shields.io/badge/Status-In%20Development-yellow?style=for-the-badge" alt="Status Badge">
</p>

> **Final Project | Computer Programming I**  
> A modular, terminal-based Library Management System built from scratch in C, combining dynamic memory management, recursive sorting, multi-filter search, user authentication, statistical reporting, and dual-format persistence (.txt, .dat, and .csv) with cross-platform UTF-8 support.

---
<br>

## ✨ Current Project Status

The project is actively under development:

- [x] **Cross-Platform UTF-8 Support**: Automatic console encoding setup for both Windows (`SetConsoleCP`/`SetConsoleOutputCP`) and Linux (`setlocale`).
- [x] **Dynamic Book Vector (`VetorLivros`)**: Initialized dynamically in memory with automatic cleanup (`liberar`) upon exit.
- [x] **Custom CLI Interface & Banner**: Interactive box-drawn terminal menu paired with an external ASCII splash header (`title.txt`).
- [x] **Book Registration & Listing**: Full input sanitization (`limpar_buffer & limpar_espacos`), string handling with spaces, duplicate ID validation, and formatted console output.
- [x] **Multi-filter search & Safe Exit Flow**: Direct book lookup by author, category and title. Also have an interactive exit confirmation prompt.
- [x] **Book Removal & Array Shifting**: Removes books by ID without leaving memory gaps.
- [x] **Sorting & Advanced Search**: Recursive Merge Sort and case-insensitive substring search (title, author, category).
- [ ] **Dual File Persistence**: Saving and loading records in both plain text (`livros.txt`) and binary (`livros.dat`) formats.
- [ ] **Bonus Features**: User authentication (`usuarios.txt`), extra whitespace trimming, automatic category grouping, and `.csv` report export.

---

## 🏗️ Project Architecture

The codebase follows strict modular design principles, separating data structures, dynamic memory management, file I/O, and helper utilities:

```text
library-management-system/
├── include/               # Header files (.h)
│   ├── livro.h            # Book struct definition and single-record operations
│   ├── vetor.h            # Dynamic array management & sorting
│   ├── arquivo.h          # Text/Binary persistence, login & CSV export
│   └── util.h             # Buffer sanitization & input validation helpers
├── src/                   # Source files (.c)
│   ├── main.c             # Application entry point, UTF-8 setup & main menu loop
│   ├── livro.c
│   ├── vetor.c
│   ├── arquivo.c
│   └── util.c
├── data/                  # Persistent storage & assets
│   ├── title.txt          # Custom ASCII art banner loaded at startup
│   ├── livros.txt         # Human-readable database (ID;Title;Author;Year;Category)
│   ├── livros.dat         # Binary database
│   └── usuarios.txt       # Credentials file for system login
├── Makefile               # Automated build & cleanup rules
└── README.md              # Project documentation
```

---

## 🚀 Compilation & Execution

### Using `Makefile` (Recommended)

```bash
# Compile the entire project with strict warning flags
make

# Run the application
./lms        # Linux / macOS
lms.exe      # Windows

# Clean compiled object files and binaries
make clean
```

### Manual Compilation (Without `make`)

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/*.c -o lms
./lms
```

---

## 📋 Menu Overview

| Option | Feature | Current State |
| :---: | :--- | :---: |
| **`[1]`** | **Register Book** (`ID`, `Title`, `Author`, `Year`, `Category`) | ✅ Implemented |
| **`[2]`** | **List All Books** (with Title/Year sorting options) | 🚧 In Progress (Listing working, sorting not yet) |
| **`[3]`** | **Search Books** (by ID, Title substring, Author, or Category) | 🚧 In Progress (ID search working, filters not yet) |
| **`[4]`** | **Remove Book by ID** (with dynamic array reorganization) | 🚧 In Progress |
| **`[5]`** | **Save to Text File** (`livros.txt`) | 🚧 In Progress |
| **`[6]`** | **Save to Binary File** (`livros.dat`) | 🚧 In Progress |
| **`[7]`** | **Load Data from Files** | 🚧 In Progress |
| **`[8]`** | **Generate Reports & Export `.csv`** | 🚧 In Progress |
| **`[9]`** | **Exit** (with unsaved-changes prompt & memory `free`) | 🚧 In Progress (No saving yet) |

---
<br><br><br>

## 👥 Authors

Developed collaboratively as the final capstone for **Computer Programming I**:

* **Vinícius ([@vinicius133](https://github.com/vinicius133))** — Main menu orchestration, input utilities (`util`), text/binary file persistence (`arquivo`), login authentication, CSV export, and build system (`Makefile`).
* **José ([@Devze2612](https://github.com/Devze2612))** — Book data structures (`livro`), dynamic memory array (`vetor`), recursive Merge Sort, search filters, and statistical reporting.
