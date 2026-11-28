# 📚 Library Management System (LMS)

<p align="left">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Badge">
  <img src="https://img.shields.io/badge/Build-Makefile-427819?style=for-the-badge&logo=gnu-make&logoColor=white" alt="Makefile Badge">
  <img src="https://img.shields.io/badge/Memory-Dynamic%20(Heap)-blueviolet?style=for-the-badge" alt="Memory Badge">
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-purple?style=for-the-badge" alt="Platform Badge">
  <img src="https://img.shields.io/badge/Status-In%20Development-yellow?style=for-the-badge" alt="Status Badge">
</p>

> **Final Capstone Project | Computer Programming I**  
> A modular, terminal-based **Library Management System** built from scratch in C. Designed to apply core systems programming concepts—dynamic heap allocation, recursive sorting, input buffer sanitization, and file persistence—wrapped in a clean, cross-platform UTF-8 command-line interface.

---

## ✨ Feature Roadmap & Current Status

- [x] **Cross-Platform UTF-8 Engine**: Automatic console encoding setup for Windows (`SetConsoleCP` / `SetConsoleOutputCP`) and POSIX/Linux (`setlocale`), ensuring proper rendering of accented characters.
- [x] **Dynamic Array (`VetorLivros`)**: Starts with capacity for 10 books (`malloc`) and automatically doubles its capacity (`realloc`) as the catalog grows, freeing all memory (`free`) safely upon exit.
- [x] **Custom CLI & Splash Banner**: Box-drawn terminal interface arranged in vertical columns, paired with an external ASCII header loaded at runtime (`data/title.txt`).
- [x] **Input Sanitization & Validation**: Safe string and integer readers (`ler_string`, `ler_inteiro`) that clear leftover newline characters (`limpar_buffer`), collapse extra whitespace (`limpar_espacos`), and block duplicate book IDs.
- [x] **Recursive Merge Sort (`O(n log n)`)**: Alphabetical sorting by **Title** (`strcmp`) or chronological sorting by **Year** when listing the catalog.
- [x] **Case-Insensitive Substring Search**: Partial text matching (`tolower` + `strstr`) across **Title**, **Author**, and **Category**.
- [x] **Gap-Free Removal**: Deletes records by ID and shifts subsequent elements left to keep memory contiguous.
- [x] **Plain-Text Persistence (`livros.txt`)**: Automatic startup loading and manual save/reload using semicolon-delimited parsing (`strtok`).
- [x] **Collection Statistics Report**: Displays total book count, oldest/newest titles, and dynamic per-category counts without duplicate labels (`calloc`).
- [ ] **Binary Persistence (`livros.data`)**: Direct memory dump/load using `fwrite` and `fread`.
- [ ] **Bonus Enhancements**: User login screen (`usuarios.txt`) and `.csv` report export.

---

## 🧠 Under the Hood (How It Works)

Instead of relying on fixed-size global arrays, the system organizes memory and data flow across four decoupled layers:

```text
┌───────────────────┐     ┌───────────────────┐     ┌───────────────────┐
│   data/livros.txt │ ──▶ │   arquivo.c       │ ──▶ │   VetorLivros     │
│  (ID;Title;...)   │ ◀── │ (strtok / fprintf)│ ◀── │ (Dynamic Heap)    │
└───────────────────┘     └───────────────────┘     └─────────┬─────────┘
                                                              │
                          ┌───────────────────┐               ▼
                          │   util.c          │     ┌───────────────────┐
                          │ (Safe I/O & Trim) │ ──▶ │   vetor.c         │
                          └───────────────────┘     │ (MergeSort/Search)│
                                                    └───────────────────┘
```

* **Smart Memory Growth (`vetor.c`)**: `VetorLivros` holds a pointer to a `livro` array, its active count (`tamanho`), and its allocated limit (`capacidade`). When `tamanho == capacidade`, `cadastrar_livro()` doubles the allocated block via `realloc`, avoiding frequent system calls.
* **Divide-and-Conquer Sorting (`merge_sort_rec`)**: To sort books without mutating data mid-comparison, the array is recursively split into halves and merged back in order using temporary heap buffers (`E` and `D`), which are immediately freed afterward.
* **Bulletproof Terminal Input (`util.c`)**: Standard `scanf` calls often leave stray `\n` characters in `stdin` or fail on invalid text. Every input passes through `limpar_buffer()` and `limpar_espacos()`, preventing infinite loops and messy formatting.

