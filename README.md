# 📚 Library Management System (LMS)

<p align="left">
  <img src="https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C11 Badge">
  <img src="https://img.shields.io/badge/Build-Makefile-427819?style=for-the-badge&logo=gnu-make&logoColor=white" alt="Makefile Badge">
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey?style=for-the-badge" alt="Platform Badge">
  <img src="https://img.shields.io/badge/Status-In%20Development-yellow?style=for-the-badge" alt="Status Badge">
</p>

> **Final Project — Computer Programming I**  
> A modularized, persistent, and terminal-based **Library Management System** built from scratch in C, featuring dynamic memory allocation, multi-format file persistence, and cross-platform UTF-8 terminal support.

---

## ✨ Current Project Status

The project is actively under development with its core foundation, UI loop, and dynamic data structures already up and running:

- [x] **Cross-Platform UTF-8 Support**: Automatic console encoding setup for both Windows (`SetConsoleCP`/`SetConsoleOutputCP`) and Linux (`setlocale`).
- [x] **Dynamic Book Vector (`VetorLivros`)**: Initialized dynamically in memory with automatic cleanup (`liberar`) upon exit.
- [x] **Custom CLI Interface & Banner**: Interactive box-drawn terminal menu paired with an external ASCII splash header (`title.txt`)[cite: 1].
- [x] **Book Registration & Listing**: Full input sanitization (`limpar_buffer`), string handling with spaces, duplicate ID validation, and formatted console output[cite: 1].
- [x] **ID Search & Safe Exit Flow**: Direct book lookup by ID and interactive exit confirmation prompt[cite: 1].
- [ ] **Book Removal & Array Shifting**: Removing records by ID without leaving memory gaps[cite: 1].
- [ ] **Sorting & Advanced Search**: Recursive Merge Sort (by title/year) and case-insensitive substring search (title, author, category)[cite: 1].
- [ ] **Dual File Persistence**: Saving and loading records in both plain text (`livros.txt`) and binary (`livros.dat`) formats[cite: 1].
- [ ] **Bonus Features**: User authentication (`usuarios.txt`), extra whitespace trimming, automatic category grouping, and `.csv` report export[cite: 1].

---

## 🏗️ Project Architecture

The codebase follows strict modular design principles, separating data structures, dynamic memory management, file I/O, and helper utilities:

```text
library-management-system/
├── include/               # Header files (.h)
│   ├── livro.h            # Book struct definition and single-record operations
│   ├── vetor.h            # Dynamic array (VetorLivros) management & sorting
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
│   ├── livros.dat         # Binary database snapshot
│   └── usuarios.txt       # Credentials file for system login
├── Makefile               # Automated build & cleanup rules
└── README.md              # Project documentation
```

---

## 🚀 Compilation & Execution

### Using `Makefile` (Recommended)
Make sure you have `gcc` and `make` installed (on Windows, MSYS2/MinGW is recommended):

```bash
# Compile the entire project with strict warning flags
make

# Run the application
./biblioteca        # Linux / macOS
biblioteca.exe      # Windows

# Clean compiled object files and binaries
make clean
```

### Manual Compilation (Without `make`)
If you prefer compiling directly via `gcc`:

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/*.c -o biblioteca
./biblioteca
```

---

## 📋 Menu Overview

| Option | Feature | Current State |
| :---: | :--- | :---: |
| **`[1]`** | **Register Book** (`ID`, `Title`, `Author`, `Year`, `Category`) | ✅ Implemented[cite: 1] |
| **`[2]`** | **List All Books** (with Title/Year sorting options) | 🟡 Listing active / Sorting WIP[cite: 1] |
| **`[3]`** | **Search Books** (by ID, Title substring, Author, or Category) | 🟡 ID search active / Filters WIP[cite: 1] |
| **`[4]`** | **Remove Book by ID** (with dynamic array reorganization) | 🚧 In Progress[cite: 1] |
| **`[5]`** | **Save to Text File** (`livros.txt`) | 🚧 In Progress[cite: 1] |
| **`[6]`** | **Save to Binary File** (`livros.dat`) | 🚧 In Progress[cite: 1] |
| **`[7]`** | **Load Data from Files** | 🚧 In Progress[cite: 1] |
| **`[8]`** | **Generate Reports & Export `.csv`** | 🚧 In Progress[cite: 1] |
| **`[9]`** | **Exit** (with unsaved-changes prompt & memory `free`) | 🟡 Prompt active / Persistence hook WIP[cite: 1] |

---

## 🗄️ Data Format Specification

### Plain Text Database (`livros.txt`)
Records are stored one per line using a semicolon (`;`) delimiter:
```text
101;O Hobbit;J.R.R. Tolkien;1937;Fantasia
102;1984;George Orwell;1949;Ficcao Cientifica
103;Clean Code;Robert C. Martin;2008;Tecnologia
```

---

## 👥 Authors

Developed collaboratively as the final capstone for **Computer Programming I**:

* **Vinícius de Queiroz (`@vinicius133`)** — Main menu orchestration, cross-platform UTF-8 & input utilities (`util`), text/binary file persistence (`arquivo`), login authentication, CSV export, and build system (`Makefile`).
* **José** — Book data structures (`livro`), dynamic memory array (`vetor`), recursive Merge Sort, search filters, and statistical reporting.