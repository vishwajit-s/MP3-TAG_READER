# 🎵 MP3 Tag Reader & Editor

> A command-line tool written in C to read and modify ID3 metadata embedded in MP3 files — title, artist, album, year, genre, and more.

---

## 📖 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Concepts Used](#concepts-used)
- [Technologies Used](#technologies-used)
- [Getting Started](#getting-started)
- [Sample Input / Output](#sample-input--output)
- [Author](#author)

---

## Overview

The **MP3 Tag Reader & Editor** parses the **ID3v1 tag** stored in the last 128 bytes of an MP3 file. It allows users to inspect and update song metadata directly from the terminal — no GUI required.

This project demonstrates low-level binary file handling, struct-based data parsing, and offset-based memory access in C, making it an excellent deep-dive into how real-world media formats store metadata.

---

## Features

- 🎵 Read ID3v1 metadata from any `.mp3` file
- ✏️ Edit tags — Title, Artist, Album, Year, Genre, Comment
- 📁 Display structured song information in a readable format
- 💾 Write updated tags back to the MP3 file without altering audio data
- ⚡ Fast, lightweight command-line execution

---

## Project Structure

```
MP3_Tag_Editor/
│
├── main.c              # Entry point — argument parsing and operation dispatch
├── read_tags.c         # Reads and displays ID3v1 tag fields from the MP3 file
├── edit_tags.c         # Handles user input and overwrites tag fields
├── file_handler.c      # Low-level binary file open/seek/read/write operations
├── mp3_tags.h          # Header — ID3 struct definition and function declarations
│
└── sample/
    └── song.mp3        # Sample MP3 file for testing
```

---

## Concepts Used

| Concept | Usage |
|---|---|
| **Binary File Handling** | Opens MP3 in binary mode (`"rb+"`) and seeks to the ID3 tag offset |
| **Structures** | `struct ID3Tag` maps exactly to the 128-byte ID3v1 tag layout |
| **`fseek` / `fread` / `fwrite`** | Navigates to and reads/writes the tag block at the end of the file |
| **String Manipulation** | `strncpy`, `memset` to safely copy and clear fixed-length tag fields |
| **Command-line Arguments** | `argc` / `argv` used to pass the MP3 file path and operation flags |
| **Modular Programming** | Read, edit, and file operations separated into individual source files |

---

## Technologies Used

- **Language:** C (C99)
- **Compiler:** GCC
- **Platform:** Linux / Windows (GCC supported)
- **Tag Standard:** ID3v1 (128-byte footer tag)

---

## Getting Started

### Prerequisites

Ensure GCC is installed:

```bash
gcc --version
```

### Compile

```bash
gcc *.c -o mp3editor
```

### Run

**Linux / macOS:**
```bash
./mp3editor song.mp3
```

**Windows:**
```bash
mp3editor.exe song.mp3
```

---

## Sample Input / Output

### 🎵 Reading Tags

```bash
./mp3editor song.mp3 --read
```

```
========================================
         MP3 Tag Information
========================================
Title   : Bohemian Rhapsody
Artist  : Queen
Album   : A Night at the Opera
Year    : 1975
Genre   : Rock
Comment : Classic track
========================================
```

### ✏️ Editing a Tag

```bash
./mp3editor song.mp3 --edit
```

```
Select field to edit:
1. Title
2. Artist
3. Album
4. Year
5. Genre
6. Comment
Enter choice: 2

Current Artist : Queen
Enter new value: Queen (Remastered)

✅ Tag updated successfully!
```

### 🔍 After Re-reading

```
========================================
         MP3 Tag Information
========================================
Title   : Bohemian Rhapsody
Artist  : Queen (Remastered)
Album   : A Night at the Opera
Year    : 1975
Genre   : Rock
Comment : Classic track
========================================
```

### ❌ Invalid File

```bash
./mp3editor notafile.mp3 --read

Error: Could not open file 'notafile.mp3'. Please check the path.
```

---

## Author

**Vishwajit Sawant**

---