---

## 🏗️ Project Architecture

```text
library-management-system/
├── include/               # Public module interfaces (.h)
│   ├── livro.h            # Book struct (id, titulo, autor, ano, categoria) & display
│   ├── vetor.h            # Dynamic vector lifecycle, search, Merge Sort & reports
│   ├── arquivo.h          # File path macros (TXT, BIN) & persistence prototypes
│   └── util.h             # Buffer cleanup, whitespace trimming & safe input helpers
├── src/                   # Implementation files (.c)
│   ├── main.c             # UTF-8 setup, ASCII banner loader & main switch loop
│   ├── livro.c            # Book constructor & formatted card output
│   ├── vetor.c            # Heap management, case-insensitive search & Merge Sort
│   ├── arquivo.c          # Text file reader/writer (strtok / fprintf)
│   └── util.c             # Cross-platform screen clear/pause & input validation
├── data/                  # Persistent storage & assets
│   ├── title.txt          # Startup ASCII art banner
│   ├── livros.txt         # Human-readable database (ID;Title;Author;Year;Category)
│   └── livros.data        # Binary database target
├── Makefile               # Automated build & cleanup rules
└── README.md              # Project documentation
```

> [!NOTE]
> **Database File Format (`data/livros.txt`)**  
> Records are stored one per line using `;` as a delimiter, automatically handling both Windows (`\r\n`) and Linux (`\n`) line endings:
> ```text
> 1;Crime e Castigo;Fiódor Dostoiévski;1866;Romance Psicológico
> 0;O Hobbit;J. R. R. Tolkien;1937;Fantasia
> ```

---

## 🚀 Compilation & Execution

### Using `Makefile` (Recommended)

```bash
# Build the project with compiler warnings enabled
make

# Run the executable
./lms        # Linux / macOS
lms.exe      # Windows

# Remove compiled object files and binaries
make clean
```

### Manual Compilation (Without `make`)

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/*.c -o lms
./lms
```

> [!TIP]
> Always run the executable from the **project root directory** (where `data/` is located) so the program can locate `data/title.txt` and `data/livros.txt` using relative paths.

---

## 📋 Main Menu Overview

The CLI menu is organized into **three vertical columns** for quick scanning:

| Option | Feature | Implementation Details | Status |
| :---: | :--- | :--- | :---: |
| **`[1]`** | **Register Book** | Reads `ID`, `Title`, `Author`, `Year`, `Category`; blocks duplicate IDs | ✅ Ready |
| **`[2]`** | **List Books** | Sorts via recursive **Merge Sort** by Title (A–Z) or Year (Ascending) | ✅ Ready |
| **`[3]`** | **Search Books** | Case-insensitive partial match by Title, Author, or Category | ✅ Ready |
| **`[4]`** | **Remove Book by ID** | Locates record by ID and shifts remaining items left | ✅ Ready |
| **`[5]`** | **Save to Text** | Exports full catalog to `data/livros.txt` | ✅ Ready |
| **`[6]`** | **Save to Binary** | Exports raw struct array to `data/livros.data` | 🚧 Planned |
| **`[7]`** | **Load from Text** | Resets memory and reloads records from `data/livros.txt` | ✅ Ready |
| **`[8]`** | **Generate Reports** | Shows total count, oldest/newest book, and per-category breakdown | ✅ Ready |
| **`[9]`** | **Exit** | Prompts to save changes before freeing heap memory (`liberar`) | ✅ Ready *(Text save)* |

---

## 👥 Authors

Developed collaboratively for **Computer Programming I**:

* **Vinícius ([@vinicius133](https://github.com/vinicius133))** — Main menu loop & UTF-8 terminal setup (`main`), safe input/buffer utilities (`util`), text/binary file persistence (`arquivo`), and build automation (`Makefile`).
* **José ([@Devze2612](https://github.com/Devze2612))** — Book struct & formatting (`livro`), dynamic array memory management (`vetor`), recursive Merge Sort, substring search filters, and collection reports.

```